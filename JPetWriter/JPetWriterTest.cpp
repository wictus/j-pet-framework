#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetWriterTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>  // for filesystem::remove
#include <TNamed.h>
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"
#include "../JPetBaseSignal/JPetBaseSignal.h"
#include "../JPetRawSignal/JPetRawSignal.h"
#include "../JPetRecoSignal/JPetRecoSignal.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetHit/JPetHit.h"
#include "../JPetLOR/JPetLOR.h"
#include "../JPetWriter/JPetWriter.h"
#include "../JPetReader/JPetReader.h"


//  JPetWriter(const char *p_fileName);
//  virtual ~JPetWriter(void);
//
//  template <class T>
//  bool Write(const T& obj);
//  //bool OpenFile(const char* filename);
//  void WriteHeader(TObject* header);
//  inline bool IsOpenFile() const {return fFile.IsOpen();}
//  void closeFile();
//
//  int WriteObject(const TObject* obj, const char* name){ return fFile.WriteObject(obj, name); }
//  

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  JPetWriter writer("test.root");
  BOOST_REQUIRE(writer.isOpen());
  writer.closeFile();
  BOOST_REQUIRE(!writer.isOpen());
}

BOOST_AUTO_TEST_CASE( my_test2 )
{
  std::string fileName = "test2.root";
  JPetWriter writer(fileName.c_str());
  TNamed obj("TNamed", "Title of this testObj");
  writer.write(obj);
  writer.closeFile();
  
  JPetReader reader(fileName.c_str());
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 1);
  TNamed& objOut = (TNamed&)reader.getCurrentEvent();
  BOOST_REQUIRE(std::string(objOut.GetName())=="TNamed");
  BOOST_REQUIRE(std::string(objOut.GetTitle())=="Title of this testObj");
}


/// a tree must have a name if not SetAutoSave makes it crash when when call Branch 
BOOST_AUTO_TEST_CASE( my_helperTest_for_test3 )
{
  std::string fileName = "test3_bis.root";
  TFile file(fileName.c_str(), "RECREATE");
  TTree tree("tree", "tree");  
  tree.SetAutoSave(1000);
  TNamed* filler = 0;
  // cppcheck-suppress nullPointer
  tree.Branch("TNamed", "TNamed", &filler);
  const int kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    TNamed obj("TNamed", Form("Title of this testObj%d",i));
    filler = &obj;
    tree.Fill();
    tree.FlushBaskets();
  }
  std::cout <<std::endl;
  file.Close();
}

BOOST_AUTO_TEST_CASE( my_test3 )
{
  std::string fileName = "test3.root";
  JPetWriter writer(fileName.c_str());
  const int kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    TNamed obj("TNamed", Form("Title of this testObj%d",i));
    if (i%1000==0) std::cout<<"*"<<std::flush;
    writer.write(obj);
  }
  std::cout <<std::endl;
  writer.closeFile();
  
  JPetReader reader(fileName.c_str());
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), kHugeNumberOfObjects);
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    reader.nthEvent(i);
    TNamed& objOut = (TNamed&)reader.getCurrentEvent();
    BOOST_REQUIRE(std::string(objOut.GetName())=="TNamed");
    BOOST_REQUIRE(std::string(objOut.GetTitle())==Form("Title of this testObj%d",i));
  }
}


BOOST_AUTO_TEST_CASE( saving_different_objects1 )
{
  //JPetSigCh testJPetSigCh;
   auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetSigCh testJPetSigCh;
    writer.write(testJPetSigCh);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_CASE( saving_different_objects2 )
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetTimeWindow testJPetTimeWindow;
    writer.write(testJPetTimeWindow);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_CASE( saving_different_objects3 )
{

  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetBaseSignal testJPetBaseSignal;
    writer.write(testJPetBaseSignal);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_CASE( saving_different_objects4 )
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetRawSignal testJPetRawSignal;
    writer.write(testJPetRawSignal);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_CASE( saving_different_objects5 )
{

  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetRecoSignal testJPetRecoSignal;
    writer.write(testJPetRecoSignal);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_CASE( saving_different_objects6 )
{

  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetPhysSignal testJPetPhysSignal;
    writer.write(testJPetPhysSignal);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_CASE( saving_different_objects7 )
{

  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetHit testJPetHit;
    writer.write(testJPetHit);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_CASE( saving_different_objects8 )
{

  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  const auto kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    JPetLOR testJPetLOR;
    writer.write(testJPetLOR);
  }
  if(boost::filesystem::exists(fileTest))
          boost::filesystem::remove(fileTest);
} 

BOOST_AUTO_TEST_SUITE_END()
