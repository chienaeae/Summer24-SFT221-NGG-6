#ifdef _WIN32
#include <conio.h> // Windows 
#else
#include <unistd.h> // Unix
#endif
#include "mapping.h"

const double WEIGHT_MAX = 2500;

const int validBoxSizes[3] = {1,3,5};

const char leftMostRow = 'A';
const char rightMostRow = 'Y';
const int TOP_MOST_COL = 1;
const int DOWN_MOST_COL = 25;

struct Shipment {
    int m_weight;
    int m_boxSize;
    struct Point m_dest;
};

struct Truck {
    // 1: blue; 2:green; 3: yellow
    int routeColor;
    struct Route route;
    int m_weight_capacity;
    int m_volume_capacity;
};

/**
 * Function: isValidWeight
 * - Check if the field `m_weight` of the given shipment is valid.
 * 
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @returns - integer, return true if valide, otherwise return false
 */
int isValidWeight(struct Shipment *shipement);

/**
 * Function: isValidWeight
 * - Check if the field `m_boxSize` of the given shipment is valid.
 * 
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @returns - integer, return true if valide, otherwise return false
 */
int isValidBoxSize(struct Shipment *shipement);

/**
 * Function: isValidWeight
 * - Check if the field `m_dest` of the given shipment is valid.
 * 
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @returns - integer, return true if valide, otherwise return false
 */
int isValidDest(struct Shipment *shipement);

/**
 * Function: findTruckForShipment
 * - Finds the best truck for a shipment. It considers both the load on the truck, 
 * the size and weight of the shipment, and the route of the truck to try to place 
 * it on a truck which goes closest to the destination. If there is no truck that 
 * can deliver the shipment, it returns -1.
 * 
 * @param map - the map of the delivery area with buildings on it.
 * @param trcnks - an array of trucks including the route for each of the trucks.
 * @param numTrucks - the number of trucks in the array of trucks.
 * @param shipment - a data structure containing the size and weight of the shipment.
 * @param diverted - a data structure representing the diverted route to the destination (passed by parameter)
 * @returns - integer, representing the index of the truck in the trucks array on which 
 * the shipment should be placed. If no truck can take the shipment, then -1 is returned.
 */
int findTruckForShipment(
    struct Map map, 
    struct Truck trucks[], 
    int numTrucks, 
    struct Shipment shipment, 
    struct Route *diverted
);

/**
 * Function: IsTruckCanShip
 * - Test if a trunck can hold a shipment
 * 
 * @param truck - a truck to test if it can hold anther given shipment 
 * @param shipment - a shipment to add to the truck
 * @returns - integer, representing the result of checking, -1 indicates the shipment
 *  cannot be added to the truck, otherwise it can. 
 */
int isTruckCanShip(struct Truck *truck, struct Shipment *shipment);


/** 
* Function: Print the map usign the symbols as `printMap` and only print one point at a time.
* This function is for debugging
*
* @param baseMap - map to print (required to be a map without any route added)
* @param route - the route used for tracing each move
* @param base1 - if true print row indices from 1 up otherwise 0 up
* @param alphaCols - if true print col header as letters, otherwise numbers
*/
void visualizeRoute(
	const struct Map* baseMap, const struct Route* route, const int base1, const int alphaCols
) {
	int index = 0;
	int i = 0;
	for(i = 0; i < route->numPoints; i ++) {
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
                if(point.row == r-base1 && point.col == c) {
                    printf("%c", '*');
                } else{
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
