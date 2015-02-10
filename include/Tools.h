#ifndef Tools_h
#define Tools_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// This will house the tools needed for the calculation and analysis //
// of the electric field from the initial Geant4 calculation of the  //
// vector potential.  Also some generic histogram formatting methods //
// will be added.                                                    //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TH1F.h"
#include "TVirtualFFT.h"
#include "TString.h"
#include <iostream>
#include "TMath.h"
#include "Options.h"

class Tools : public TObject
{

 public:

  // Constructor / Destructor
  Tools(){ m_FTFDcalled = false; };
  virtual ~Tools(){};

  // Get fourier transform of time-domain input
  TH1F* getFTFD(TH1F* h_TD);

  // Get fourier transform back to time-domain
  // and also hacking off some frequency.
  // NOTE: getFT must be called first
  TH1F* getFTTD(TH1F* h_TD, TH1F* h_FD,
		float fmin=-999, float fmax=-999);

 private:
  
  //TVirtualFFT* m_FFT;     // FFT object from root
  bool m_FTFDcalled;      // Necessary flag

  ClassDef(Tools,1);

};

#endif
