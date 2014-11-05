#ifndef MetaData_h
#define MetaData_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// This is a meta-data class that will be written to the root //
// file for easy readback information.                        //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "TObject.h"
#include <iostream>

class MetaData : public TObject
{

 public:
  
  // Default constructor / destructor
  MetaData(){ m_nEvents = 0; };
  virtual ~MetaData(){};

  // Set all variables
  void initialize(int nevts, int nprim, float energy,
		  int nSteps, float ss){
    m_nEvents  = nevts;
    m_nPrimary = nprim;
    m_Energy   = energy;
    m_nSteps   = nSteps;
    m_stepSize = ss;
    std::cout<<"Setting events: "<<m_nEvents<<std::endl;
  };

  // Print
  void print(){
    std::cout<<m_nEvents<<std::endl;
  };

  // Setting
  void setNEvents(int nevts) { m_nEvents  = nevts;  };
  void setNPrimary(int nprim){ m_nPrimary = nprim;  };
  void setEnergy(int energy) { m_Energy   = energy; };
  void setNSteps(int steps)  { m_nSteps   = steps;  };
  void setStepSize(float ss) { m_stepSize = ss;     };

  // Getting
  int getNEvents()   { return m_nEvents;  };
  int getNPrimary()  { return m_nPrimary; };
  float getEnergy()  { return m_Energy;   };
  int getNSteps()    { return m_nSteps;   };
  float getStepSize(){ return m_stepSize; };
  
 protected:
  
  // Run parameters
  int m_nEvents; 
  int m_nPrimary; 
  float m_Energy;

  // Timing information
  int m_nSteps;
  float m_stepSize;
  
  ClassDef(MetaData, 1);

};

#endif
