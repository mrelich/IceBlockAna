#ifndef Reader_h
#define Reader_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// A class to parse the geant4 output which is in text file //
// format.                                                  //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include <fstream>
#include <string>
#include "TH1F.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include "Event.h"
#include <cmath>

class Reader
{

 public:
  
  // Constructor / Destructor
  Reader(std::string infname);
  virtual ~Reader();

  // Retrieve meta data
  void getMetaData(int &nEvents,     // Number of events for run
		   int &nPrimaries,  // Number of primaries per event
		   float &pEnergy,   // Primary energy
		   int &nAntenna,    // Number of Antennas for this run
		   int &nTSteps,     // Number of timing steps
		   float &tStep,     // Size of timing step
		   int &nbunch,      // Number of bunches simulated
		   float &tOffset);  // Timing offset

  // Retrieve Event info
  void getEventInfo(Event* evt,      // Event to store info
		    int nTimeSteps,  // Number of time steps
		    float timeStep,  // Time step size
		    float scale);    // Scale to bring up to 10^9 particles

  
 protected:
  
  // file object
  std::ifstream m_infile;

  // Store the meta data info for easy 
  // retrieval
  int m_nEvt;
  int m_nPrim;
  int m_nAnt;
  int m_nSteps;
  float m_pEnergy;
  float m_tStep;
  float m_nBunches;
  float m_tOffset;
  
  
};

#endif
