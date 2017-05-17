#ifndef WCG4_PHYSLISTCONF
#define WCG4_PHYSLISTCONF
struct WCG4SimConfig {

  const bool doPairProd;
  const bool doMuonIonization;
  const bool doDeltaRays;
  const char* title;

  WCG4SimConfig(bool _pp, bool _mi, bool _dr, char* _title );
  ~WCG4SimConfig();


};

#endif
