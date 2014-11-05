#ifndef Antenna_h
#define Antenna_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Antenna class to hold the information about the antenna   //
// position, vector potential, and also some convenient info //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TH1F.h"
#include "TObject.h"
#include <sstream>

class Antenna : public TObject
{

 public:

  // Default constructor / destructor
  Antenna(){ reset(); };
  virtual ~Antenna(){ reset(); };

  // Constructor
  void initialize(float x, float y, float z,
		  int nSteps, float stepSize,
		  float startTime)
  {
    // Set Pos
    this->setPos(x,y,z);
    
    // Hist name
    std::stringstream name;
    name << "Ant_" << x << "_" 
	 << y <<  "_" << z;
    
    // Hist min max
    float tmin = startTime - stepSize/2.;
    float tmax = tmin + nSteps * stepSize;
    this->m_VP = new TH1F(name.str().c_str(),"",
			  nSteps,tmin,tmax);
  };

  // Method to reset vars
  void reset(){
    if( m_VP ) delete m_VP;
    m_VP = NULL;

    m_x = 0;
    m_y = 0;
    m_z = 0;
  };

  // Setting
  void setPos(float x, float y, float z){
    m_x = x; m_y = y; m_z = z;
  };
  void setX(float x){ m_x = x; };
  void setY(float y){ m_y = y; };
  void setZ(float z){ m_z = z; };
  
  // Getting
  float getX() { return m_x;  };
  float getY() { return m_y;  };
  float getZ() { return m_z;  };
  TH1F* getVP(){ return m_VP; };

  ClassDef(Antenna, 1);

 protected:
  
  // Profile for overall result
  TH1F* m_VP;
  
  // Position 
  float m_x;
  float m_y;
  float m_z;


};

#endif
