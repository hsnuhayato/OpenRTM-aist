// -*- C++ -*-
/*!
 * @file   DataFlowComponentActionServantTests.cpp
 * @brief  DataFlowComponentActionServant test class
 * @date   $Date$ 
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$ 
 *
 */

/*
 * $Log$
 *
 */

#ifndef DataFlowComponentActionServant_cpp
#define DataFlowComponentActionServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

/*!
 * @class DataFlowComponentActionServantTests class
 * @brief DataFlowComponentActionServant test
 */
namespace DataFlowComponentActionServant
{
  class DataFlowComponentActionServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataFlowComponentActionServantTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    DataFlowComponentActionServantTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~DataFlowComponentActionServantTests()
    {
    }
  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace DataFlowComponentActionServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataFlowComponentActionServant::DataFlowComponentActionServantTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
    bool retcode = runner.run();
    return !retcode;
}
#endif // MAIN
#endif // DataFlowComponentActionServant_cpp
