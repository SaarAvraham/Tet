#pragma once
 
#include "Point.h"
#include "Gotoxy.h"
#include <iostream>
#include "Shape.h"

enum StartPointX { StartPointX=0 };

#define SLEEP 250
#define MIN_SLEEP 77
#define MAX_SLEEP 420
#define SLEEP_CHANGE 120


#define LINE_STRING 5
#define SQUARE_STRING 7
#define JOKER_STRING 2
#define BOMB_STRING 2

#define UPDATE_PARTS 0
#define UPDATE_SCORE 1

#define START_POINT_X  0
#define START_POINT_Y 0

#define PAUSE_RESUME_POINT_X 0
#define PAUSE_RESUME_POINT_Y 1

#define SPEED_UP_POINT_X 18
#define SPEED_UP_POINT_Y 0

#define SPEED_DOWN_POINT_X 18
#define SPEED_DOWN_POINT_Y 1

#define EXIT_POINT_X  34
#define EXIT_POINT_Y 0

#define SCORE_POINT_X 48
#define SCORE_POINT_Y 0

#define SCORE_NUMBER_POINT_X  55
#define SCORE_NUMBER_POINT_Y 0

#define PARTS_POINT_X  48
#define PARTS_POINT_Y 1

#define PARTS_NUMBER_POINT_X 65
#define PARTS_NUMBER_POINT_Y 1


#define NEXT_SHAPE_POINT_X 20
#define NEXT_SHAPE_POINT_Y 5

#define ROW_LENGTH 31

class Shape;

class Menu
{
private:
	int score = 0;
	int partsCounter = 0;
	int delayMovement = SLEEP;


	void printNumber(int x, int y, int& numToPrint, int isParts);
public:
	enum ControlKeys { START = '1', PAUSE_OR_RESUME = '2', SPEED_UP = '3', SPEED_DOWN = '4', EXIT = '9' };
	Menu();
	void addAndPrintScore(const int& scoreToAdd);

	void addAndPrintParts();
	void speedUpMovement();

	void speedDownMovement();

	int getSpeedMovement() { return delayMovement; }

	void printBorders();

	void printNextShape(const int& type);
	void setFontSize(const int& FontSize);
};