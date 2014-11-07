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
		  int nAnt, int nSteps, float ss,
		  int nbunch, float tOffset){
    m_nEvents  = nevts;
    m_nPrimary = nprim;
    m_Energy   = energy;
    m_nAntenna = nAnt;
    m_nSteps   = nSteps;
    m_stepSize = ss;
    m_nBunches = nbunch;
    m_tOffset  = tOffset;

    print();
  };

  // Print
  void print(){
    std::cout<<std::endl;
    std::cout<<"NEvents:    "<<m_nEvents<<std::endl;
    std::cout<<"NPrimaries: "<<m_nPrimary<<std::endl;
    std::cout<<"Energy:     "<<m_Energy<<std::endl;
    std::cout<<"NTSteps:    "<<m_nSteps<<std::endl;
    std::cout<<"TStep:      "<<m_stepSize<<std::endl;
    std::cout<<"NAntenna:   "<<m_nAntenna<<std::endl;
    std::cout<<"NBunches:   "<<m_nBunches<<std::endl;
    std::cout<<"tOffset:    "<<m_tOffset<<std::endl;
    std::cout<<std::endl;
  };

  // Setting
  void setNEvents(int nevts) { m_nEvents  = nevts;  };
  void setNPrimary(int nprim){ m_nPrimary = nprim;  };
  void setEnergy(int energy) { m_Energy   = energy; };
  void setNSteps(int steps)  { m_nSteps   = steps;  };
  void setStepSize(float ss) { m_stepSize = ss;     };
  void setNAntenna(int nAnt) { m_nAntenna = nAnt;   };
  void setNBunches(int nB)   { m_nBunches = nB;     };
  void setTOffset(float dt)  { m_tOffset  = dt;     };

  // Getting
  int getNEvents()   { return m_nEvents;  };
  int getNPrimary()  { return m_nPrimary; };
  float getEnergy()  { return m_Energy;   };
  int getNSteps()    { return m_nSteps;   };
  float getStepSize(){ return m_stepSize; };
  int getNAntenna()  { return m_nAntenna; };
  int getNBunches()  { return m_nBunches; };
  
 protected:
  
  // Run parameters
  int m_nEvents; 
  int m_nPrimary; 
  float m_Energy;

  // Timing information
  int m_nSteps;
  float m_stepSize;
  
  // Store number of antenna
  int m_nAntenna;

  // Bunch information
  int m_nBunches;
  float m_tOffset;

  ClassDef(MetaData, 1);

};

#endif
