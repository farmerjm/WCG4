#ifndef WCG4_SIMMAN
#define WCG4_SIMMAN
#include "common.hh"
#include <vector>
#include <numeric>
#include "WCG4SimConfig.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "WCG4StackingAction.hh"
//#include "TH1D.h"

class WCG4SimManager {
  private:

    unsigned int runID;
    unsigned int numEvents;
    double start, end;

    std::vector<WCG4SimConfig*> configList;
    std::vector<double> VEMList;
    std::vector<double> VEMSigmaList;
    std::vector<std::vector<double> > MuonCurves;
    std::vector<std::vector<double> > MuonCurvesSigma;
    //std::vector<TH1D> histoList;
    
    G4UImanager* UI;
  public:
    WCG4SimManager();
    void SetEndpoints(double _start, double _end) {start=_start; end=_end;};
    void AddConfig(WCG4SimConfig* conf) {configList.push_back(conf);}
    void GenerateStandardConfigs();

    void ConfigureRunPhysics(WCG4SimConfig* theConf);
    void EndRun();

    void CalculateVEM();
    void RunSimAllConfigs(double granularity);
};


#endif
