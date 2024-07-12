#define _CRT_SECURE_NO_WARNINGS
#include "shipment.h"

#ifdef _WIN32
#include <conio.h> // Windows 
#else
#include <unistd.h> // Unix
#endif
#include "mapping.h"

const int WEIGHT_MAX = 2500;
const int VOLUME_MAX = 100;


const char LEFT_MOST_ROW = 'A';
const char RIGHT_MOST_ROW = 'Y';
const int TOP_MOST_COL = 1;
const int DOWN_MOST_COL = 25;

const int validBoxSizes[3] = { 1,3,5 };

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


