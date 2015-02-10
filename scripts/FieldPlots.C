
#include "myHist.C"

TString m_savedir  = "../plots/Fields/";
TString m_savename = "";
//bool m_save = true;
bool m_save = false;

//--------------------------------------------------//
// Main
//--------------------------------------------------//
void FieldPlots(int fopt, int opt)
{

  // Open a file
  TFile* file = NULL;
  int iAnt = 0;
  if(fopt == 0){
    //file = new TFile("rootfiles/SingleBunch_50Evt_40MeV.root");
    file = new TFile("rootfiles/Bunches1_50Evt_40MeV_xzScan.root");
    m_savename = "Bunch1";
    iA = 26;
  }
  else if(fopt == 1) {
    //file = new TFile("rootfiles/Bunches5_50Evt_40MeV.root");
    file = new TFile("rootfiles/Bunches5_50Evt_40MeV_xzScan.root");
    m_savename = "Bunch5";
    iA = 26;
  }
  else if(fopt == 2) {
    file = new TFile("rootfiles/Bunches5_50Evt_40MeV_10000Prim_Gauss60mm_xzScan.root");
    m_savename = "Bunch5_bw60mm";
    iA = 19;
  }
  else if(fopt == 3) {
    file = new TFile("rootfiles/Bunches5_50Evt_40MeV_10000Prim_Gauss45mm_xzScan.root");
    m_savename = "Bunch5_bw45mm";
    iA = 19;
  }
  else if(fopt == 4) {
    file = new TFile("rootfiles/Bunches5_50Evt_40MeV_10000Prim_Gauss45mm_xzScan_730cmAway.root");
    m_savename = "Bunch5_bw45mm_730cm";
    iA = 21;
  }
  else if(fopt == 5) {
    file = new TFile("rootfiles/BP_bias120_50Evt_40MeV_xz_730cm.root");
    m_savename = "BP_bw45mm_730cm";
    iA = 21;
  }
  else return;


  // Choose what to plot
  if(opt == 0) plotA(file, iA);
  if(opt == 1) plotE(file, iA);
  if(opt == 2) plotEcomp(file, iA);

}

//--------------------------------------------------//
// Plot a single angle vector potential
//--------------------------------------------------//
void plotA(TFile* file)
{

  // Specify the plot number
  int iA = 21; // corresponds to 56 degrees
  float tmin = 590e-9;
  float tmax = 602e-9;  

  // Make canvas
  TCanvas* c = makeCanvas("c");
  c->SetLogy();

  // Get histogram
  TH1F* h_A = SummaryMag->getA(iA);
  setHistAtt(h_A,"time [s]","|A(t)| [Vs/m]",kBlack,20);
  h_A->SetMarkerSize(0.5);
  
  cout<<"Plotting: "<<SummaryMag->getAngle(iA)*180/TMath::Pi()<<endl;

  // Set some ranges
  h_A->SetMinimum( h_A->GetMaximum() * 1e-5);
  //h_A->GetXaxis()->SetRange( h_A->FindBin(tmin), h_A->FindBin(tmax) );

  // Draw
  h_A->Draw();

  // Save
  if(m_save)
    c->SaveAs((m_savedir+m_savename+"_VP_56deg.png"));

}

//--------------------------------------------------//
// Plot a single angle efield
//--------------------------------------------------//
void plotE(TFile* file)
{

  // Specify the plot number
  int iA = 28; // corresponds to 56 degrees
  float tmin = 593e-9;
  float tmax = 596e-9;  

  // Make canvas
  TCanvas* c = makeCanvas("c");

  // Get histogram
  TH1F* h_E = SummaryMag->getE(iA);
  setHistAtt(h_E,"time [s]","|E(t)| [V/m]",kBlack,20);
  h_E->SetMarkerSize(0.5);
  
  // Set some ranges
  //h_E->SetMinimum( h_E->GetMaximum() * 1e-5);
  h_E->GetXaxis()->SetRange( h_E->FindBin(tmin), h_E->FindBin(tmax) );

  // Draw
  h_E->Draw("hist");

  // Save
  if(m_save)
    c->SaveAs((m_savedir+m_savename+"_E_56deg.png"));

}

//--------------------------------------------------//
// Plot components of the electric field
//--------------------------------------------------//
void plotEcomp(TFile* file)
{

  // Specify the plot number
  int iA = 41; // corresponds to 56 degrees

  // Make canvas
  TCanvas* c = makeCanvas("c");

  // Legend
  TLegend* leg = makeLegend(0.8,0.9,0.7,0.9);

  // Hist attributes
  TString ytitle = "E(t) [V/m]";
  TString xtitle = "time [s]";
  int colors[]   = {kBlack, kBlue, kRed, kMagenta};
  
  // Store the histograms
  const int nHists = 3;
  TH1F* hists[nHists];
  TString hnames[] = {"E_{x}","E_{z}","E_{y}"}

  // Get histogram
  //hists[0] = SummaryMag->getE(iA);
  hists[0] = SummaryX->getE(iA);
  hists[1] = SummaryZ->getE(iA);
  hists[2] = SummaryY->getE(iA);

  // Get central value of t
  float tpeak = maxT(hists[0]);
  float dt    = 1e-9;

  // Set attributes
  for(int ih=0; ih<nHists; ++ih){
    setHistAtt(hists[ih],xtitle,ytitle,colors[ih],20);
    leg->AddEntry(hists[ih],hnames[ih],"l");
    hists[ih]->GetXaxis()->SetRange( hists[ih]->FindBin(tpeak-dt),
				     hists[ih]->FindBin(tpeak+dt));    
    hists[ih]->Draw( (ih==0 ? "hist" : "histsame") );
  }
  leg->Draw("same");
  
  // Save
  if(m_save)
    c->SaveAs((m_savedir+m_savename+"_E_Comparison.png"));

}

//--------------------------------------------------//
// Find time where vector potential peaks
//--------------------------------------------------//
float maxT(TH1F* h)
{

  // Find the bin corresponding to max value
  return h->GetBinCenter( h->GetMaximumBin() );

}
