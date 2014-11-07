
#include "TreeMaker.h"

using namespace std;

//--------------------------------------------------//
// Constructor
//--------------------------------------------------//
TreeMaker::TreeMaker(string infname,
		     string outfname) :
  m_reader(NULL),
  m_outfile(NULL)
{

  // Initialize the reader object
  m_reader = new Reader(infname);

  // Open up an output root file
  m_outfile = new TFile(("rootfiles/"+outfname).c_str(),"recreate");

}

//--------------------------------------------------//
// Destructor
//--------------------------------------------------//
TreeMaker::~TreeMaker()
{

  // Write file
  m_outfile->Write();
  m_outfile->Close();
  
  // Clean up
  delete m_reader;
  delete m_outfile;
  delete m_MD;

}

//--------------------------------------------------//
// Fill Meta Data
//--------------------------------------------------//
void TreeMaker::fillMetaData()
{
  
  // Define the variables to be stored in 
  // meta-data and initialize them.
  int nEvents    = 0;
  int nPrim      = 0;
  float Energy   = 0;
  int nAntenna   = 0;
  int nSteps     = 0;
  float stepSize = 0;
  int nBunch     = 0;
  float tOffset  = 0;

  // Set the meta data
  m_reader->getMetaData(nEvents, nPrim, Energy,
			nAntenna, nSteps, stepSize,
			nBunch, tOffset);
  
  // Create MetaData object
  m_MD = new MetaData();
  m_MD->initialize(nEvents, nPrim, Energy,
		   nAntenna, nSteps, stepSize,
		   nBunch, tOffset);

  // Calculate the scale factor
  m_scale = Options::NParticles / nPrim / Options::NBunches;

  // Write this to the root file
  m_outfile->cd();
  m_MD->Write();
  
}

//--------------------------------------------------//
// Fill Event information tree
//--------------------------------------------------//
void TreeMaker::fillEvents()
{
  
  // Create an event object
  Event* event = new Event();

  // Make the tree for output
  TTree* tree = new TTree("EventInfo","Event Information");
  tree->SetAutoSave(1000000);
  tree->SetMaxTreeSize(3000000000u);
  tree->Branch("event", "Event", &event, 32000, 1);

  // Loop over the number of events and load info
  int nEvents = m_MD->getNEvents();
  for(int iEvt=0; iEvt < nEvents; ++iEvt){

    if( iEvt % 5 == 0 )
      cout<<"Working on Event: "<<iEvt<<endl;

    // Setup even characteristics
    event->reset();
    event->initialize(iEvt);

    // Fill the antennas
    m_reader->getEventInfo(event, 
			   m_MD->getNSteps(),
			   m_MD->getStepSize(),
			   m_scale);
    
    // Fill the event
    tree->Fill();

  }
  
  // Now write the tree and delete
  event->reset();
  m_outfile->cd();
  tree->Write();
  delete tree;

  

}

//--------------------------------------------------//
// Fill Summary info
//--------------------------------------------------//
void TreeMaker::fillSummary()
{

  // For creating the summary histograms we need to 
  // open up the event results from the output file
  TTree* tree = (TTree*) m_outfile->Get("EventInfo");
  Event* event = new Event();
  tree->SetBranchAddress("event", &event);

  // Get number of entries
  int nEnt = tree->GetEntries();

  // Create Summary object 
  Summary* summary = new Summary();

  // Now loop over events and save results
  for(int ent = 0; ent<nEnt; ++ent){
    tree->GetEntry(ent);
    
    // Get antennas
    vector<Antenna*> ants = event->getAnts();

    // Loop over antennas and save results
    for(unsigned int iA=0; iA<ants.size(); ++iA){

      TH1F* A = ants.at(iA)->getVP();

      // For first antenna, just clone it over
      if(ent == 0){
	TString hname = A->GetName();
	summary->addA( (TH1F*) A->Clone((hname+"_avg")) );
	summary->addAngle( atan(ants.at(iA)->getX()/ants.at(iA)->getZ()) );
      }
      else{
	summary->getA(iA)->Add(A);
      }
      
    }// end loop over antennas

  }// end loop over entries
  
  // Delete the event and reset the pointer to the tree
  tree = NULL;
  delete event;

  // Right now the bin content is the total sum over all 
  // the events.  Divide by the number of events to get
  // the average.  Also calculate the electric field
  unsigned int nAnt = summary->getA().size();
  for(unsigned int iA=0; iA<nAnt; ++iA){
    TH1F* A = summary->getA(iA);
    A->Scale(1./nEnt);
    summary->addE( getEfield(A, iA) );
  }

  // Write this object
  m_outfile->cd();
  summary->Write();
  delete summary;

}

//--------------------------------------------------//
// Method to calculate the e-field from vector 
// potential. 
// TODO: Move to tools package
// TODO: Change name of E-field histogram
//--------------------------------------------------//
TH1F* TreeMaker::getEfield(TH1F* A, int num)
{

  // Conversion factor for ns
  float conv = 1; //1e-9;

  // Get the binning information
  float bw   = A->GetBinWidth(1);
  float tmin = A->GetXaxis()->GetXmin() + bw/2.;
  float tmax = A->GetXaxis()->GetXmax() + bw/2.;
  int nebins  = (int) ((tmax-tmin)/bw);

  // Make histogram for E-field
  stringstream name; name << "E_" << num;
  TH1F* E = new TH1F(name.str().c_str(),"",nebins,tmin,tmax);
  E->Sumw2();

  // now loop and calculate the E field
  for(int bin=1; bin<A->GetNbinsX(); ++bin){
    float A0    = A->GetBinContent(bin);
    float A1    = A->GetBinContent(bin+1);
    float A0err = A->GetBinError(bin);
    float A1err = A->GetBinError(bin+1);
    float t0    = A->GetBinCenter(bin);
    float t1    = A->GetBinCenter(bin+1);

    // Get new values including errors.
    // Treat bin-to-bin errors as uncorrelated
    int newbin = E->FindBin((t1+t0)/2.);
    float Evar = (A1-A0)/(bw*conv);
    float Eerr = sqrt(pow(A1err/(bw*conv),2) +
		      pow(A0err/(bw*conv),2));

    // Reset the bin content
    E->SetBinContent(newbin, Evar);
    E->SetBinError(newbin, Eerr);
  }

  return E;
  
}

//###################################################################//
//                              MAIN                                 //
//###################################################################//

int main(int argc, char** argv)
{

  // Define options here
  string input  = "";
  string output = "";

  // Loop over arguments
  for(int i=1; i<argc; ++i){
    if(strcmp(argv[i], "-i") == 0)
      input = argv[++i];
    else if(strcmp(argv[i], "-o") == 0)
      output = argv[++i];
    else{
      cout<<"Option not supported"<<endl;
      cout<<"Job will not run!   "<<endl;
      return 0;
    }
  }// end loop over options

  // Check for empty strings
  if( input.empty() || output.empty() ){
    cout<<endl;
    cout<<"Please specify input name and output"<<endl;
    cout<<"name in order to run script"<<endl;
    cout<<"Script will now exit"<<endl;
    cout<<endl;
    return 0;
  }

  // Output some information
  cout<<endl;
  cout<<"-----------------------------------------------"<<endl;
  cout<<"Input:  "<<input<<endl;
  cout<<"Output: "<<output<<endl;
  cout<<"-----------------------------------------------"<<endl;
  cout<<endl;


  // Create TreeMaker
  TreeMaker* maker = new TreeMaker(input,output);

  // Save Meta Data
  maker->fillMetaData();

  // Get event info
  maker->fillEvents();

  // Set the summary info 
  maker->fillSummary();

  // Clean up
  delete maker;
  return 0;

}
