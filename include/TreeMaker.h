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
#include "Summary.h"

// Root
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH1F.h"

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

  // Calcualte efield -- move to package later
  TH1F* getEfield(TH1F* A, int num);

 private:

  Reader* m_reader;   // Object to read in Geant4 output
  MetaData* m_MD;     // Object for meta data
  TFile* m_outfile;   // Output file for this script

};

#endif
