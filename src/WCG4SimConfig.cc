#include "WCG4SimConfig.hh"


WCG4SimConfig::WCG4SimConfig(bool _pp, bool _mi, bool _dr, char* _title): doPairProd(_pp), doMuonIonization(_mi), doDeltaRays(_dr), title(_title) {
}

WCG4SimConfig::~WCG4SimConfig() {

}
