
#include "myHist.C"

TString m_savedir = "../plots/Angular/";
bool m_save = false;
//bool m_save = true;

//--------------------------------------------//
// Quick angular plot
//--------------------------------------------//
void Angular(int opt, bool save = false)
{

  m_save = save;

  if(opt == 0) plotInd();
  if(opt == 1) plotFileComp();


}

//--------------------------------------------//
// Plot individual file multi freq
//--------------------------------------------//
void plotFileComp()
{

  // Setup files
  TString fdir = "rootfiles/";
  vector<TString> fnames;
  fnames.push_back(fdir+"Bunches5_50Evt_40MeV_10000Prim_Gauss60mm_xzScan.root");
  fnames.push_back(fdir+"Bunches5_50Evt_40MeV_10000Prim_Gauss45mm_xzScan.root");
  fnames.push_back(fdir+"Bunches5_50Evt_40MeV_10000Prim_Gauss45mm_xzScan_730cmAway.root");
  fnames.push_back(fdir+"BP_bias120_50Evt_40MeV_10000Prim__xz_730cmAway_Gauss45mm.root");

  // Setup legend names
  vector<TString> ftitles;
  ftitles.push_back("bw=6cm, x=6");
  ftitles.push_back("bw=4.5cm, x=6");
  ftitles.push_back("bw=4.5cm, x=7.3m");
  ftitles.push_back("bw=4.5cm, x=7.3, BP");

  // Tools object
  Tools* tool = new Tools();

  // Plot for just one Frequency
  float freq = 400e6;
  TString ltitle = "400MHz";

  // plotting stuff
  TString xtitle = "Angle relative to beam [deg]";
  TString ytitle = "Arbitrary Units";
  int colors[] = {kBlack, kBlue, kViolet, kRed};

  // Make canvas and legend
  TCanvas* c = makeCanvas("c");
  TLegend* leg = makeLegend(0.15,0.3,0.6,0.93);
  leg->SetHeader(ltitle);

  // Open the first file
  TFile* file = new TFile(fnames.at(0));
  
  // Set place holders
  int npoints = SummaryZ->getN();
  float angles[4][1000];
  float Ef[4][1000];
  float maximum = -999;

  // Close file
  file->Close();

  // Loop over the files
  for(unsigned int i=0; i<fnames.size(); ++i){
    file = new TFile(fnames.at(i));

    // Loop and save info
    for(int ip=0; ip<npoints; ++ip){
      
      // Save angle
      angles[i][ip] = fabs(SummaryZ->getAngle(ip) * 180/TMath::Pi());
      
      // Get Efield histogram
      TH1F* h_TD = SummaryZ->getE(ip);

      // Fourier Transform
      TH1F* h_FD = tool->getFTFD(h_TD);

      // Now save for different frequencies
      int bin = h_FD->FindBin(freq);
      Ef[i][ip] = h_FD->GetBinContent(bin);
      if( maximum < Ef[i][ip] )
	maximum = Ef[i][ip];
    }    
    
    file->Close();

  }

  // Now make frame object
  TH1F* frame = makeHist("frame",1,0,90,xtitle,ytitle,kBlack,20);
  frame->SetMaximum(maximum*1.2);
  frame->Draw();

  // Now make graphs and plot
  for(unsigned int i=0; i<fnames.size(); ++i){
    TGraph* gr = new TGraph(npoints, angles[i], Ef[i]);
    setAtt(gr,xtitle,ytitle,colors[i]);
    gr->Draw("same");
    leg->AddEntry(gr,ftitles.at(i),"le");
  }

  leg->Draw("same");
  
  // Save the plot
  if(m_save)
    c->SaveAs((m_savedir+"Comparison_xzScan_"+ltitle+".png"));

}

//--------------------------------------------//
// Plot individual file multi freq
//--------------------------------------------//
void plotInd()
{

  // Input file and save name
  //TFile* file = new TFile("rootfiles/Bunches5_50Evt_40MeV_10000Prim_Gauss60mm_xzScan.root");
  //TString save = "Bunches5_xzScan_bw60mm";

  //TFile* file = new TFile("rootfiles/Bunches5_50Evt_40MeV_10000Prim_Gauss45mm_xzScan.root");
  //TString save = "Bunches5_xzScan_bw45mm";
  
  //TFile* file = new TFile("rootfiles/Bunches5_50Evt_40MeV_10000Prim_Gauss45mm_xzScan_730cmAway.root");
  //TString save = "Bunches5_xzScan_bw45mm_730cmAway";

  TFile* file = new TFile("rootfiles/BP_bias120_50Evt_40MeV_10000Prim__xz_730cmAway_Gauss45mm.root");
  TString save = "BP_bias120_xzScan_bw45mm_730cmAway";


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
  int npoints = SummaryZ->getN();
  float angles[1000];
  float Ef[4][1000];
  float maximum = -999;

  // Loop and save info
  for(int ip=0; ip<npoints; ++ip){
    
    // Save angle
    angles[ip] = fabs(SummaryZ->getAngle(ip) * 180/TMath::Pi());
    
    // Get Efield histogram
    TH1F* h_TD = SummaryZ->getE(ip);

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
    c->SaveAs((m_savedir+save+".png"));
}
