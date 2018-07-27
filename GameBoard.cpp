#include "gameBoard.h"
#include "Point.h"

void GameBoard::cleanRow(int row)
{
	Point p;
	int i, j;

	//Filling the row with spaces
	for (i = FIRST_COL_GAME; i <= LAST_COL_GAME; i++)
	{
		board[row+ (BOARD_HEIGHT - 1) - LAST_ROW_GAME][i-FIRST_COL_GAME] = 0;
		p.setX(i);
		p.setY(row);
		p.draw(' ');
	}

	//Normalizing the board (need to get rid of the blank row)
	for (i = row; i >= 1+ -((BOARD_HEIGHT - 1) - LAST_ROW_GAME); i--)
	{
		for (j = FIRST_COL_GAME; j <= LAST_COL_GAME; j++)
		{
			board[i + (BOARD_HEIGHT - 1) - LAST_ROW_GAME][j- FIRST_COL_GAME] = board[i +( BOARD_HEIGHT - 1) - LAST_ROW_GAME - 1][j- FIRST_COL_GAME];
			p.setX(j);
			p.setY(i);
			p.draw(board[i + (BOARD_HEIGHT - 1) - LAST_ROW_GAME -1][j - FIRST_COL_GAME]);
		}
	}

}


bool GameBoard::isRowFull(int row) const
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		if (board[row + (BOARD_HEIGHT - 1) - LAST_ROW_GAME][i] == 0)
			return false;
	}
	return true;
}


bool GameBoard::isLegitMove(Point * p, int shapeLen, Point lastPos[MAX_LEN]) const
{
	int i;
	bool selfColide = false;
	for (i = 0; i < shapeLen; i++)
	{
		selfColide = false;
		if (p[i].getY() <= LAST_ROW_GAME && p[i].getY() >= FIRST_ROW_GAME && p[i].getX() >= FIRST_COL_GAME && p[i].getX() <= LAST_COL_GAME)
		{
			if (lastPos == NULL)
			{
				if (board[p[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME)][p[i].getX() - FIRST_COL_GAME] == Shape::MATERIAL)
					return false;
			}
			else //lastpos is not NULL
			{
				for (int j = 0; j < Shape::MAXLEN; j++)
				{
					if ((p[i].getY() == lastPos[j].getY()) && (p[i].getX() == lastPos[j].getX()))
						selfColide = true;
				}
				if (board[p[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME)][p[i].getX() - FIRST_COL_GAME] == Shape::MATERIAL && selfColide == false)
					return false;
			}
			if (p[i].getY() == LAST_ROW_GAME + 1)
				return false;

		}
		else
			return false;

	}
	return true;
}
