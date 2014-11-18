#ifndef Antenna_h
#define Antenna_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Antenna class to hold the information about the antenna   //
// position, vector potential, and also some convenient info //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TH1F.h"
#include "TObject.h"
#include "TString.h"
#include <sstream>
#include <iostream>

class Antenna : public TObject
{

 public:

  // Default constructor / destructor
  Antenna(){
    m_VP_mag = NULL;
    m_VP_X = NULL;
    m_VP_Y = NULL;
    m_VP_Z = NULL;
    this->setPos(0,0,0);
    this->setRPos(0,0,0);
    m_initialized = false;
  };
  virtual ~Antenna(){     
    if(m_VP_mag) delete m_VP_mag;
    if(m_VP_X) delete m_VP_X;
    if(m_VP_Y) delete m_VP_Y;
    if(m_VP_Z) delete m_VP_Z;
  };
  
  // Constructor
  void initialize(float x, float y, float z,
		  float xr, float yr, float zr,
		  int nSteps, float stepSize,
		  float startTime)
  {
    // Set Pos
    this->setPos(x,y,z);
    this->setRPos(xr,yr,zr);
    
    // Hist name
    std::stringstream name;
    name << "A_Ant_" << x << "_" 
	 << y <<  "_" << z;
    TString basename = TString(name.str().c_str());
    
    // Hist min max
    float tmin = startTime - stepSize/2.;
    float tmax = tmin + nSteps * stepSize;

    // Now make histograms for the X,Y,Z, Mag
    m_VP_mag = new TH1F((basename+"_mag"),"",nSteps,tmin,tmax);			
    m_VP_mag->Sumw2();
    m_VP_X = new TH1F((basename+"_X"),"",nSteps,tmin,tmax);			
    m_VP_X->Sumw2();
    m_VP_Y = new TH1F((basename+"_Y"),"",nSteps,tmin,tmax);			
    m_VP_Y->Sumw2();
    m_VP_Z = new TH1F((basename+"_Z"),"",nSteps,tmin,tmax);			
    m_VP_Z->Sumw2();

    // Set flag to true
    m_initialized = true;

  };

  // Setting
  void setPos(float x, float y, float z){
    m_x = x; m_y = y; m_z = z;
  };
  void setRPos(float x, float y, float z){
    m_xr = x; m_yr = y; m_zr = z;
  };
  void setX(float x){ m_x = x; };
  void setY(float y){ m_y = y; };
  void setZ(float z){ m_z = z; };
  
  // Getting
  float getX()  { return m_x;   };
  float getY()  { return m_y;   };
  float getZ()  { return m_z;   };
  TH1F* getVP() { return m_VP_mag;  };
  TH1F* getVPX(){ return m_VP_X; };
  TH1F* getVPY(){ return m_VP_Y; };
  TH1F* getVPZ(){ return m_VP_Z; };

  // Fill information
  void fill(float time, float A) { m_VP_mag->Fill(time, A); }  
  void fillX(float time, float A){ m_VP_X->Fill(time, A);   }  
  void fillY(float time, float A){ m_VP_Y->Fill(time, A);   }  
  void fillZ(float time, float A){ m_VP_Z->Fill(time, A);   }  

  // Checker
  bool isInitialized(){ return m_initialized; };

  ClassDef(Antenna, 1);

 protected:
  
  // Profile for overall result
  TH1F* m_VP_mag;
  TH1F* m_VP_X;
  TH1F* m_VP_Y;
  TH1F* m_VP_Z;
  
  // Position 
  float m_x;
  float m_y;
  float m_z;

  // Refracted Position 
  float m_xr;
  float m_yr;
  float m_zr;

  // Flag whether initialized
  bool m_initialized;

};

#endif
