
#include "myHist.C"

TString m_savedir  = "../plots/Fields/";
TString m_savename = "";
bool m_save = true;

//--------------------------------------------------//
// Main
//--------------------------------------------------//
void FieldPlots(int fopt, int opt)
{

  // Open a file
  TFile* file = NULL;
  if(fopt == 0){
    file = new TFile("rootfiles/SingleBunch_50Evt_40MeV.root");
    m_savename = "Bunch1";
  }
  else if(fopt == 1) {
    file = new TFile("rootfiles/Bunches5_50Evt_40MeV.root");
    m_savename = "Bunch5";
  }
  else return;


  // Choose what to plot
  if(opt == 0) plotA(file);
  if(opt == 1) plotE(file);

}

//--------------------------------------------------//
// Plot a single angle vector potential
//--------------------------------------------------//
void plotA(TFile* file)
{

  // Specify the plot number
  int iA = 28; // corresponds to 56 degrees
  float tmin = 590e-9;
  float tmax = 602e-9;  

  // Make canvas
  TCanvas* c = makeCanvas("c");
  c->SetLogy();

  // Get histogram
  TH1F* h_A = Summary->getA(iA);
  setHistAtt(h_A,"time [s]","|A(t)| [Vs/m]",kBlack,20);
  h_A->SetMarkerSize(0.5);
  
  // Set some ranges
  h_A->SetMinimum( h_A->GetMaximum() * 1e-5);
  h_A->GetXaxis()->SetRange( h_A->FindBin(tmin), h_A->FindBin(tmax) );

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
  TH1F* h_E = Summary->getE(iA);
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

