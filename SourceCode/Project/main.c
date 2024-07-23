#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "string.h"
#include "shipment.h"

struct Point toPoint(int row, int col);

struct Truck createTruck(int id, struct Route route, int weight, int volume);

int main(void)
{
	printf("=================\n");
	printf("Seneca Polytechnic Deliveries\n");
	printf("=================\n");

	struct Map map = populateMap();
	struct Truck trucks [6];
	trucks[0] = createTruck(0, getBlueRoute(), 0, 0);
	trucks[1] = createTruck(1, getBlueRoute(), 0, 0);
	trucks[2] = createTruck(2, getGreenRoute(), 0, 0);
	trucks[3] = createTruck(3, getGreenRoute(), 0, 0);
	trucks[4] = createTruck(4, getYellowRoute(), 0, 0);
	trucks[5] = createTruck(5, getYellowRoute(), 0, 0);

	while(1) {
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		int inputWeight;
		int inputSize;
		char inputDestination[10];
		int destRow;
		char destCol;
        if (scanf("%d %d %s", &inputWeight, &inputSize, inputDestination) != 3){
			printf("Unkown input format\n");
			continue;
		}
 		
		if(inputWeight == 0 && inputSize == 0 && strcmp(inputDestination, "x") == 0) {
			break;
		}
		
		if(sscanf(inputDestination, "%d%c", &destRow, &destCol) != 2) {
			printf("Unkown input format\n");
			continue;
		}

		struct Shipment shipment = {inputWeight, inputSize, toPoint(destRow, destCol)};
		if(!isValidDest(&shipment)) {
			printf("Invalid destination\n");
			continue;
		}

		if(!isValidBoxSize(&shipment)) {
			printf("Invalid size\n");
			continue;
		}
		
		if(!isValidWeight(&shipment)) {
			printf("Invalid weight (must be 1-2500 Kg.)\n");
			continue;
		}
		
		
		struct Route diverted = { {0,0}, 0, DIVERSION };
		int idx = findTruckForShipment(&map, trucks, 6, &shipment, &diverted);
		if(idx != -1) {
			trucks[idx].m_weight_capacity += shipment.m_weight;
			trucks[idx].m_volume_capacity += shipment.m_boxSize;
			int i = 0;

#ifdef DEBUG
			struct Map debuggingMap = populateMap();

			if(trucks[idx].route.routeSymbol == BLUE) {
				struct Route route = getBlueRoute();
				debuggingMap = addRoute(&debuggingMap, &route);
				visualizeRoute(&debuggingMap, &diverted, 1, 1);
			}else if(trucks[idx].route.routeSymbol == GREEN){
				struct Route route = getGreenRoute();
				debuggingMap = addRoute(&debuggingMap, &route);
				visualizeRoute(&debuggingMap, &diverted, 1, 1);

			}else if(trucks[idx].route.routeSymbol == YELLOW) {
				struct Route route = getYellowRoute();
				debuggingMap = addRoute(&debuggingMap, &route);
				visualizeRoute(&debuggingMap, &diverted, 1, 1);
			}

			printf("-------------------------------------------\n");
			printf("          debugging information            \n");
			printf("-------------------------------------------\n");
			for(int idx = 0; idx < 6 ; idx ++) {
				printf("%d: %d, %d (weight, volume)", idx, trucks[idx].m_weight_capacity, trucks[idx].m_volume_capacity);
				printf("\t[");
				switch (trucks[idx].route.routeSymbol)
				{
				case BLUE:
					printf("BLUE LINE");
					break;
				case GREEN:
					printf("GREEN LINE");
					break;
				case YELLOW:
					printf("YELLOW LINE");
					break;
				default:
					break;
				}
				printf("]\n");
			}
			printf("\n");
#endif
			printf("Ship on ");
			switch (trucks[idx].route.routeSymbol)
			{
			case BLUE:
				printf("BLUE LINE");
				break;
			case GREEN:
				printf("GREEN LINE");
				break;
			case YELLOW:
				printf("YELLOW LINE");
				break;
			default:
				break;
			}

			if(diverted.numPoints == 0) {
				printf(", no diversion");
			}else {
				printf(", divert: ");
				for(i = 0; i < diverted.numPoints; i ++) {
					printf("%d%c", diverted.points[i].row + 1, diverted.points[i].col + 65);
					if(i != diverted.numPoints - 1) {
						printf(", ");
					}
				}
			}
			printf("\n");			
		} else {
			printf("No available truck\n");
		}
	}

	printf("Thanks for shipping with Seneca Polytechnic!\n");
	return 0;
}

struct Point toPoint(int row, int col) {
	struct Point p = {row - 1, col >= 97 ? col - 97 : col - 65};
	return p;
}


struct Truck createTruck(int id, struct Route route, int weight, int volume) {
	struct Truck truck = {id, route, weight, volume};
	return truck;
}
