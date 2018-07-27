#include "Bomb.h"

Bomb::Bomb(char material)
{
	body[0] = { STARTX, STARTY };
	material = BOMB_MATERIAL;
}

void Bomb::draw() 
{
	body[0].draw(Shape::BOMB_MATERIAL);
}

bool Bomb::move(ARROWS key, GameBoard & gameBoard, Menu& menu)
{
	int blastCount = 0;
	Point p[BOMB_LEN] = { {0 , 0} };
	int size;
	switch (key)
	{
	case ARROWS::LEFT:
	{
		p[0].setX(body[0].getX() - 1);
		p[0].setY(body[0].getY());
		size = 1;
		if (gameBoard.isLegitMove(p, size))
		{
			if (this->body[0].getX() != FIRST_COL_GAME)
			{
				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');
				body[0] = body[0].left();
				this->draw();

			}
		}
		else if (this->body[0].getX() == FIRST_COL_GAME)
			return true;
		else
			return false;
		break;
	}
	case ARROWS::RIGHT:
	{
		p[0].setX(body[0].getX() + 1);
		p[0].setY(body[0].getY());
		size = 1;
		if (gameBoard.isLegitMove(p, size))
		{
			if (this->body[0].getX() != LAST_COL_GAME)
			{
				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');
				body[0] = body[0].right();
				this->draw();

			}
		}
		else if (this->body[0].getX() == LAST_COL_GAME)
			return true;
		else
			return false;
		break;
	}
	case ARROWS::DOWN:
	{
		p[0].setX(body[0].getX());
		p[0].setY(body[0].getY() + 1);
		size = 1;
		if (gameBoard.isLegitMove(p, size))
		{
			if (this->body[0].getY() != LAST_ROW_GAME)
			{
				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');
				body[0] = body[0].down();
				this->draw();
			}
		}
		else
		{
			blastCount = explodeBomb(gameBoard);
			menu.addAndPrintScore(blastCount * SCORE_PENALTY);
			PlaySound(TEXT("C:\\BombSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return false;
		}
		break;
	}
	}
	return true;
}

void Bomb::immidiateDown(GameBoard & gameBoard, Menu& menu)
{
	int blastCount = 0;
	bool resume = true;
	while (resume == true)
	{
		resume = this->move(Shape::DOWN, gameBoard, menu);
		this->updateBoard(Shape::DOWN, gameBoard, menu);
	}
	blastCount = this->explodeBomb(gameBoard);
	menu.addAndPrintScore(blastCount *SCORE_PENALTY);
	PlaySound(TEXT("C:\\BombSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

int Bomb::explodeBomb(GameBoard & gameBoard)
{
	int size = this->getLen();
	int blastCount = 0, x, y, bodyX, bodyY;
	Point p;
	this->getBodyCellXY(0, bodyX, bodyY);
	for (int i = bodyX - EXPLOSION_RADIUS; i <= bodyX + EXPLOSION_RADIUS; i++)
	{
		for (int j = bodyY - EXPLOSION_RADIUS; j <= bodyY + EXPLOSION_RADIUS; j++)
		{
			p.setX(i);
			p.setY(j);
			if (p.getY() <= LAST_ROW_GAME && p.getY() >= FIRST_ROW_GAME && p.getX() >= FIRST_COL_GAME && p.getX() <= LAST_COL_GAME)
			{
				x = p.getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME);
				y = p.getX() - FIRST_COL_GAME;
				if (gameBoard.getCell(x, y) == Shape::MATERIAL)
					blastCount++;

				x = p.getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME);
				y = p.getX() - FIRST_COL_GAME;
				gameBoard.setCell(x, y, 0);
				p.draw(' ');
			}

		}
	}
	return blastCount;
}

bool Bomb::hasReachedBottom(GameBoard &gameBoard, Menu& menu) 
{
	if (body[0].getY() == LAST_ROW_GAME)
	{
		this->explodeBomb(gameBoard);
		return true;
	}
	else
		return false;
}



