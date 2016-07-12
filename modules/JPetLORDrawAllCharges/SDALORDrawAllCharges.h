
#ifndef _JPETANALYSISMODULE_SDALORDRAWALLCHARGES_H_
#define _JPETANALYSISMODULE_SDALORDRAWALLCHARGES_H_

#include "../../JPetTask/JPetTask.h"
#include "TCanvas.h"
#include <map>

class SDALORDrawAllCharges: public JPetTask
{

public:

  SDALORDrawAllCharges(const char* name, const char* description);
  virtual ~SDALORDrawAllCharges();
  virtual void exec();
  virtual void init();
  virtual void terminate();

private:
  // put any custom variables (e.g. histograms) here:
  std::map<int,TH1F*> fChargeHistos;
  std::map<int,std::vector<double> > fCharges;
  double fCharge;
  std::vector<int> fIDs;
  unsigned int fNumberOfPMTs;
  std::string fFileName;
};

#endif

