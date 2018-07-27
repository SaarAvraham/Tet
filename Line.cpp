#include "Line.h"
#include "GameBoard.h"
Line::Line(ShapeDir shapeDir, char material)
{
	this->shapeDir = shapeDir;
	this->c = material;
	body[0] = { STARTX, STARTY };

	body[1] = body[0].right();
	body[2] = body[1].right();
	body[3] = body[2].right();
}

void Line::draw() 
{
	if (shapeDir == ORIGINAL)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		for (int i = 1; i <= 3; i++)
			body[i] = body[i - 1].right();
	}
	else if (shapeDir == CW90)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		for (int i = 1; i <= 3; i++)
			body[i] = body[i - 1].down();
	}
	else if (shapeDir == CW180)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		for (int i = 1; i <= 3; i++)
			body[i] = body[i - 1].left();
	}
	else//CW270
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		for (int i = 1; i <= 3; i++)
			body[i] = body[i - 1].up();
	}
	for (size_t i = 0; i <this->getLen(); i++)
	{
		body[i].draw(this->c);
	}
}

bool Line::move(ARROWS key, GameBoard & gameBoard, Menu& menu)
{
	Point p[4] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
	int size;

	switch (key)
	{
	case ARROWS::LEFT:
	{
		if (this->shapeDir == Shape::CW180)
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
		}
		else if (this->shapeDir == Shape::ORIGINAL)
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
		}
		else
		{
			p[0].setY(body[0].getY());
			p[1].setY(body[1].getY());
			p[2].setY(body[2].getY());
			p[3].setY(body[3].getY());

			p[0].setX(body[0].getX() - 1);
			p[1].setX(body[1].getX() - 1);
			p[2].setX(body[2].getX() - 1);
			p[3].setX(body[3].getX() - 1);
			size = this->getLen();//4
		}
		if (gameBoard.isLegitMove(p, size, body))
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

		if (this->shapeDir == Shape::CW180)
		{
			p[0].setX(body[0].getX() + 1);
			p[0].setY(body[0].getY());
			size = 1;//this is for isLegitMove "1" CAN NOT replaced with a constant
		}
		else if (this->shapeDir == Shape::ORIGINAL)
		{
			p[0].setX(body[3].getX() + 1);
			p[0].setY(body[3].getY());
			size = 1;//this is for isLegitMove "1" CAN NOT replaced with a constant
		}
		else
		{
			p[0].setY(body[0].getY());
			p[1].setY(body[1].getY());
			p[2].setY(body[2].getY());
			p[3].setY(body[3].getY());

			p[0].setX(body[0].getX() + 1);
			p[1].setX(body[1].getX() + 1);
			p[2].setX(body[2].getX() + 1);
			p[3].setX(body[3].getX() + 1);
			size = this->getLen();//4
		}

		if (gameBoard.isLegitMove(p, size))
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
		if (this->shapeDir == Shape::CW90)
		{
			p[0].setX(body[3].getX());
			p[0].setY(body[3].getY() + 1);
			size = 1;
		}
		else if (this->shapeDir == Shape::CW270)
		{
			p[0].setX(body[0].getX());
			p[0].setY(body[0].getY() + 1);
			size = 1;
		}
		else
		{
			p[0].setY(body[0].getY() + 1);
			p[1].setY(body[1].getY() + 1);
			p[2].setY(body[2].getY() + 1);
			p[3].setY(body[3].getY() + 1);

			p[0].setX(body[0].getX());
			p[1].setX(body[1].getX());
			p[2].setX(body[2].getX());
			p[3].setX(body[3].getX());
			size = 4;
		}

		if (gameBoard.isLegitMove(p, size))
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
	return true;
}

Shape::ShapeDir Line::getShapeDir() const
{
	return shapeDir;
}


void Line::rotateRight(GameBoard & gameBoard, Menu & menu)
{
	Point p[4] = { 0 };
	int x, y;
	int size;
	y = this->body[0].getY();
	x = this->body[0].getX();
	if (shapeDir == Shape::ORIGINAL)
	{
		p[0].setX(body[0].getX());
		p[1].setX(body[0].getX());
		p[2].setX(body[0].getX());


		p[0].setY(body[0].getY() + 1);
		p[1].setY(body[0].getY() + 2);
		p[2].setY(body[0].getY() + 3);
		size = 3;
		if (gameBoard.GameBoard::isLegitMove(p, size))
		{
			body[1].draw(' ');
			body[2].draw(' ');
			body[3].draw(' ');
			body[1].setX(body[0].getX());
			body[2].setX(body[0].getX());
			body[3].setX(body[0].getX());

			body[1].setY(body[0].getY() + 1);
			body[2].setY(body[0].getY() + 2);
			body[3].setY(body[0].getY() + 3);

			shapeDir = CW90;
			this->draw();

		}
	}
	else if (shapeDir == Shape::CW90)
	{
		p[0].setY(body[0].getY());
		p[1].setY(body[0].getY());
		p[2].setY(body[0].getY());

		p[0].setX(body[0].getX() - 1);
		p[1].setX(body[0].getX() - 2);
		p[2].setX(body[0].getX() - 3);
		size = 3;
		if (gameBoard.GameBoard::isLegitMove(p, size))
		{
			body[1].draw(' ');
			body[2].draw(' ');
			body[3].draw(' ');
			body[1].setY(body[0].getY());
			body[2].setY(body[0].getY());
			body[3].setY(body[0].getY());


			body[1].setX(body[0].getX() - 1);
			body[2].setX(body[0].getX() - 2);
			body[3].setX(body[0].getX() - 3);

			shapeDir = CW180;
			this->draw();

		}


	}
	else if (shapeDir == Shape::CW180)
	{

		p[0].setX(body[0].getX());
		p[1].setX(body[0].getX());
		p[2].setX(body[0].getX());


		p[0].setY(body[0].getY() - 1);
		p[1].setY(body[0].getY() - 2);
		p[2].setY(body[0].getY() - 3);
		size = 3;

		if (gameBoard.GameBoard::isLegitMove(p, size))
		{
			body[1].draw(' ');
			body[2].draw(' ');
			body[3].draw(' ');
			body[1].setX(body[0].getX());
			body[2].setX(body[0].getX());
			body[3].setX(body[0].getX());

			body[1].setY(body[0].getY() - 1);
			body[2].setY(body[0].getY() - 2);
			body[3].setY(body[0].getY() - 3);

			shapeDir = CW270;
			this->draw();
		}
	}
	else//CW270
	{

		p[0].setY(body[0].getY());
		p[1].setY(body[0].getY());
		p[2].setY(body[0].getY());

		p[0].setX(body[0].getX() + 1);
		p[1].setX(body[0].getX() + 2);
		p[2].setX(body[0].getX() + 3);
		size = 3;
		if (gameBoard.GameBoard::isLegitMove(p, size))
		{
			body[1].draw(' ');
			body[2].draw(' ');
			body[3].draw(' ');
			body[1].setY(body[0].getY());
			body[2].setY(body[0].getY());
			body[3].setY(body[0].getY());

			body[1].setX(body[0].getX() + 1);
			body[2].setX(body[0].getX() + 2);
			body[3].setX(body[0].getX() + 3);
			shapeDir = ORIGINAL;
			this->draw();
		}
	}
}
	


void Line::immidiateDown(GameBoard & gameBoard, Menu& menu)
{
	bool resume = true;
	
	while (resume == true)
	{
		resume = this->move(Shape::DOWN, gameBoard, menu);
		this->updateBoard(Shape::DOWN, gameBoard, menu);
	}
}

void Line::updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN]) const
{
	int i;

	int x, y;


	switch (keyPressed)
	{
	case Shape::DOWN:
	{
		if (this->shapeDir == Shape::CW90)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				x = this->body[i].getX() - FIRST_COL_GAME;
				y = this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME);
				gameBoard.setCell(y, x, this->getChar());

			}
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 1, this->body[0].getX() - FIRST_COL_GAME, 0);

		}
		if (this->shapeDir == Shape::CW270)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				x = this->body[i].getX() - FIRST_COL_GAME;
				y = this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME);
				gameBoard.setCell(y, x, this->getChar());

			}
			gameBoard.setCell(this->body[3].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 1, this->body[3].getX() - FIRST_COL_GAME, 0); //was body[0]


		}
		if (this->shapeDir == Shape::ORIGINAL || this->shapeDir == Shape::CW180)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				x = this->body[i].getX() - FIRST_COL_GAME;
				y = this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME);
				gameBoard.setCell(y, x, this->getChar());
				if (this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 1 > 0)
					gameBoard.setCell(y - 1, x, 0);
			}

		}
		break;
	}
	case Shape::LEFT:
	{
		if (this->shapeDir == Shape::CW90 || this->shapeDir == Shape::CW270)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() + 1 - FIRST_COL_GAME, 0);

			}
		}
		else if (this->shapeDir == Shape::ORIGINAL)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
			}
			gameBoard.setCell(this->body[3].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[3].getX() - FIRST_COL_GAME + 1, 0);

		}
		else if (this->shapeDir == Shape::CW180)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());


			}
			gameBoard.setCell(this->body[0].getY() + (BOARD_HEIGHT - 1) - LAST_ROW_GAME, this->body[0].getX() - FIRST_COL_GAME + 1, 0);///// we stopped here 12.1

		}
		break;
	}
	case Shape::RIGHT:
	{
		if (this->shapeDir == Shape::CW90 || this->shapeDir == Shape::CW270)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME - 1, 0);
			}
		}
		else if (this->shapeDir == Shape::ORIGINAL)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
			}
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[0].getX() - FIRST_COL_GAME - 1, 0);

		}
		else if (this->shapeDir == Shape::CW180)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
			}
			gameBoard.setCell(this->body[3].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[3].getX() - FIRST_COL_GAME - 1, 0);
		}
		break;
	}
	case Shape::CHANGER:
	{
		if (this->shapeDir == Shape::CW90)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
			}
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), (this->body[0].getX()) - FIRST_COL_GAME + 1, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), (this->body[0].getX()) - FIRST_COL_GAME + 2, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), (this->body[0].getX()) - FIRST_COL_GAME + 3, 0);
		}

		else if (this->shapeDir == Shape::CW180)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
			}
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) + 1, (this->body[0].getX()) - FIRST_COL_GAME, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) + 2, (this->body[0].getX()) - FIRST_COL_GAME, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) + 3, (this->body[0].getX()) - FIRST_COL_GAME, 0);
		}
		else if (this->shapeDir == Shape::CW270)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
			}
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), (this->body[0].getX()) - FIRST_COL_GAME - 1, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), (this->body[0].getX()) - FIRST_COL_GAME - 2, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), (this->body[0].getX()) - FIRST_COL_GAME - 3, 0);
		}
		else if (this->shapeDir == Shape::ORIGINAL)
		{
			for (i = 0; i < this->getLen(); i++)
			{
				gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
			}
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 1, (this->body[0].getX()) - FIRST_COL_GAME, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 2, (this->body[0].getX()) - FIRST_COL_GAME, 0);
			gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME) - 3, (this->body[0].getX()) - FIRST_COL_GAME, 0);
		}
	}
	break;
	}
}

bool Line::hasReachedBottom(GameBoard &gameBoard, Menu& menu) 
{
	if (this->getShapeDir() == 1) 
		return (body[0].getY() == LAST_ROW_GAME - 3);
	else if (this->getShapeDir() == 3)
		return (body[0].getY() == LAST_ROW_GAME);
	else if (this->getShapeDir() == 0 || this->getShapeDir() == 2)
		return (body[0].getY() == LAST_ROW_GAME);
}

bool Line::isGameOver() const
{
	int y, dummyX;
	this->getBodyCellXY(0, dummyX, y);
	if ( y== this->getStartY())
		return true;
	else return false;
}
