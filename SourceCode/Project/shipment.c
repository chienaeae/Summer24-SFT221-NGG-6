#define _CRT_SECURE_NO_WARNINGS
#include "shipment.h"
#include <stdio.h>

#ifdef _WIN32
#include <conio.h> // Windows 
#else
#include <unistd.h> // Unix
#endif
#include <float.h>
#include "mapping.h"

const int WEIGHT_MAX = 2500;
const int VOLUME_MAX = 100;
const char MAX_ROW = 24;
const char MAX_COL = 24;

const int validBoxSizes[3] = { 1,3,5 };

int isValidDest(struct Shipment* shipement) {
	// check row
	if (shipement->m_dest.row < 0 || shipement->m_dest.row > MAX_ROW) {
		return 0;
	}
	// check column
	else if (shipement->m_dest.col < 0 || shipement->m_dest.col > MAX_COL) {
		return 0;
	}
	else {
		return 1;
	}
}

double limitingFactorWithShipment(struct Truck* truck, struct Shipment* withShipment) {
	int newWeight = truck->m_weight_capacity + withShipment->m_weight;
	int newVolume = truck->m_volume_capacity + withShipment->m_boxSize;

	// Calculate the weight and volume percentages
	double weightPercentage = (double)newWeight / WEIGHT_MAX * 100.0;
	double volumePercentage = (double)newVolume / VOLUME_MAX * 100.0;

	if (weightPercentage > 100 || volumePercentage > 100) return -1;
	// Return the higher percentage as the limiting factor
	return (weightPercentage > volumePercentage) ? weightPercentage : volumePercentage;
}

void visualizeRoute(
	const struct Map* baseMap, const struct Route* route, const int base1, const int alphaCols
) {
	int index = 0;
	int i = 0;
	for (i = 0; i < route->numPoints; i++) {
		struct Point point = route->points[i];
		// clear console
#ifdef _WIN32
		system("cls");
#else
		printf("\e[1;1H\e[2J");
#endif

		printf("Current Point: (%d:%d)\n", point.row, point.col);

		//              01234567890123456
		//              1248F
		char sym[] = { " XB?G?.?Y?-?*?+?P" };
		int r, c, rowMax;

		rowMax = baseMap->numRows + base1;

		printf("%4s", " ");
		for (c = 0; c < baseMap->numCols; c++)
		{
			if (alphaCols) printf("%c", 'A' + c);
			else printf("%d", c % 10);
		}
		printf("\n");
		printf("%4s", " ");
		for (c = 0; c < baseMap->numCols; c++)
		{
			printf("-");
		}
		printf("\n");

		for (r = base1; r < rowMax; r++)
		{
			printf("%3d|", r);
			for (c = 0; c < baseMap->numCols; c++)
			{
				if (point.row == r - base1 && point.col == c) {
					printf("%c", '*');
				}
				else {
					printf("%c", sym[baseMap->squares[r - base1][c]]);
				}
			}
			printf("\n");
		}
		printf("Press enter to see the next move: ");

		// Wait fot console input
#ifdef _WIN32
		while (_getch() != '\r');
#else
		while (getchar() != '\n');
#endif
	}
}

int isValidWeight(struct Shipment* shipement)
{
	if (shipement->m_weight >= 1 && shipement->m_weight <= 2500)
	{
		return 1;
	}
	return 0;
}


int isValidBoxSize(struct Shipment* shipement)
{
	if (shipement->m_boxSize == 1 || shipement->m_boxSize == 3 || shipement->m_boxSize == 5)
	{
		return 1;
	}
	return 0;
}

int isTruckCanShip(struct Truck* truck, struct Shipment* shipment)
{
	if (truck->m_weight_capacity + shipment->m_weight > WEIGHT_MAX)
	{
		return 0;
	}
	if (truck->m_volume_capacity + shipment->m_boxSize > VOLUME_MAX)
	{
		return 0;
	}
	return 1;
}

int findTruckForShipment(
	struct Map* map,
	struct Truck trucks[],
	int numTrucks,
	struct Shipment* shipment,
	struct Route* diverted
)
{
	int selected = -1;
	double selectedDist = DBL_MAX;
	int selectedClosestPtIdx = -1;
	for (int i = 0; i < numTrucks; i++)
	{
		if(!isTruckCanShip(&trucks[i], shipment)) {
			continue;
		}

		int closestPtIdx = getClosestPoint(&trucks[i].route, shipment->m_dest);
		if(closestPtIdx == -1) {
			continue;
		}

		double routeClosestDistance = distance(&trucks[i].route.points[closestPtIdx], &shipment->m_dest);

		if(selectedDist > routeClosestDistance) {
			selected = i;
			selectedDist = routeClosestDistance;
			selectedClosestPtIdx = closestPtIdx;
			
		}
	}

	if (selected != -1 && selectedDist > 0)
	{
		*diverted = shortestPathBFS(map, trucks[selected].route.points[selectedClosestPtIdx], shipment->m_dest);
	}


	return selected;
}