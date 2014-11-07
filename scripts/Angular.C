
#include "myHist.C"

TString m_savedir = "../plots/Angular/";
//bool m_save = false;
bool m_save = true;

//--------------------------------------------//
// Quick angular plot
//--------------------------------------------//
void Angular()
{

  // Input file
  //TFile* file = new TFile("test.root");
  //TFile* file = new TFile("rootfiles/SingleBunch_50Evt_40MeV.root");
  //TFile* file = new TFile("rootfiles/Bunches5_50Evt_40MeV.root");
  //TFile* file = new TFile("rootfiles/SingleBunch_50Evt_40MeV_xzScan.root");
  TFile* file = new TFile("rootfiles/Bunches5_50Evt_40MeV_xzScan.root");

  // Tools object
  Tools* tool = new Tools();

  // Specify the frequencies
  vector<float> freqs;
  freqs.push_back(800e6);
  freqs.push_back(600e6);
  freqs.push_back(400e6);
  freqs.push_back(200e6);

  // Specify names for legend
  vector<TString> fnames;
  fnames.push_back("800 MHz");
  fnames.push_back("600 MHz");
  fnames.push_back("400 MHz");
  fnames.push_back("200 MHz");

  // plotting stuff
  TString xtitle = "Angle relative to beam [deg]";
  TString ytitle = "Arbitrary Units";
  int colors[] = {kBlack, kBlue, kViolet, kRed};

  // Make canvas and legend
  TCanvas* c = makeCanvas("c");
  TLegend* leg = makeLegend(0.15,0.3,0.6,0.93);
  
  // Set place holders
  int npoints = Summary->getN();
  float angles[1000];
  float Ef[4][1000];
  float maximum = -999;

  // Loop and save info
  for(int ip=0; ip<npoints; ++ip){
    
    // Save angle
    angles[ip] = fabs(Summary->getAngle(ip) * 180/TMath::Pi());
    
    // Get Efield histogram
    TH1F* h_TD = Summary->getE(ip);

    // Fourier Transform
    TH1F* h_FD = tool->getFTFD(h_TD);

    // Now save for different frequencies
    for(unsigned int i=0; i<freqs.size(); ++i){
      float freq = freqs.at(i);
      int bin    = h_FD->FindBin(freq);
      Ef[i][ip] = h_FD->GetBinContent(bin);
      if( maximum < Ef[i][ip] )
	maximum = Ef[i][ip];
    }    
  }

  // Now make frame object
  TH1F* frame = makeHist("frame",1,0,90,xtitle,ytitle,kBlack,20);
  frame->SetMaximum(maximum*1.2);
  frame->Draw();

  // Now make graphs and plot
  for(unsigned int i=0; i<freqs.size(); ++i){
    TGraph* gr = new TGraph(npoints, angles, Ef[i]);
    setAtt(gr,xtitle,ytitle,colors[i]);
    gr->Draw("same");
    leg->AddEntry(gr,fnames.at(i),"le");
  }

  leg->Draw("same");
  
  // Save the plot
  if(m_save)
    //c->SaveAs((m_savedir+"singlePulse.png"));
    //c->SaveAs((m_savedir+"bunches5.png"));
    c->SaveAs((m_savedir+"bunches5_xzScan.png"));
}
