
#include "Reader.h"

using namespace std;

//-------------------------------------------------------//
// Constructor
//-------------------------------------------------------//
Reader::Reader(string infname) :
  m_nEvt(0),
  m_nPrim(0),
  m_nAnt(0),
  m_nSteps(0),
  m_pEnergy(0.),
  m_tStep(0.)
{

  // Open up the file
  m_infile.open(infname.c_str(), ifstream::in);

  // Read in the first line to store meta data
  char dummy[120];
  m_infile >> dummy 
	   >> m_nEvt
	   >> m_nPrim
	   >> m_pEnergy
	   >> m_nAnt
	   >> m_nSteps
	   >> m_tStep;
  
}

//-------------------------------------------------------//
// Destructor
//-------------------------------------------------------//
Reader::~Reader()
{

  // Close the file
  m_infile.close();  

}


//-------------------------------------------------------//
// Set meta data
//-------------------------------------------------------//
void Reader::getMetaData(int &nEvents, int &nPrimaries,	
			 float &pEnergy, int &nAntenna,
			 int &nTSteps, float &tStep)
{

  // Just set the values from memory
  nEvents    = m_nEvt;
  nPrimaries = m_nPrim;
  pEnergy    = m_pEnergy;
  nAntenna   = m_nAnt;
  nTSteps    = m_nSteps;
  tStep      = m_tStep;

}

//-------------------------------------------------------//
// Retrieve event info
//-------------------------------------------------------//
void Reader::getEventInfo(Event* evt, int nTimeSteps,
			  float stepSize)
{
  
  // Set the kill switches
  string event = "Event:";
  string end   = "End:";
  string ant   = "Antenna:";

  // The variables to be read in
  // Antenna info: 
  //    [1]     -- Number
  //    [3,4,5] -- x,y,z
  //    [6,7,8] -- xr,yr,zr (refracted pts)
  // Vector potential:
  //    [0]     -- Time
  //    [1,2,3] -- Ax, Ay, Az
  const int nPars = 9;
  float vars[nPars];
  
  // Physics vars
  float time = 0;
  float Ax=0, Ay=0, Az=0;
  float x=0, y=0, z=0;
  float xr=0, yr=0, zr=0;
  int nant = 0;

  // Loop
  int counter= 0;
  while( !m_infile.eof() ){
    
    // Specify some generic char vector
    char buf[512];

    // Get the line
    m_infile.getline(buf,512);
    if( string(buf).empty() ) continue;

    // Now parse buffer
    char* tokens[nPars] = {};
    tokens[0] = strtok(buf," ");

    // Check for breaks
    if( event.compare(tokens[0]) == 0 ){
      //cout<<"Have event "<<endl;
      continue;
    }
    
    if( end.compare(tokens[0]) == 0 ){
      //cout<<"End of event"<<endl;
      break;
    }
    
    // If we find antenna, store antenna info
    if( ant.compare(tokens[0]) == 0){
      for(int i=1; i<nPars; ++i){
	vars[i] = atof(strtok(0," "));
      }// end loop over vars
      
      // Create an antenna
      evt->addAnt( new Antenna() );
      
      // Save some vars
      nant = vars[1];
      x    = vars[3];
      y    = vars[4];
      z    = vars[5];
      xr   = vars[6];
      yr   = vars[7];
      zr   = vars[8];
      //cout<<nant<<" "<<x<<" "<<y<<" "<<z<<" "<<xr<<" "<<yr<<" "<<zr<<endl;
      continue;
    }

    counter++;
    //if(counter > 4) continue;

    // Otherwise we have the event information
    time = atof(tokens[0]);
    Ax   = atof(strtok(0," "));
    Ay   = atof(strtok(0," "));
    Az   = atof(strtok(0," "));
    
    // Save the antenna information
    Antenna* antenna = evt->getAnt(nant);
    if( !antenna->isInitialized() )
      antenna->initialize(x,y,z,
			  xr,yr,zr,
			  nTimeSteps, 
			  stepSize,
			  time);

    antenna->fill(time, sqrt(Ax*Ax+Ay*Ay+Az*Az));

  }
  
}
