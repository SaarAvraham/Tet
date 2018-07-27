#include "TShape.h"

tShape::tShape(ShapeDir shapeDir, char material)
{
	this->shapeDir = shapeDir;
	this->c = material;
	body[0] = { STARTX, STARTY + 1 };

	body[1] = body[0].left();
	body[2] = body[0].up();
	body[3] = body[0].right();
}

void tShape::draw()
{
	if (shapeDir == ORIGINAL)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].right();
		body[2] = body[1].up();
		body[3] = body[1].right();
	}
	else if (shapeDir == CW90)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].down();
		body[2] = body[1].right();
		body[3] = body[1].down();
		
	}
	else if (shapeDir == CW180)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].left();
		body[2] = body[1].down();
		body[3] = body[1].left();
	}
	else//CW270
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].up();
		body[2] = body[1].left();
		body[3] = body[1].up();
	}
	for (size_t i = 0; i <this->getLen(); i++)
	{
		body[i].draw(this->c);
	}
}

bool tShape::move(ARROWS key, GameBoard & gameBoard, Menu & menu)
{
	Point p[MAXLEN] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } }, lastPos[MAXLEN]{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
	int size;

	lastPos[0] = this->body[0];
	lastPos[1] = this->body[1];
	lastPos[2] = this->body[2];
	lastPos[3] = this->body[3];
	switch (key)
	{
	case ARROWS::LEFT:
	{
		p[0].setY(body[0].getY());
		p[1].setY(body[1].getY());
		p[2].setY(body[2].getY());
		p[3].setY(body[3].getY());

		p[0].setX(body[0].getX() - 1);
		p[1].setX(body[1].getX() - 1);
		p[2].setX(body[2].getX() - 1);
		p[3].setX(body[3].getX() - 1);

		size = this->getLen();//this is for isLegitMove "1" CAN NOT replaced with a constant

		if (gameBoard.isLegitMove(p, size, lastPos))
		{
			if (this->body[0].getX() != FIRST_COL_GAME && this->body[3].getX() != FIRST_COL_GAME)
			{
				gotoxy(body[3].getX(), body[3].getY());
				body[3].draw(' ');
				gotoxy(body[2].getX(), body[2].getY());
				body[2].draw(' ');

				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');

				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');

				body[0].setX(body[0].getX() - 1);
			}
		}
		else
			return false;
		break;
	}
	case ARROWS::RIGHT:
	{


		p[0].setY(body[0].getY());
		p[1].setY(body[1].getY());
		p[2].setY(body[2].getY());
		p[3].setY(body[3].getY());

		p[0].setX(body[0].getX() + 1);
		p[1].setX(body[1].getX() + 1);
		p[2].setX(body[2].getX() + 1);
		p[3].setX(body[3].getX() + 1);
		size = this->getLen();//this is for isLegitMove "1" CAN NOT replaced with a constant

		if (gameBoard.isLegitMove(p, size,lastPos))
		{
			if (this->body[0].getX() != LAST_COL_GAME && this->body[3].getX() != LAST_COL_GAME)
			{
				gotoxy(body[3].getX(), body[3].getY());
				body[3].draw(' ');
				gotoxy(body[2].getX(), body[2].getY());
				body[2].draw(' ');

				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');

				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');

				body[0].setX(body[0].getX() + 1);
			}
		}
		else
			return false;
		break;

	}
	case ARROWS::DOWN:
	{
			p[0].setY(body[0].getY() + 1);
			p[1].setY(body[1].getY() + 1);
			p[2].setY(body[2].getY() + 1);
			p[3].setY(body[3].getY() + 1);

			p[0].setX(body[0].getX());
			p[1].setX(body[1].getX());
			p[2].setX(body[2].getX());
			p[3].setX(body[3].getX());
			size = this->getLen();
		if (gameBoard.isLegitMove(p, size, lastPos))
		{
			if (this->body[0].getY() != LAST_ROW_GAME && this->body[3].getY() != LAST_ROW_GAME)
			{
				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');
				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');
				gotoxy(body[2].getX(), body[2].getY());
				body[2].draw(' ');
				gotoxy(body[3].getX(), body[3].getY());
				body[3].draw(' ');

				body[0].setY(body[0].getY() + 1);
				body[1].setY(body[1].getY() + 1);
				body[2].setY(body[2].getY() + 1);
				body[3].setY(body[3].getY() + 1);
			}
		}
		else
			return false;
		break;
	}
	}
	this->draw();
	this->updateBoard(key, gameBoard, menu, lastPos);
	return true;
}

Shape::ShapeDir tShape::getShapeDir() const
{
	return shapeDir;
}

void tShape::rotateRight(GameBoard & gameBoard, Menu &menu)
{
	Point lastPos[TSHAPE_LEN];
	Point pCheck[TSHAPE_LEN];
	for (size_t i = 0; i < TSHAPE_LEN; i++)
		lastPos[i] = body[i];
	for (size_t i = 0; i < TSHAPE_LEN; i++)
		pCheck[i] = body[i];

	for (int i = 0; i < this->getLen(); i++)
	{
		pCheck[i].rotateRight90Point((float)pCheck[1].getX(), (float)pCheck[1].getY());
	}

	if (gameBoard.GameBoard::isLegitMove(pCheck, this->getLen(), lastPos))
	{
		for (int i = 0; i < this->getLen(); i++)
		{
			body[i].draw(' ');
			body[i].rotateRight90Point((float)body[1].getX(), (float)body[1].getY());
		}
		shapeDir = (Shape::ShapeDir) (((int)shapeDir + 1) % NUM_OF_ROTATIONS);
		this->draw();
		this->updateBoard(Shape::CHANGER, gameBoard, menu ,lastPos);
	}
}

void tShape::immidiateDown(GameBoard & gameBoard, Menu & menu)
{
	bool resume = true;

	while (resume == true)
	{
		resume = this->move(Shape::DOWN, gameBoard, menu);
		this->updateBoard(Shape::DOWN, gameBoard, menu);
	}
}

void tShape::updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN]) const
{
	int i;
	if (lastPos != NULL)
	{
		for (i = 0; i < this->getLen(); i++)
			gameBoard.setCell(lastPos[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), lastPos[i].getX() - FIRST_COL_GAME, 0);
	}

	for (i = 0; i < this->getLen(); i++)
		gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
}

bool tShape::hasReachedBottom(GameBoard &gameBoard, Menu& menu) 
{
	if (this->getShapeDir() == Shape::ORIGINAL)
		return (body[0].getY() == LAST_ROW_GAME);
	else if (this->getShapeDir() == Shape::CW90)
		return (body[0].getY() == LAST_ROW_GAME - 2);
	else if (this->getShapeDir() == Shape::CW180)
		return (body[0].getY() == LAST_ROW_GAME - 1);
	else if (this->getShapeDir() == Shape::CW270)
		return (body[0].getY() == LAST_ROW_GAME);
}


bool tShape::isGameOver() const
{
	int y, dummyX;
	this->getBodyCellXY(0, dummyX, y);
	if (y == this->getStartY())
		return true;
	else return false;
}