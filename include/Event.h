#ifndef Event_h
#define Event_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// This class will hold the event information for each antenna //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TObject.h"
#include "Antenna.h"

typedef unsigned int uint;

class Event : public TObject
{

 public:
  
  // Default constructor / destructor
  Event(){ reset(); };
  virtual ~Event(){ reset(); };

  // Constructor
  Event(int evtNum){ m_evtNum = evtNum; };

  // Method to reset event info
  void reset(){
    for(uint i=0; i<m_ants.size(); ++i)
      delete m_ants.at(i);
    m_ants.clear();
    
    m_evtNum = -9999;
  };
  
  // Event num accessors
  void setEvtNum(int num){ m_evtNum = num; };
  int getEvtNum(){ return m_evtNum; };

  // Method to add new antenna
  void addAnt(Antenna* ant){ m_ants.push_back(ant); };

  // Method to access antennas
  Antenna* getAnt(uint iAnt){ return m_ants.at(iAnt); };
  std::vector<Antenna*> getAnts(){ return m_ants; };
  
  ClassDef(Event, 1);

 protected:

  int m_evtNum;                  // Event number
  std::vector<Antenna*> m_ants;   // Antenna objects

};

#endif
