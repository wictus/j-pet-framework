#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../../JPetLoggerInclude.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetParamBank/JPetParamBank.h"


class JPetParamManager
{
 public:
  JPetParamManager();
  JPetParamManager(const char* dBConfigFile);

  void getParametersFromDatabase(const int run);
  bool saveParametersToFile(const char* filename);
  bool readParametersFromFile(const char* filename);
  const JPetParamBank& getParamBank() const { return fBank;}
  void clearParameters();

 private:
  std::string generateSelectQuery(std::string table, std::string run_id); 

  void fillAllContainers     (const int p_run_id);
  void fillScintillators     (const int p_run_id);
  void fillPMs               (const int p_run_id);
  void fillFEBs               (const int p_run_id);
  void fillTRBs              (const int p_run_id);
  void fillTOMB              (const int p_run_id);
  void fillScintillatorsTRefs(void);
  void fillPMsTRefs          (void);
  void fillFEBsTRefs          (void);
  void fillTRBsTRefs         (void);

  void fillAllTRefs          (void);


  JPetParamBank fBank;
};

#endif
