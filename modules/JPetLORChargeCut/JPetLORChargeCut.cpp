#include "./JPetLORChargeCut.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"

JPetLORChargeCut::~JPetLORChargeCut()
{

}

JPetLORChargeCut::JPetLORChargeCut(const char* name, const char* description, const std::map< int, double >& cuts)
: JPetTask(name, description), fCuts( cuts )
{

}

void JPetLORChargeCut::exec()
{
   const JPetLOR& currentLOR = (JPetLOR&)(*getEvent());
   
   
   std::vector<JPetRecoSignal> signalsInsideLOR;
   
   signalsInsideLOR.push_back( currentLOR.getFirstHit().getSignalA().getRecoSignal() );
   signalsInsideLOR.push_back( currentLOR.getFirstHit().getSignalB().getRecoSignal() );
   signalsInsideLOR.push_back( currentLOR.getSecondHit().getSignalA().getRecoSignal() );
   signalsInsideLOR.push_back( currentLOR.getSecondHit().getSignalB().getRecoSignal() );
   
   bool passedThreshold= true;
   for(unsigned int i = 0; i < signalsInsideLOR.size(); i++ )
   {
      if( signalsInsideLOR[i].getCharge() < fCuts[ signalsInsideLOR[i].getPM().getID() ] )
 	passedThreshold = false;     
   }	
   
   JPetLOR goodLOR = currentLOR;

   if( passedThreshold )
     fWriter->write(goodLOR);
   
}

void JPetLORChargeCut::init(const JPetTaskInterface::Options&)
{
}

void JPetLORChargeCut::terminate()
{
}

