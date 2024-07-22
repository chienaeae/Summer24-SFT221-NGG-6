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
            Logger::WriteMessage("In Shipment Test Suite Initialize");
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            Logger::WriteMessage("In Shipment Test Suite Cleanup");
        }

        TEST_METHOD(TestIsValidDest_ValidPoint)
        {
            Shipment shipment = { 10, 20, {10, 10} };
            int result = isValidDest(&shipment);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestIsValidDest_ValidBoundaryPoint)
        {
            Shipment shipment = { 10, 20, {24, 24} };
            int result = isValidDest(&shipment);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestIsValidDest_InvalidRow_Negative)
        {
            Shipment shipment = { 10, 20, {-1, 10} };
            int result = isValidDest(&shipment);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestIsValidDest_InvalidRow_Exceeds)
        {
            Shipment shipment = { 10, 20, {25, 10} };
            int result = isValidDest(&shipment);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestIsValidDest_InvalidCol_Negative)
        {
            Shipment shipment = { 10, 20, {10, -1} };
            int result = isValidDest(&shipment);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestIsValidDest_InvalidCol_Exceeds)
        {
            Shipment shipment = { 10, 20, {10, 25} };
            int result = isValidDest(&shipment);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_WeightLimit)
        {
            struct Truck truck = { 1, {{ {10, 0}, {20, 0}, {30, 0} }, 3, 'A'}, 2400, 50 };
            struct Shipment shipment = { 100, 10, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(100.0, result, 1e-6);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_VolumeLimit)
        {
            struct Truck truck = { 1, {{ {10, 5}, {20, 5}, {30, 5} }, 3, 'A'}, 2000, 90 };
            struct Shipment shipment = { 100, 10, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(100.0, result, 1e-6);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_BothEqual)
        {
            struct Truck truck = { 1, {{ {10, 10}, {20, 20}, {30, 30} }, 3, 'A'}, 2450, 95 };
            struct Shipment shipment = { 50, 5, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(100.0, result, 1e-6);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_NoAdditionalWeight)
        {
            struct Truck truck = { 1, {{ {10, 10}, {20, 20}, {30, 30} }, 3, 'A'}, 2300, 80 };
            struct Shipment shipment = { 0, 20, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(100.0, result, 1e-6);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_NoAdditionalVolume)
        {
            struct Truck truck = { 1, {{ {10, 10}, {20, 20}, {30, 30} }, 3, 'A'}, 2200, 90 };
            struct Shipment shipment = { 300, 0, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(100.0, result, 1e-6);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_EmptyTruck)
        {
            struct Truck truck = { 1, {{ {0, 0} }, 0, 'A'}, 0, 0 };
            struct Shipment shipment = { 0, 0, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(0.0, result, 1e-6);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_ExactCapacity)
        {
            struct Truck truck = { 1, {{ {50, 50} }, 1, 'A'}, 2500, 100 };
            struct Shipment shipment = { 100, 10, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(-1, result, 1e-6);
        }

        TEST_METHOD(TestLimitingFactorWithShipment_OverCapacity)
        {
            struct Truck truck = { 1, {{ {60, 60} }, 1, 'A'}, 2300, 85 };
            struct Shipment shipment = { 300, 20, {0, 0} };
            double result = limitingFactorWithShipment(&truck, &shipment);
            Assert::AreEqual(-1, result, 1e-6);
        }

        TEST_METHOD(TestIsValidWeight_BelowLimit)
        {
            struct Shipment shipment = { 0, 1, {0, 0} };
            Assert::AreEqual(0, isValidWeight(&shipment));
        }

        TEST_METHOD(TestIsValidWeight_AboveLimit)
        {
            struct Shipment shipment = { 2501, 1, {0, 0} };
            Assert::AreEqual(0, isValidWeight(&shipment));
        }

        TEST_METHOD(TestIsValidWeight_Lowerlimit)
        {
            struct Shipment shipment = { 1, 1, {0, 0} };
            Assert::AreEqual(1, isValidWeight(&shipment));
        }

        TEST_METHOD(TestIsValidWeight_Upperlimit)
        {
            struct Shipment shipment = { 2500, 1, {0, 0} };
            Assert::AreEqual(1, isValidWeight(&shipment));
        }

        TEST_METHOD(TestIsValidSize_WithValidSizes)
        {
            struct Shipment shipment;
            shipment = { 1, 1, {0, 0} };
            Assert::AreEqual(1, isValidBoxSize(&shipment));
            shipment = { 1, 3, {0, 0} };
            Assert::AreEqual(1, isValidBoxSize(&shipment));
            shipment = { 1, 5, {0, 0} };
            Assert::AreEqual(1, isValidBoxSize(&shipment));
        }

        TEST_METHOD(TestIsValidSize_WithInvalidSizes)
        {
            struct Shipment shipment;
            shipment = { 1, 0, {0, 0} };
            Assert::AreEqual(0, isValidBoxSize(&shipment));
            shipment = { 1, 2, {0, 0} };
            Assert::AreEqual(0, isValidBoxSize(&shipment));
            shipment = { 1, 4, {0, 0} };
            Assert::AreEqual(0, isValidBoxSize(&shipment));
            shipment = { 1, 6, {0, 0} };
            Assert::AreEqual(0, isValidBoxSize(&shipment));
        }

        TEST_METHOD(TestIsTruckCanShip_Weight)
        {
            struct Truck truck = { 1, {{ {60, 60} }, 1, 1}, WEIGHT_MAX - 200, 0 };

            struct Shipment shipment;
            shipment = { 100, 1, {0, 0} };
            Assert::AreEqual(1, isTruckCanShip(&truck, &shipment));
            shipment = { 200, 1, {0, 0} };
            Assert::AreEqual(1, isTruckCanShip(&truck, &shipment));
            shipment = { 50, 3, {0, 0} };
            Assert::AreEqual(1, isTruckCanShip(&truck, &shipment));
            shipment = { 50, 5, {0, 0} };
            Assert::AreEqual(1, isTruckCanShip(&truck, &shipment));
        }

        TEST_METHOD(TestIsTruckCanShip_Size)
        {
            struct Truck truck = { 1, {{ {60, 60} }, 1, 1}, WEIGHT_MAX - 200, VOLUME_MAX - 125 };

            struct Shipment shipment;
            shipment = { 1, 1, {0, 0} };
            Assert::AreEqual(1, isTruckCanShip(&truck, &shipment));
            shipment = { 1, 3, {0, 0} };
            Assert::AreEqual(1, isTruckCanShip(&truck, &shipment));
            shipment = { 1, 5, {0, 0} };
            Assert::AreEqual(1, isTruckCanShip(&truck, &shipment));
        }
        TEST_METHOD(TestFindTruckForShipment_whitebox1)
        {
            struct Map map = populateMap();
            const int numTrucks = 1;
            struct Truck trucks[numTrucks]; // Array of 3 trucks for testing
            trucks[0].route = getBlueRoute();

            trucks[0].m_weight_capacity = 1400;
            trucks[0].m_volume_capacity = 95;
            struct Shipment shipment;
            shipment.m_weight = 1500; // Example weight
            shipment.m_boxSize = 3;   // Example box size
            shipment.m_dest = { 3, 1 }; // Example destination

            struct Route divertedRoute;
            Assert::AreEqual(-1, findTruckForShipment(&map, trucks, numTrucks, &shipment, &divertedRoute));
        }
        TEST_METHOD(TestFindTruckForShipment_whitebox2)
        {
            struct Map map = populateMap();
            const int numTrucks = 3;
            struct Truck trucks[numTrucks]; // Array of 3 trucks for testing
            trucks[0].route = getBlueRoute();
            trucks[2].route = getGreenRoute();
            trucks[1].route = getYellowRoute();

            trucks[0].m_weight_capacity = 1400;
            trucks[0].m_volume_capacity = 95;
            trucks[1].m_weight_capacity = 250;
            trucks[1].m_volume_capacity = 50;
            trucks[2].m_weight_capacity = 2500;
            trucks[2].m_volume_capacity = 20;

            struct Shipment shipment;
            shipment.m_weight = 1500; // Example weight
            shipment.m_boxSize = 3;   // Example box size
            shipment.m_dest = { 17, 1 }; // Example destination

            struct Route divertedRoute;
            Assert::AreEqual(1, findTruckForShipment(&map, trucks, numTrucks, &shipment, &divertedRoute));
        }
        TEST_METHOD(TestFindTruckForShipment_whitebox3)
        {
            struct Map map = populateMap();
            const int numTrucks = 3;
            struct Truck trucks[numTrucks]; // Array of 3 trucks for testing
            trucks[0].route = getBlueRoute();
            trucks[2].route = getGreenRoute();
            trucks[1].route = getYellowRoute();

            trucks[0].m_weight_capacity = 1900;
            trucks[0].m_volume_capacity = 95;
            trucks[1].m_weight_capacity = 2000;
            trucks[1].m_volume_capacity = 50;
            trucks[2].m_weight_capacity = 1000;
            trucks[2].m_volume_capacity = 98;

            struct Shipment shipment;
            shipment.m_weight = 800; // Example weight
            shipment.m_boxSize = 3;   // Example box size
            shipment.m_dest = { 17, 11 }; // Example destination

            struct Route divertedRoute;
            Assert::AreEqual(-1, findTruckForShipment(&map, trucks, numTrucks, &shipment, &divertedRoute));

        }
        
        TEST_METHOD(TestFindTruckForShipment_whitebox4)
        {
            struct Map map = populateMap();
            const int numTrucks = 3;
            struct Truck trucks[numTrucks]; // Array of 3 trucks for testing
            trucks[0].route = getBlueRoute();
            trucks[2].route = getGreenRoute();
            trucks[1].route = getYellowRoute();

            trucks[0].m_weight_capacity = 100;
            trucks[0].m_volume_capacity = 20;
            trucks[1].m_weight_capacity = 2500;
            trucks[1].m_volume_capacity = 50;
            trucks[2].m_weight_capacity = 1800;
            trucks[2].m_volume_capacity = 60;

            struct Shipment shipment;
            shipment.m_weight = 900; // Example weight
            shipment.m_boxSize = 5;   // Example box size
            shipment.m_dest = { 15, 10 }; // Example destination

            struct Route divertedRoute;
            Assert::AreEqual(0, findTruckForShipment(&map, trucks, numTrucks, &shipment, &divertedRoute));



        }
	};

    TEST_CLASS(MappingTest) 
    {
    public:
        TEST_CLASS_INITIALIZE(ClassInitialize)
        {
            Logger::WriteMessage("In Mapping Test Suite Initialize");
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            Logger::WriteMessage("In Mapping Test Suite Cleanup");
        }

        TEST_METHOD(TestDistance_SamePoint)
        {
            Point p1 = { 0, 0 };
            Point p2 = { 0, 0 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(0.0, result, 1e-6);
        }

        TEST_METHOD(TestDistance_AdjacentPoints)
        {
            Point p1 = { 0, 0 };
            Point p2 = { 0, 1 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(1.0, result, 1e-6);
        }

        TEST_METHOD(TestDistance_Diagonal)
        {
            Point p1 = { 0, 0 };
            Point p2 = { 1, 1 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(sqrt(2.0), result, 1e-6);
        }

        TEST_METHOD(TestDistance_LargeDistance)
        {
            Point p1 = { 0, 0 };
            Point p2 = { 3, 4 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(5.0, result, 1e-6);
        }

        TEST_METHOD(TestDistance_NegativeCoordinates)
        {
            Point p1 = { -1, -1 };
            Point p2 = { -4, -5 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(5.0, result, 1e-6);
        }

        TEST_METHOD(TestDistance_MixedCoordinates)
        {
            Point p1 = { -1, -1 };
            Point p2 = { 1, 1 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(sqrt(8.0), result, 1e-6);
        }

        TEST_METHOD(TestDistance_PositiveCoordinates)
        {
            Point p1 = { 2, 3 };
            Point p2 = { 5, 7 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(5.0, result, 1e-6);
        }

        TEST_METHOD(TestDistance_NonIntegerResult)
        {
            Point p1 = { 1, 2 };
            Point p2 = { 4, 6 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(5.0, result, 1e-6);
        }

        TEST_METHOD(TestDistance_FractionalCoordinates)
        {
            Point p1 = { 0, 0 };
            Point p2 = { 1, 2 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(sqrt(5.0), result, 1e-6);
        }

        TEST_METHOD(TestDistance_ZeroRow)
        {
            Point p1 = { 0, 5 };
            Point p2 = { 0, -5 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(10.0, result, 1e-6);
        }

        TEST_METHOD(TestDistance_ZeroCol)
        {
            Point p1 = { 7, 0 };
            Point p2 = { -7, 0 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(14.0, result, 1e-6);
        }
        TEST_METHOD(TestGetClosestPoint_EmptyRoute)
        {
            Route route = { 0 };
            Point pt = { 0, 0 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(-1, result);
        }

        TEST_METHOD(TestGetClosestPoint_SinglePoint)
        {
            Route route = { {{0, 0}}, 1, 'A' };
            Point pt = { 1, 1 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestGetClosestPoint_MultiplePoints)
        {
            Route route = { {{0, 0}, {1, 1}, {2, 2}}, 3, 'A' };
            Point pt = { 1, 0 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestGetClosestPoint_MultiplePoints_ClosestMiddle)
        {
            Route route = { {{0, 0}, {1, 1}, {2, 2}}, 3, 'A' };
            Point pt = { 1, 1 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestGetClosestPoint_MultiplePoints_ClosestLast)
        {
            Route route = { {{0, 0}, {1, 1}, {2, 2}}, 3, 'A' };
            Point pt = { 3, 3 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(2, result);
        }

        TEST_METHOD(TestGetClosestPoint_LongRoute)
        {
            Route route = {
                {
                    {0, 0}, {1, 2}, {3, 1}, {4, 4}, {5, 0}, {6, 6}, {7, 3}, {8, 8}, {9, 1}, {10, 10},
                    {11, 11}, {12, 2}, {13, 13}, {14, 14}, {15, 5}, {16, 16}, {17, 7}, {18, 18}, {19, 9}, {20, 20}
                },
                20, // numPoints
                'B'
            };
            Point pt = { 10, 9 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(9, result); // Expected to be the closest point to (10, 9)
        }

        TEST_METHOD(TestGetClosestPoint_LongRoute_ExactMatch)
        {
            Route route = {
                {
                    {0, 0}, {1, 2}, {3, 1}, {4, 4}, {5, 0}, {6, 6}, {7, 3}, {8, 8}, {9, 1}, {10, 10},
                    {11, 11}, {12, 2}, {13, 13}, {14, 14}, {15, 5}, {16, 16}, {17, 7}, {18, 18}, {19, 9}, {20, 20}
                },
                20, // numPoints
                'B'
            };
            Point pt = { 7, 3 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(6, result); // Expected to be the exact match point (7, 3)
        }

        TEST_METHOD(TestGetClosestPoint_LongRoute_NoMatch)
        {
            Route route = {
                {
                    {0, 0}, {1, 2}, {3, 1}, {4, 4}, {5, 0}, {6, 6}, {7, 3}, {8, 8}, {9, 1}, {10, 10},
                    {11, 11}, {12, 2}, {13, 13}, {14, 14}, {15, 5}, {16, 16}, {17, 7}, {18, 18}, {19, 9}, {20, 20}
                },
                20, // numPoints
                'B'
            };
            Point pt = { 21, 21 };
            int result = getClosestPoint(&route, pt);
            Assert::AreEqual(19, result); // Expected to be the last point (20, 20)
        }
    };
}
