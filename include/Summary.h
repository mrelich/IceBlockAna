#ifndef Summary_h
#define Summary_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Class to hold the summary information which includes //
// the average vector potential and the electric field  //
// calculated from the vector potential.                //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "TObject.h" 
#include "TH1F.h"
#include <vector>

class Summary : public TObject
{

 public: 
  
  // Constructor / Destructor
  Summary(){
    m_A.clear();
    m_E.clear();
  };
  virtual ~Summary(){
    for(unsigned int i=0; i<m_A.size(); ++i){
      delete m_A.at(i);
      delete m_E.at(i);
    }
  };

  // Add new histograms
  void addA(TH1F* A){ m_A.push_back(A); };
  void addE(TH1F* E){ m_E.push_back(E); };
  
  // Get a histogram
  TH1F* getA(int i){ return m_A.at(i); };
  TH1F* getE(int i){ return m_E.at(i); };

  // Get the vector
  std::vector<TH1F*> getA(){ return m_A; };
  std::vector<TH1F*> getE(){ return m_E; };
  
  // Get length of the vectors
  int getN(){
    if( m_A.size() != m_E.size() ){
      std::cout<<"Error: Vectors not same size"<<std::endl;
      return 0;
    }
    return m_A.size();
  };

 private:

  std::vector<TH1F*> m_A;
  std::vector<TH1F*> m_E;

  ClassDef(Summary,1);

};

#endif
