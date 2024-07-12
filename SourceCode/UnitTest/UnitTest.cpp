#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "shipment_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_MODULE_INITIALIZE(ModuleInitialize)
    {
        Logger::WriteMessage("In Module Initialize");
    }

    TEST_MODULE_CLEANUP(ModuleCleanup)
    {
        Logger::WriteMessage("In Module Cleanup");
    }

	TEST_CLASS(ShipmentTest)
	{
	public:
		
        TEST_CLASS_INITIALIZE(ClassInitialize)
        {
            Logger::WriteMessage("In Class Initialize");
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            Logger::WriteMessage("In Class Cleanup");
        }

        TEST_METHOD(ShipmentOneTest)
        {
            Logger::WriteMessage("In ShipmentOneTest test");
            int i = shipmentAdd(1, 2);
            Assert::AreEqual(3, i);
        }
	};

    TEST_CLASS(MappingTest) 
    {
        TEST_CLASS_INITIALIZE(ClassInitialize)
        {
            Logger::WriteMessage("In Class Initialize");
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            Logger::WriteMessage("In Class Cleanup");
        }

        TEST_METHOD(MappingOneTest)
        {
            Logger::WriteMessage("In MappingOneTest test");
            int i = mappingAdd(1, 2);
            Assert::AreEqual(3, i);
        }
    };
}
