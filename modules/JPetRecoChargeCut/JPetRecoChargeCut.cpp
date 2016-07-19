#include "./JPetRecoChargeCut.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"

JPetRecoChargeCut::~JPetRecoChargeCut()
{

}

JPetRecoChargeCut::JPetRecoChargeCut(const char* name, const char* description, const std::map< int, double >& cuts)
: JPetTask(name, description), fCuts( cuts )
{

}

void JPetRecoChargeCut::exec()
{
   const JPetRecoSignal& currentReco = (JPetRecoSignal&)(*getEvent());
   
   bool passedThreshold = true;

   if( currentReco.getCharge() < fCuts[ currentReco.getPM().getID() ] )
 	passedThreshold = false;     
   	
   
   if( passedThreshold )
     fWriter->write(currentReco);
   
}

void JPetRecoChargeCut::init(const JPetTaskInterface::Options&)
{
}

void JPetRecoChargeCut::terminate()
{
}

