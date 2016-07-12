#ifndef _JPETANALYSISMODULE_JPETLORCHARGECUT_H_
#define _JPETANALYSISMODULE_JPETLORCHARGECUT_H_

#include "TCanvas.h"
#include "../../JPetTask/JPetTask.h"
#include "../../JPetWriter/JPetWriter.h"
#include <vector>
#include <utility>

class JPetLORChargeCut : public JPetTask
{
public:

  JPetLORChargeCut(const char* name, const char* description, const std::map<int, double>& cuts );
  virtual ~JPetLORChargeCut();
  virtual void exec();
  virtual void init(const JPetTaskInterface::Options& /* opts */);
  virtual void terminate();
  virtual void setWriter(JPetWriter* writer) {
    fWriter = writer;
  }

  
private:
    std::map<int, double> fCuts;
    JPetWriter* fWriter;
};

#endif
