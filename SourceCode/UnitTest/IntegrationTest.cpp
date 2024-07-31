#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "shipment_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTest
{
	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}

	TEST_CLASS(I001)
	{
	public:

		TEST_METHOD(TestRouteClosestDistanceOnRouteA)
		{
			struct Truck truck;
			truck.route = getBlueRoute();
			truck.m_volume_capacity = 50;
			truck.m_weight_capacity = 2000;
			struct Shipment shipment;
			shipment.m_boxSize = 3;
			shipment.m_weight = 500;

			int idx = 0;
			shipment.m_dest = truck.route.points[idx];
			int closestPtIdx = getClosestPoint(&truck.route, shipment.m_dest);
			double routeClosestDistance = distance(&truck.route.points[closestPtIdx], &shipment.m_dest);
			Assert::AreEqual(idx, closestPtIdx, L"Point index check");
			Assert::AreEqual(0.0, routeClosestDistance, L"Distance check");
		}

		TEST_METHOD(TestRouteClosestDistanceOnRouteB)
		{
			struct Truck truck;
			truck.route = getBlueRoute();
			truck.m_volume_capacity = 50;
			truck.m_weight_capacity = 2000;
			struct Shipment shipment;
			shipment.m_boxSize = 3;
			shipment.m_weight = 500;

			int idx = 7;
			shipment.m_dest = truck.route.points[idx];
			int closestPtIdx = getClosestPoint(&truck.route, shipment.m_dest);
			double routeClosestDistance = distance(&truck.route.points[closestPtIdx], &shipment.m_dest);
			Assert::AreEqual(idx, closestPtIdx, L"Point index check");
			Assert::AreEqual(0.0, routeClosestDistance, L"Distance check");
		}

		TEST_METHOD(TestRouteClosestDistanceOnRouteC)
		{
			struct Truck truck;
			truck.route = getBlueRoute();
			truck.m_volume_capacity = 50;
			truck.m_weight_capacity = 2000;
			struct Shipment shipment;
			shipment.m_boxSize = 3;
			shipment.m_weight = 500;

			int idx = 15;
			shipment.m_dest = truck.route.points[idx];
			int closestPtIdx = getClosestPoint(&truck.route, shipment.m_dest);
			double routeClosestDistance = distance(&truck.route.points[closestPtIdx], &shipment.m_dest);
			Assert::AreEqual(idx, closestPtIdx, L"Point index check");
			Assert::AreEqual(0.0, routeClosestDistance, L"Distance check");
		}
	};
	TEST_CLASS(I002)
	{
	public:
		TEST_METHOD(TestRouteClosestDistanceOffRouteA)
		{
			struct Truck truck;
			truck.route = getBlueRoute();
			truck.m_volume_capacity = 50;
			truck.m_weight_capacity = 2000;
			struct Shipment shipment;
			shipment.m_boxSize = 3;
			shipment.m_weight = 500;

			int idx = 0;
			shipment.m_dest = truck.route.points[idx];
			shipment.m_dest.col += 4;
			int closestPtIdx = getClosestPoint(&truck.route, shipment.m_dest);
			double routeClosestDistance = distance(&truck.route.points[closestPtIdx], &shipment.m_dest);
			Assert::AreEqual(idx, closestPtIdx, L"Point index check");
			Assert::AreEqual(4.0, routeClosestDistance, L"Distance check");
		}

		TEST_METHOD(TestRouteClosestDistanceOffRouteB)
		{
			struct Truck truck;
			truck.route = getBlueRoute();
			truck.m_volume_capacity = 50;
			truck.m_weight_capacity = 2000;
			struct Shipment shipment;
			shipment.m_boxSize = 3;
			shipment.m_weight = 500;

			int idx = 7;
			shipment.m_dest = truck.route.points[idx];
			shipment.m_dest.row += 4;
			int closestPtIdx = getClosestPoint(&truck.route, shipment.m_dest);
			double routeClosestDistance = distance(&truck.route.points[closestPtIdx], &shipment.m_dest);
			Assert::AreEqual(idx, closestPtIdx, L"Point index check");
			Assert::AreEqual(4.0, routeClosestDistance, L"Distance check");
		}

		TEST_METHOD(TestRouteClosestDistanceOffRouteC)
		{
			struct Truck truck;
			truck.route = getBlueRoute();
			truck.m_volume_capacity = 50;
			truck.m_weight_capacity = 2000;
			struct Shipment shipment;
			shipment.m_boxSize = 3;
			shipment.m_weight = 500;

			int idx = 15;
			shipment.m_dest = truck.route.points[idx];
			shipment.m_dest.col += 4;
			int closestPtIdx = getClosestPoint(&truck.route, shipment.m_dest);
			double routeClosestDistance = distance(&truck.route.points[closestPtIdx], &shipment.m_dest);
			Assert::AreEqual(idx, closestPtIdx, L"Point index check");
			Assert::AreEqual(4.0, routeClosestDistance, L"Distance check");
		}
	};
}