#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "shipment_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AcceptanceTest
{
    TEST_MODULE_INITIALIZE(ModuleInitialize)
    {
        Logger::WriteMessage("In Module Initialize");
    }

    TEST_MODULE_CLEANUP(ModuleCleanup)
    {
        Logger::WriteMessage("In Module Cleanup");
    }

	TEST_CLASS(R001)
	{
	public:

		TEST_METHOD(TestDestinationWithinDeliveryArea)
		{
			// Arrange
			Shipment shipment;
			shipment.m_dest.row = 10; // Set a valid row within the delivery area
			shipment.m_dest.col = 15; // Set a valid column within the delivery area

			// Act
			int result = isValidDest(&shipment);

			// Assert
			Assert::AreEqual(1, result, L"Destination should be within the delivery area");
		}

		TEST_METHOD(TestDestinationOutOfDeliveryArea)
		{
			// Arrange
			Shipment shipment;
			shipment.m_dest.row = 25; // Set an invalid row outside the delivery area
			shipment.m_dest.col = 15; // Set a valid column within the delivery area

			// Act
			int result = isValidDest(&shipment);

			// Assert
			Assert::AreEqual(0, result, L"Destination should be out of the delivery area");
		}
	};

	TEST_CLASS(R002)
	{
	public:

		TEST_METHOD(TestChooseProperTruckWhenDistanceIsTheSame)
		{
			// Arrange
			Map map = populateMap();
			Route route1 = getBlueRoute();
			Route route2 = getGreenRoute();

			Truck trucks[2] = {
				{1, route1, 1000, 10},
				{2, route2, 1000, 10}
			};

			Shipment shipment;
			shipment.m_dest.row = 9;
			shipment.m_dest.col = 9;
			shipment.m_weight = 500;
			shipment.m_boxSize = 3;

			Route divertedRoute;

			// Act
			int selectedTruckIndex = findTruckForShipment(&map, trucks, 2, &shipment, &divertedRoute);

			// Assert
			Assert::AreEqual(0, selectedTruckIndex, L"The first truck should be selected when distances are the same.");
		}
	};

	TEST_CLASS(R003) {
		TEST_METHOD(TestGetClosestPoint)
		{
			// Arrange
			Route route = getBlueRoute();
			Point destination;
			destination.row = 10;
			destination.col = 9;

			// Act
			int closestPointIndex = getClosestPoint(&route, destination);

			// Assert
			Assert::AreEqual(19, closestPointIndex, L"The closest point index should be 19.");
		}
	};

	TEST_CLASS(R004)
	{
	public:

		TEST_METHOD(TestValidWeight)
		{
			// Arrange
			Shipment shipment;
			shipment.m_weight = 1500; // Set a valid weight within the range

			// Act
			int result = isValidWeight(&shipment);

			// Assert
			Assert::AreEqual(1, result, L"The weight should be valid and within the allowed range.");
		}
	};

	TEST_CLASS(R005) {
	public:

		TEST_METHOD(TestValidBoxSize)
		{
			// Arrange
			Shipment shipment;
			shipment.m_boxSize = 3; // Set a valid box size

			// Act
			int result = isValidBoxSize(&shipment);

			// Assert
			Assert::AreEqual(1, result, L"The box size should be valid and within the allowed sizes.");
		}
	};


	TEST_CLASS(R006) {
	public:
		TEST_METHOD(TestTruckCanShip)
		{
			// Arrange
			Truck truck;
			truck.m_weight_capacity = 1000;
			truck.m_volume_capacity = 50;

			Shipment shipment;
			shipment.m_weight = 500;
			shipment.m_boxSize = 3;

			// Act
			int result = isTruckCanShip(&truck, &shipment);

			// Assert
			Assert::AreEqual(1, result, L"The truck should be able to carry the shipment with the current weight.");
		}

		TEST_METHOD(TestTruckCannotShipOverweight)
		{
			// Arrange
			Truck truck;
			truck.m_weight_capacity = 2400;
			truck.m_volume_capacity = 50;

			Shipment shipment;
			shipment.m_weight = 200;
			shipment.m_boxSize = 3;

			// Act
			int result = isTruckCanShip(&truck, &shipment);

			// Assert
			Assert::AreEqual(0, result, L"The truck should not be able to carry the shipment if the weight exceeds the maximum capacity.");
		}
	};

	TEST_CLASS(R007) {
	public:

		TEST_METHOD(TestFindTruckForShipment)
		{
			// Arrange
			Map map = populateMap();
			Route route1 = getBlueRoute();
			Route route2 = getGreenRoute();

			Truck trucks[2] = {
				{1, route1, 1000, 10},
				{2, route2, 1000, 10}
			};

			Shipment shipment;
			shipment.m_dest.row = 10;
			shipment.m_dest.col = 10;
			shipment.m_weight = 500;
			shipment.m_boxSize = 3;

			Route divertedRoute;

			// Act
			int selectedTruckIndex = findTruckForShipment(&map, trucks, 2, &shipment, &divertedRoute);

			// Assert
			Assert::AreEqual(0, selectedTruckIndex, L"The first truck should be selected for the shipment.");
		}

		TEST_METHOD(TestFindTruckForShipmentNoTruckAvailable)
		{
			// Arrange
			Map map = populateMap();
			Route route1 = getBlueRoute();
			Route route2 = getGreenRoute();

			Truck trucks[2] = {
				{1, route1, 1000, 10},
				{2, route2, 1000, 10}
			};

			Shipment shipment;
			shipment.m_dest.row = 10;
			shipment.m_dest.col = 10;
			shipment.m_weight = 3000;  // Over the maximum weight
			shipment.m_boxSize = 3;

			Route divertedRoute;

			// Act
			int selectedTruckIndex = findTruckForShipment(&map, trucks, 2, &shipment, &divertedRoute);

			// Assert
			Assert::AreEqual(-1, selectedTruckIndex, L"No truck should be available for the shipment.");
		}
	};
}