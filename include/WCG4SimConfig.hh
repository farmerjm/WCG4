#ifndef WCG4_PHYSLISTCONF
#define WCG4_PHYSLISTCONF
struct WCG4PhysListConfig {
private:

  const bool doPairProd;
  const bool doMuonIonization;
  const bool doDeltaRays;
  const char* title;

public:
  WCG4PhysListConfig(bool _pp, bool _mi, bool _dr, char* _title ) : doPairProd(_pp), doMuonIonization(_mi), doDeltaRays(_dr), title(_title);
  ~WCG4PhysListConfig();


};

#endif
