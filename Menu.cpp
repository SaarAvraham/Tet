#include <string>
#include "Menu.h"
#include "TetrisGame.h"
#include <iostream>
#include "shape.h"
using namespace std;
class Shape;
//Function that prints the borders for the tetris' board.
void Menu::printBorders()
{
	int j;

	for (j = FIRST_ROW_GAME; j <= LAST_ROW_GAME; j++)
	{
		gotoxy(FIRST_COL_GAME - 1, j);
		cout << "|";
		gotoxy(LAST_COL_GAME + 1, j);
		cout << "|";
		Sleep(100);
	}

	for (j = FIRST_COL_GAME - 1; j <= LAST_COL_GAME + 1; j++)
	{

			gotoxy(j, LAST_ROW_GAME + 1);
			cout << "-";
			Sleep(30);


	}
}
//This function let the player know what will be the next shape, so he can play with a strategy :)
void Menu::printNextShape(const int& type)
{
	gotoxy(NEXT_SHAPE_POINT_X, NEXT_SHAPE_POINT_Y - 2);
	cout << "Next shape:";
	char spaces[ROW_LENGTH] = { "             " };
	string halfSquare =  "**" ;
	string line =  "****" ;
	string joker =  "*" ;
	string bomb =  "@" ;
	string halfTshpae1 = "  * ";
	string halfTshpae2 = "***";
	string halfZshpae1 = "** ";
	string halfZshpae2 = " **";
	string halfLshpae1 = "* ";
	string halfLshpae2 = "***";
	gotoxy(NEXT_SHAPE_POINT_X, NEXT_SHAPE_POINT_Y);
	cout << spaces;
	gotoxy(NEXT_SHAPE_POINT_X, NEXT_SHAPE_POINT_Y + 1);
	cout << spaces;
	gotoxy(NEXT_SHAPE_POINT_X, NEXT_SHAPE_POINT_Y);
	switch (type)
	{
	case Shape::SQUARE:
	{
		cout<<halfSquare;
		gotoxy(NEXT_SHAPE_POINT_X, NEXT_SHAPE_POINT_Y + 1);
		cout << halfSquare;
		break;
	}
	case Shape::LINE:
	{
		cout << line;
		break;
	}
	case Shape::JOKER:
	{
		cout << joker;
		break;
	}
	case Shape::BOMB:
	{
		cout << bomb;
		break;
	}
	case Shape::TSHAPE:
	{
		cout << halfTshpae1;
		gotoxy(NEXT_SHAPE_POINT_X + 1 , NEXT_SHAPE_POINT_Y + 1);
		cout << halfTshpae2;
		break;

	}
	case Shape::LSHAPE:
	{
		cout << halfLshpae1;
		gotoxy(NEXT_SHAPE_POINT_X, NEXT_SHAPE_POINT_Y + 1);
		cout << halfLshpae2;
		break;
	}
	case Shape::ZSHAPE:
	{
		cout << halfZshpae1;
		gotoxy(NEXT_SHAPE_POINT_X, NEXT_SHAPE_POINT_Y + 1);
		cout << halfZshpae2;
		break;
	}
	}
}

//This helps the game look more convincing, yet we stiil use the 10x15 board!
void Menu::setFontSize(const int& FontSize)
{

	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}


void Menu::printNumber(int x, int y, int& numToPrint, int isParts)
{
	char numberString[ROW_LENGTH];
	char spaces[ROW_LENGTH] = { "          " };
	if (isParts == UPDATE_PARTS)
	{
		gotoxy(PARTS_NUMBER_POINT_X, PARTS_NUMBER_POINT_Y);
	}
	else gotoxy(SCORE_NUMBER_POINT_X, SCORE_NUMBER_POINT_Y);
	cout << spaces;
	sprintf_s(numberString, "%d", numToPrint);
	gotoxy(x, y);
	cout << numberString;
}

Menu::Menu()
{
	score = 0;
	partsCounter = 0;
	this->setFontSize(20);

	gotoxy(START_POINT_X, START_POINT_Y);
	cout << "(1) Start ";

	gotoxy(PAUSE_RESUME_POINT_X, PAUSE_RESUME_POINT_Y);
	cout << "(2) Pause/Resume ";

	gotoxy(SPEED_UP_POINT_X, SPEED_UP_POINT_Y);
	cout << "(3) Speed Up ";

	gotoxy(SPEED_DOWN_POINT_X, SPEED_DOWN_POINT_Y);
	cout << "(4) Speed Down ";

	gotoxy(EXIT_POINT_X, EXIT_POINT_Y);
	cout << "(9) Exit ";

	gotoxy(SCORE_POINT_X, SCORE_POINT_Y);
	cout << "Score: ";

	printNumber(SCORE_NUMBER_POINT_X, SCORE_NUMBER_POINT_Y, score, UPDATE_SCORE);

	gotoxy(PARTS_POINT_X, PARTS_POINT_Y);
	cout << "Number of Parts: ";

	printNumber(PARTS_NUMBER_POINT_X, PARTS_NUMBER_POINT_Y, partsCounter, UPDATE_PARTS);
	printBorders();

}
	void Menu::addAndPrintScore(const int& scoreToAdd)
	{
		if (score + scoreToAdd >= 0)
			score = score + scoreToAdd;
		else
			score = 0;
		printNumber(SCORE_NUMBER_POINT_X, SCORE_NUMBER_POINT_Y, score, UPDATE_SCORE);
	}

	void Menu::addAndPrintParts()
	{
		partsCounter++;
		printNumber(PARTS_NUMBER_POINT_X, PARTS_NUMBER_POINT_Y, partsCounter, UPDATE_PARTS);
	}
	void Menu::speedUpMovement()
	{
		if (delayMovement - SLEEP_CHANGE >= MIN_SLEEP)
			delayMovement -= SLEEP_CHANGE;
		else delayMovement = MIN_SLEEP;
	} //limit unwanted abuse speeds such as "negative" or "too much"

	void Menu::speedDownMovement()
	{
		if (delayMovement + SLEEP_CHANGE <= MAX_SLEEP)
			delayMovement += SLEEP_CHANGE;
		else delayMovement = MAX_SLEEP;

	} //limit unwanted abuse speeds such as "negative" or "too much"