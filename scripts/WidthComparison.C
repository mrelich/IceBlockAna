
#include "myHist.C"

TString m_savedir = "../plots/BPPlots/";
bool m_save = false;
int m_colors[] = {kBlack, kRed, kBlue, kGreen, kOrange-3, kMagenta};
int m_markers[] = {20, 25, 24, 23, 26, 21};

//----------------------------------------//
// Main
//----------------------------------------//
void WidthComparison(int opt, bool save=false)
{

  m_save = save;

  // Specify the input files for comaparison
  TString dir = "rootfiles/";
  vector<TString> fnames;
  //fnames.push_back(dir+"Bunches1_50Evt_40MeV_1000Prim_SinglePos.root");
  //fnames.push_back(dir+"Bunches5_50Evt_40MeV_1000Prim_SinglePos.root");
  //fnames.push_back(dir+"Bunches1_50Evt_40MeV_10000Prim_Gauss60mm.root");
  //fnames.push_back(dir+"Bunches5_50Evt_40MeV_10000Prim_Gauss60mm.root");
  //fnames.push_back(dir+"Bunches1_100Evt_40MeV_10000Prim_Gauss100mm.root");
  //fnames.push_back(dir+"Bunches5_100Evt_40MeV_10000Prim_Gauss100mm.root");

  fnames.push_back(dir+"Bunches5_50Evt_40MeV_10000Prim_HardCodedAntenna_R100m_Gauss45mm.root");
  fnames.push_back(dir+"Bunches12_50Evt_40MeV_10000Prim_HardCodedAntenna_R100m_Gauss45mm.root");
  fnames.push_back(dir+"BP_bias120_50Evt_40MeV_10000Prim__HardCodedAntenna_R100m_Gauss45mm.root");
  fnames.push_back(dir+"BP_bias120_50Evt_40MeV_10000Prim__HardCodedAntenna_R100m_singlePos.root");
  

  // Specify the legend names
  vector<TString> legnames;
  //legnames.push_back("Single Pos 1 Bunch");
  //legnames.push_back("Single Pos 5 Bunch");
  //legnames.push_back("Gaussian 6cm 1 Bunch");
  //legnames.push_back("Gaussian 6cm 5 Bunch");
  //legnames.push_back("Gaussian 10cm 1 Bunch");
  //legnames.push_back("Gaussian 10cm 5 Bunch");

  legnames.push_back("#sigma=4.5cm, 5 Bunches");
  legnames.push_back("#sigma=4.5cm, 12 Bunches");
  legnames.push_back("#sigma=4.5cm, Beam Profile");
  legnames.push_back("#sigma=0, Beam Profile");

  // Scales are already taken into account!!!
  vector<float> scales;
  scales.push_back(1);
  scales.push_back(1);
  scales.push_back(1);
  scales.push_back(1);
  scales.push_back(1);
  scales.push_back(1);

  // The plots we are interested in seeing are the 
  // vector potential, electric field, the frequncy
  // spectrum for the electric field for a few frequencies
  // and then the field with our filter.
  
  // Vector potential
  if(opt == 0) plotVP(fnames, legnames, scales);
  if(opt == 1) plotE(fnames, legnames, scales);
  if(opt == 2) plotFTE(fnames, legnames, scales);
  if(opt == 3) plotEwithFilter(fnames,legnames, scales);

}

//----------------------------------------//
// Vector potential plots
//----------------------------------------//
void plotVP(vector<TString> fnames, 
	    vector<TString> lnames,
	    vector<float> scales)
{

  // Hist attributes
  TString xtitle = "time [s]";
  TString ytitle = "|A(t)| [Vs/m]";
  float xmin = 590e-9;
  float xmax = 605e-9;
  TString savename = "VP";

  // Load the histograms that are of interest
  vector<TH1F*> hists;
  for(unsigned int i=0; i<fnames.size(); ++i){
    TFile* file  = new TFile(fnames.at(i));
    hists.push_back( SummaryMag->getA(0) );
    hists.back()->SetDirectory(0);
    setHistAtt(hists.back(), xtitle, ytitle, m_colors[i], m_markers[i]);
    hists.back()->Scale(scales.at(i));
    file->Close();
  }// end loading of histograms
  
  plot(hists, lnames, savename, xmin, xmax, true);

}

//----------------------------------------//
// Vector potential plots
//----------------------------------------//
void plotE(vector<TString> fnames, 
	   vector<TString> lnames,
	   vector<float> scales)
{

  // Hist attributes
  TString xtitle = "time [s]";
  TString ytitle = "E_{z}(t) [V/m]";
  float xmin = 590e-9;
  float xmax = 600e-9;
  TString savename = "E";
  
  // Load the histograms that are of interest
  vector<TH1F*> hists;
  for(unsigned int i=0; i<fnames.size(); ++i){
    TFile* file  = new TFile(fnames.at(i));
    hists.push_back( SummaryZ->getE(0) );
    hists.back()->SetDirectory(0);
    setHistAtt(hists.back(), xtitle, ytitle, m_colors[i], m_markers[i]);
    hists.back()->Scale(scales.at(i));
    file->Close();
  }// end loading of histograms
  
  plot(hists, lnames, savename, xmin, xmax);

}

//----------------------------------------//
// Vector potential plots
//----------------------------------------//
void plotFTE(vector<TString> fnames, 
	     vector<TString> lnames,
	     vector<float> scales)
{

  // Hist attributes
  TString xtitle = "frequency [Hz]";
  TString ytitle = "Arbitrary Units";
  float xmin = 1e8;
  float xmax = 3e9;
  TString savename = "FTE";

  // Get Tool for FT
  Tools* fttool = new Tools();

  // Load the histograms that are of interest
  vector<TH1F*> hists;
  for(unsigned int i=0; i<fnames.size(); ++i){
    TFile* file  = new TFile(fnames.at(i));
    TH1F* E_td   = SummaryZ->getE(0);
    TH1F* E_fd   = fttool->getFTFD(E_td);
    hists.push_back( E_fd );
    hists.back()->SetDirectory(0);
    setHistAtt(hists.back(), xtitle, ytitle, m_colors[i], m_markers[i]);
    hists.back()->Scale(scales.at(i));
    hists.back()->SetLineWidth(2);
    file->Close();
  }// end loading of histograms
  
  plot(hists, lnames, savename, xmin, xmax, true, true);

}

//----------------------------------------//
// Vector potential plots
//----------------------------------------//
void plotEwithFilter(vector<TString> fnames, 
		     vector<TString> lnames,
		     vector<float> scales)
{

  // Hist attributes
  TString xtitle = "frequency [Hz]";
  TString ytitle = "|E(t)| [V/m]";
  float xmin = -999;
  float xmax = -999;
  TString savename = "EwithFilter";

  // Filter frequency
  float fmin = 200e6;
  float fmax = 400e6;

  // Get Tool for FT
  Tools* fttool = new Tools();

  // Load the histograms that are of interest
  vector<TH1F*> hists;
  for(unsigned int i=0; i<fnames.size(); ++i){
    TFile* file  = new TFile(fnames.at(i));
    TH1F* E_td   = SummaryMag->getE(0);
    TH1F* E_fd   = fttool->getFTFD(E_td);
    hists.push_back( fttool->getFTTD(E_td, E_fd, fmin, fmax) );
    hists.back()->SetDirectory(0);
    setHistAtt(hists.back(), xtitle, ytitle, m_colors[i], m_markers[i]);
    hists.back()->Scale(scales.at(i));
    file->Close();
  }// end loading of histograms
  
  plot(hists, lnames, savename, xmin, xmax, false);

}


//----------------------------------------//
// Plot generic
//----------------------------------------//
void plot(vector<TH1F*> hists, 
	  vector<TString> lnames,
	  TString savename,
	  float xmin=-999, float xmax=-999,
	  bool logy=false,
	  bool logx=false)
{

  // Make canvas
  TCanvas* c = makeCanvas("c");
  if(logy) c->SetLogy();
  if(logx) c->SetLogx();

  // Make legend
  TLegend* leg = makeLegend(0.6,0.80,0.93-0.05*hists.size(),0.93);
  
  // Get minimum and maximum
  float maximum = -999;
  float minimum = 999;
  for(unsigned int i=0; i<hists.size(); ++i){
    if( maximum < hists[i]->GetMaximum() )
      maximum = hists[i]->GetMaximum();
    if( minimum > hists[i]->GetMinimum() )
      minimum = hists[i]->GetMinimum();
  }

  // Set minimum and maximum y
  hists.at(0)->SetMaximum((logy ? 5 : 1.2)*maximum);
  if(logy) hists.at(0)->SetMinimum( 1e-5 * maximum);
  else     hists.at(0)->SetMinimum( 1.2*minimum );

  // Set the range to be plotted, if necessary
  if( xmin > 0 && xmax > 0){
    hists[0]->GetXaxis()->SetRange( hists[0]->FindBin(xmin),
				    hists[0]->FindBin(xmax));
  }

  // Draw
  hists.at(0)->Draw();
  leg->AddEntry(hists.at(0), lnames.at(0), "lep");
  for(unsigned int i=1; i<lnames.size(); ++i){
    hists.at(i)->Draw("same");
    leg->AddEntry(hists.at(i), lnames.at(i), "lep");
  }

  leg->Draw("same");

  // Save
  if(m_save)
    c->SaveAs((m_savedir+savename+".png"));

}
