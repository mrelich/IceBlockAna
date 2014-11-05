#ifndef TreeMaker_h
#define TreeMaker_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Class to produce a rootfile containing the meta-data, the    //
// individual event information, and a summary class containing //
// the average information from the event.                      //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

// My stuff
#include "Event.h"
#include "MetaData.h"
#include "Reader.h"

// Root
#include "TTree.h"
#include "TFile.h"

// standard
#include <iostream>
#include <string>
#include <vector>

class TreeMaker
{

 public:

  // Constructor / Destructor
  TreeMaker(std::string infname,
	    std::string outname);
  virtual ~TreeMaker();

  // Fill Meta Data
  void fillMetaData();

  // Fill Event information
  void fillEvents();

  // Fill summary information
  void fillSummary();

 private:

  Reader* m_reader;   // Object to read in Geant4 output
  TFile* m_outfile;   // Output file for this script

};

#endif
