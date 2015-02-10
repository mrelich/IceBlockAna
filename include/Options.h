#ifndef Options_h
#define Options_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Specify the constants that are going to be used //
// in the experiment.  For example fixing the beam //
// parameters.                                     //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

namespace Options
{

  const int NParticles = 1e9;      // 10^9 particles in one shot
  //const int NBunches   = 5;        // Number of bunches
  const float BunchOffset = 0.350; // ns

};

#endif
