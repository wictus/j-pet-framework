#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHitTest
#include <boost/test/unit_test.hpp>

#include "../JPetHit/JPetHit.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetHit hit;
  double epsilon = 0.0001;  
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  
  BOOST_REQUIRE_CLOSE(hit.getPosX(),0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPosY(),0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPosZ(),0, epsilon );

  BOOST_REQUIRE_EQUAL(hit.isSignalASet(), false);
  BOOST_REQUIRE_EQUAL(hit.isSignalBSet(), false);
}

BOOST_AUTO_TEST_CASE(consistency_check_test)
{
  JPetPhysSignal leftSignal;
  JPetPhysSignal rightSignal;
  JPetBarrelSlot slot1(43, true, "", 0, 43);
  JPetBarrelSlot slot2(44, true, "", 0, 44);
  JPetPM pmA(JPetPM::SideA, 101, 0, 0, std::pair<float,float>(0,0));
  JPetPM pmB(JPetPM::SideB, 102, 0, 0, std::pair<float,float>(0,0));
  leftSignal.setPM(pmA);
  rightSignal.setPM(pmB);
  
  pmA.setBarrelSlot(slot1);
  pmB.setBarrelSlot(slot1);
  
  JPetHit hit1;
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true ); 
  hit1.setSignalA(leftSignal);
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true );
  hit1.setSignalB(rightSignal);
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true );

  pmB.setBarrelSlot(slot2); // signals come from different barrel slots
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), false );

  pmB.setBarrelSlot(slot1); // everyting conistent again
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true );

  pmB.setSide(JPetPM::SideA); // pmA and pmB are both on side A
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), false );
}

BOOST_AUTO_TEST_CASE(set_get_scalars_test){
  JPetHit hit;
  float time = 0.1;
  float timeDiff = 0.2;
  float timeQual = 0.3;
  float timeDiffQual = 0.4;
  float energy = 0.5;
  float energyQual = 0.6;
  
  hit.setTime(time);
  hit.setQualityOfTime(timeQual);
  hit.setTimeDiff(timeDiff);
  hit.setQualityOfTimeDiff(timeDiffQual);
  hit.setEnergy(energy);
  hit.setQualityOfEnergy(energyQual);

  BOOST_REQUIRE_EQUAL(hit.getTime(), time);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTime(), timeQual);
  BOOST_REQUIRE_EQUAL(hit.getTimeDiff(), timeDiff);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTimeDiff(), timeDiffQual);
  BOOST_REQUIRE_EQUAL(hit.getEnergy(), energy);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfEnergy(), energyQual);
  
}


BOOST_AUTO_TEST_CASE(set_get_objects_test)
{
  TVector3 position(1.0f,2.0f,3.0f);
  JPetPhysSignal leftSignal;
  JPetPhysSignal rightSignal;

  float timeA = 123.0;
  float timeB = 456.0;
  leftSignal.setTime( timeA );
  rightSignal.setTime( timeB );

  int scinID = 42;
  JPetScin scin(scinID);
  JPetBarrelSlot slot;
  JPetPM pmA(JPetPM::SideA, 101, 0, 0, std::pair<float,float>(0,0));
  JPetPM pmB(JPetPM::SideB, 102, 0, 0, std::pair<float,float>(0,0));
  pmA.setBarrelSlot(slot);
  pmB.setBarrelSlot(slot);
  leftSignal.setPM(pmA);
  rightSignal.setPM(pmB);  
  
  JPetHit hit;
  hit.setSignalA( leftSignal );
  hit.setSignalB( rightSignal );

  hit.setScintillator( scin );
  hit.setBarrelSlot( slot );

  BOOST_REQUIRE_EQUAL( hit.getScintillator().getID(), scinID );
  BOOST_REQUIRE_EQUAL( &(hit.getScintillator()), &scin );
  BOOST_REQUIRE_EQUAL( &(hit.getBarrelSlot()), &slot );

  BOOST_REQUIRE_EQUAL( hit.getSignalA().getTime(), timeA );
  BOOST_REQUIRE_EQUAL( hit.getSignalB().getTime(), timeB );

}
BOOST_AUTO_TEST_SUITE_END()
