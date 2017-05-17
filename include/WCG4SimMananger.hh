#ifndef WCG4_SIMMAN
#define WCG$_SIMMAN
#include <vector>
#include "WCG4SimConfig.hh"

class WCG4SimManager {

  public:

    unsigned int runID;
    std::vector<WCG4SimConfig*> configList;
    
  private:
    WCG4SimManager();
    ConfigureRunPhysics();

    RunSim(double granularity);

}

#endif
