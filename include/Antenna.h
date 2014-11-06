#ifndef Antenna_h
#define Antenna_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Antenna class to hold the information about the antenna   //
// position, vector potential, and also some convenient info //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TH1F.h"
#include "TObject.h"
#include <sstream>
#include <iostream>

class Antenna : public TObject
{

 public:

  // Default constructor / destructor
  Antenna(){
    m_VP = NULL;
    this->setPos(0,0,0);
    this->setRPos(0,0,0);
    m_initialized = false;
  };
  virtual ~Antenna(){     
    if(m_VP) delete m_VP;
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
    name << "Ant_" << x << "_" 
	 << y <<  "_" << z;
    //std::cout<<"\tMaking antenna: "<<name.str()<<std::endl;
    // Hist min max
    float tmin = startTime - stepSize/2.;
    float tmax = tmin + nSteps * stepSize;
    m_VP = new TH1F(name.str().c_str(),"",
		    nSteps,tmin,tmax);
    m_VP->Sumw2();

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
  float getX() { return m_x;  };
  float getY() { return m_y;  };
  float getZ() { return m_z;  };
  TH1F* getVP(){ return m_VP; };

  // Fill information
  void fill(float time, float A){
    m_VP->Fill(time, A);
  }

  // Checker
  bool isInitialized(){ return m_initialized; };

  ClassDef(Antenna, 1);

 protected:
  
  // Profile for overall result
  TH1F* m_VP;
  
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
