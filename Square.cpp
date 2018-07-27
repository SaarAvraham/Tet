#include "Square.h"

Square::Square(char material)
{
	
	this->shapeDir = shapeDir;
	body[0] = { STARTX, STARTY };

	body[1] = body[0].right();
	body[2] = body[1].down();
	body[3] = body[0].down();
}

void Square::draw()
{
	body[0] = { this->body[0].getX(),this->body[0].getY() };
	body[1] = body[0].right();
	body[2] = body[0].down();
	body[3] = body[2].right();

	for (size_t i = 0; i < this->getLen(); i++)
	{
		body[i].draw(this->c);
	}
}

bool Square::move(ARROWS key, GameBoard & gameBoard, Menu& menu)
{
	Point p[4] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
	int size;
	body[0] = { this->body[0].getX(),this->body[0].getY() };
	body[1] = body[0].right();
	body[2] = body[0].down();
	body[3] = body[2].right();
	switch (key)
	{
	case ARROWS::LEFT:
	{

		p[0].setY(body[0].getY());
		p[1].setY(body[2].getY());

		p[0].setX(body[0].getX() - 1);
		p[1].setX(body[2].getX() - 1);
		size = 2;
		if (gameBoard.isLegitMove(p, size))
		{
			if (this->body[0].getX() != FIRST_COL_GAME)
			{
				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');
				gotoxy(body[3].getX(), body[3].getY());
				body[3].draw(' ');
				body[0].setX(body[0].getX() - 1);
				body[2].setX(body[2].getX() - 1);
				body[1].setX(body[0].getX() - 1);
				body[3].setX(body[2].getX() - 1);
			}
		}
		else
			return false;
		break;
	}
	case ARROWS::RIGHT:
	{
		p[0].setY(body[1].getY());
		p[1].setY(body[3].getY());

		p[0].setX(body[1].getX() + 1);
		p[1].setX(body[3].getX() + 1);
		size = 2;
		if (gameBoard.isLegitMove(p, size))
		{
			if (this->body[1].getX() != LAST_COL_GAME)
			{
				gotoxy(body[1].getX(), body[1].getY());
				body[0].draw(' ');
				gotoxy(body[3].getX(), body[3].getY());
				body[2].draw(' ');
				body[0].setX(body[2].getX() + 1);
			}
		}
		else
			return false;
		break;
	}
	case ARROWS::DOWN:
	{
		p[0].setX(body[2].getX());
		p[1].setX(body[3].getX());

		p[0].setY(body[2].getY() + 1);
		p[1].setY(body[3].getY() + 1);
		size = 2;
		if (gameBoard.isLegitMove(p, size))
		{
			if (this->body[2].getY() != LAST_ROW_GAME)
			{
				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');
				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');
				body[0].setY(body[0].getY() + 1);
			}
		}
		else
			return false;
		break;
	}
	}

	this->draw();

	return true;
}


void Square::immidiateDown(GameBoard & gameBoard, Menu& menu)
{
	bool resume = true;
	while (resume == true)
	{
		resume = this->move(Shape::DOWN, gameBoard, menu);
		this->updateBoard(Shape::DOWN, gameBoard, menu);
	}
}

void Square::updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN]) const
{
	int x, y, i;
	switch (keyPressed)
	{
	case Shape::DOWN:
	{
		for (i = 0; i < this->getLen(); i++)
		{
			x = this->body[i].getX() - FIRST_COL_GAME;
			y = this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME);
			gameBoard.setCell(y, x, this->getChar());

		}
		gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 1, this->body[0].getX() - FIRST_COL_GAME, 0);
		gameBoard.setCell(this->body[1].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 1, this->body[1].getX() - FIRST_COL_GAME, 0);

		break;
	}

	case Shape::LEFT:
	{
		for (i = 0; i < this->getLen(); i++)
		{
			gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
		}
		gameBoard.setCell(this->body[1].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[1].getX() - FIRST_COL_GAME + 1, 0);
		gameBoard.setCell(this->body[3].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[3].getX() - FIRST_COL_GAME + 1, 0);
		break;

	}


	case Shape::RIGHT:
	{
		for (i = 0; i < this->getLen(); i++)
		{
			gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());

		}
		gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[0].getX() - FIRST_COL_GAME - 1, 0);
		gameBoard.setCell(this->body[2].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[2].getX() - FIRST_COL_GAME - 1, 0);
		break;
	}
	}
}

bool Square::hasReachedBottom(GameBoard &gameBoard, Menu& menu) 
{
	return (body[0].getY() == LAST_ROW_GAME - 1);
}

bool Square::isGameOver() const
{
	int y, dummyX;
	this->getBodyCellXY(0, dummyX, y);
	if (y == this->getStartY())
		return true;
	else return false;
}