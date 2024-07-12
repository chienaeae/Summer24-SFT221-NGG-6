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
	};

    TEST_CLASS(MappingTest) 
    {
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
