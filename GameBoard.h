#pragma once

#include "shape.h"
#include "gameBoard.h"
#include "Point.h"
#define MAX_LEN 4
#define BOARD_LENGTH 10
#define BOARD_HEIGHT 15

class Shape;

#define SHIFT 3

class GameBoard
{
private:
	char board[15][10] = { 0 };
	char currMovingShape[4] = { 0 };
public:
	void cleanRow(int row);
	bool isRowFull(int row) const;
	bool isLegitMove(Point* p, int shapeLen, Point lastPos[MAX_LEN]=NULL) const;

	bool GameBoard::IsClearForNewShape()
	{
		if (board[STARTY - SHIFT][STARTX] != 0)
			return false;

		return true;
	}
	char getCell(int x, int y) const {return board[x][y];}
	void setCell(int x, int y, char c){board[x][y] = c;}
};