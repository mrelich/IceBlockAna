
#include "Tools.h"

using namespace std;

//--------------------------------------------------------//
// Get the fourier transform for time-domain input
//--------------------------------------------------------//
TH1F* Tools::getFTFD(TH1F* h_TD)
{

  // Get the fourier transform
  TH1F* ft = (TH1F*) h_TD->FFT(NULL,"MAG");

  // For some reason, root is stupid and doesn't
  // format the result appropriately.  So more work
  // is needed

  // Bins of FT
  float xminft = ft->GetXaxis()->GetXmin();
  float xmaxft = ft->GetXaxis()->GetXmax();
  int nbinsft  = ft->GetNbinsX();

  // Info from original
  float xmin = h_TD->GetXaxis()->GetXmin();
  float xmax = h_TD->GetXaxis()->GetXmax();
  int  nbins = h_TD->GetNbinsX();

  TString ft_name = TString(h_TD->GetName()) + "_FTTD"; 
  TH1F* ft_fixed  = new TH1F(ft_name,"",nbinsft,
			     xminft/(xmax-xmin),
			     xmaxft/(xmax-xmin));
  
  // Now fill the fixed FT
  for(int bin=1; bin<=nbinsft; ++bin){

    float bcon = ft->GetBinContent(bin)/sqrt(nbins);
    float bcen = ft->GetBinCenter(bin)/(xmax-xmin);

    int newbin = ft_fixed->FindBin(bcen);
    ft_fixed->SetBinContent(newbin, bcon);
    ft_fixed->SetBinError(newbin, 0); // Now sure how to handle error yet...

  }// end loop over bins

  // Set the flag so we know we have called this function
  m_FTFDcalled = true;

  // Clean up and return
  delete ft;
  return ft_fixed;

}

//--------------------------------------------------------//
// Get the fourier transform for going back to time-domain
// and hacking off some frequency
//--------------------------------------------------------//
TH1F* Tools::getFTTD(TH1F* h_TD, TH1F* h_FD, float fmin, float fmax)
{

  // getFTFD(...) must be called before using this method
  // It relies on one already having input the time-domain
  // response to be fourier transformed.
  if( !m_FTFDcalled ){
    cout<<"Must call getFTFD before getFTTD"<<endl;
    cout<<"Returning NULL..."<<endl;
    return NULL;
  }
  m_FTFDcalled = false;

  // Get the FFT object
  TVirtualFFT* fft = TVirtualFFT::GetCurrentTransform();

  // Get binning info
  float xmin  = h_TD->GetXaxis()->GetXmin();
  float xmax  = h_TD->GetXaxis()->GetXmax();
  float scale = 1/(xmax-xmin);
  int ntbins  = h_TD->GetNbinsX();

  // Get the real and imaginary components
  int nfbins = h_FD->GetNbinsX();
  Double_t *re_full = new Double_t[nfbins];
  Double_t *im_full = new Double_t[nfbins];
  fft->GetPointsComplex(re_full, im_full);
  
  // Now loop over real and imaginary parts
  // and reset the bin content dependent on
  // the frequency range.
  for(int n=0; n<nfbins; ++n){
    
    // Get the frequency with appropriate scale
    // to take it bck to Hz
    double f = h_FD->GetBinCenter(n+1) * scale;
    
    // Check if frequency is in range we are
    // after.  Note default = -999
    if( fmin <= 0); // do nothing
    else if( fmin < f && f < fmax){
      // Here is where we will add the gain
      // of the antenna.  For now do nothing
    }
    else{
      re_full[n] = 0;
      im_full[n] = 0;
    }

  }// end loop over points

  // Now transform the points back to time-domain
  TVirtualFFT* fft_back = TVirtualFFT::FFT(1, &ntbins, "C2R M K");
  fft_back->SetPointsComplex(re_full, im_full);
  fft_back->Transform();
  TH1F* h_back = (TH1F*) TH1::TransformHisto(fft_back,NULL,"Re");

  // Now again, root sucks and doesn't put this into
  // usable format. So format it back
  TString backname   = TString(h_FD->GetName()) + "_back";
  TH1F* h_back_fixed = new TH1F(backname,"",ntbins,xmin,xmax);
  h_back->SetName(backname);
  double shift = (xmax-xmin)/ntbins;
  for(int bin=1; bin<=ntbins; ++bin){
    float bcon = h_back->GetBinContent(bin) / ntbins;
    float berr = h_back->GetBinError(bin) / ntbins;
    float bcen = h_back->GetBinCenter(bin) * shift;
    
    int newbin = h_back_fixed->FindBin(bcen);
    h_back_fixed->SetBinContent(newbin,bcon);
    h_back_fixed->SetBinError(newbin,berr);
  }// end fix

  // clean up
  delete re_full;
  delete im_full;
  delete fft;
  delete fft_back;
  delete h_back;

  // Return the result
  return h_back_fixed;

}
