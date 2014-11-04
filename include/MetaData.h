#ifndef MetaData_h
#define MetaData_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// This is a meta-data class that will be written to the root //
// file for easy readback information.                        //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "TObject.h"

class MetaData : public TObject
{

 public:
  
  // Default constructor / destructor
  MetaData(){};
  virtual ~MetaData(){};

  // Constructor
  MetaData(int nevts, int nprim, int energy,
	   int nSteps, float ss){
    m_nEvents  = nevts;
    m_nPrimary = nprim;
    m_Energy   = energy;
    m_nSteps   = nSteps;
    m_stepSize = ss;
  };

  // Setting
  void setNEvents(int nevts) { m_nEvents  = nevts;  };
  void setNPrimary(int nprim){ m_nPrimary = nprim;  };
  void setEnergy(int energy) { m_Energy   = energy; };
  void setNSteps(int steps)  { m_nSteps   = steps;  };
  void setStepSize(float ss) { m_stepSize = ss;     };

  // Getting
  void getNEvents() { return m_nEvents;  };
  void getNPrimary(){ return m_nPrimary; };
  void getEnergy()  { return m_Energy;   };
  void getNSteps()  { return m_nSteps;   };
  void getStepSize(){ return m_stepSize; };
  
  ClassDef(MetaData, 1);
  
 protected:
  
  // Run parameters
  int m_nEvents; 
  int m_nPrimary; 
  int m_Energy;

  // Timing information
  int m_nSteps;
  float m_stepSize;
  
};

#endif
