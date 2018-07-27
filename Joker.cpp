#include "Joker.h"

Joker::Joker(char material)
{
	body[0] = { STARTX, STARTY };
	material = MATERIAL;
}

void Joker::draw() 
{
	body[0].draw(material);
}

bool Joker::move(ARROWS key, GameBoard & gameBoard, Menu& menu) 
{
	Point p[JOKER_LEN] = { {0 , 0} };
	switch (key)
	{
	case ARROWS::LEFT:
	{

		if (this->body[0].getX() != FIRST_COL_GAME)
		{
			gotoxy(body[0].getX(), body[0].getY());
			body[0].draw(' ');
			body[0] = body[0].left();

			gotoxy(this->body[0].getX() + 1, this->body[0].getY());
			p[0].setX(this->body[0].getX() + 1);
			p[0].setY(this->body[0].getY());
			p[0].draw(gameBoard.getCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[0].getX() - FIRST_COL_GAME + 1));
		}


		break;
	}
	case ARROWS::RIGHT:
	{

		if (this->body[0].getX() != LAST_COL_GAME)
		{
			gotoxy(body[0].getX(), body[0].getY());
			body[0].draw(' ');
			body[0] = body[0].right();

			gotoxy(this->body[0].getX() - 1, this->body[0].getY());
			p[0].setX(this->body[0].getX() - 1);
			p[0].setY(this->body[0].getY());
			p[0].draw(gameBoard.getCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[0].getX() - FIRST_COL_GAME - 1));
		}

		break;
	}
	case ARROWS::DOWN:
	{

		if (this->body[0].getY() != LAST_ROW_GAME)
		{
			gotoxy(body[0].getX(), body[0].getY());
			body[0].draw(' ');
			body[0] = body[0].down();

			gotoxy(this->body[0].getX(), this->body[0].getY() - 1); 
			p[0].setX(this->body[0].getX());
			p[0].setY(this->body[0].getY());
			p[0].draw(gameBoard.getCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME - 1), this->body[0].getX() - FIRST_COL_GAME));

			gotoxy(this->body[0].getX(), this->body[0].getY() - 1);
			p[0].setX(this->body[0].getX());
			p[0].setY(this->body[0].getY() - 1);
			p[0].draw(gameBoard.getCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME - 1), this->body[0].getX() - FIRST_COL_GAME));
		}

		break;
	}
	}
	this->draw();
	return true;
}

void Joker::immidiateDown(GameBoard & gameBoard, Menu& menu)
{
	bool resume = true;
	this->body[0].draw(' ');
	this->body[0].setY(LAST_ROW_GAME);
	this->updateBoard(Shape::JOKERSTOP, gameBoard, menu);	
	this->draw();
	this->cleanRows(gameBoard, menu);
}

void Joker::updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN]) const
{
	if (keyPressed == Shape::JOKERSTOP)
	{
		gameBoard.setCell(this->body[0].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[0].getX() - FIRST_COL_GAME, Shape::MATERIAL); //was body[0]
	}
}

bool Joker::hasReachedBottom(GameBoard &gameBoard, Menu& menu) 
{
	int bodyX, bodyY;
	if (body[0].getY() == LAST_ROW_GAME)
	{
		this->updateBoard(Shape::JOKERSTOP, gameBoard, menu);
		this->getBodyCellXY(0, bodyX, bodyY);
		if (gameBoard.isRowFull(bodyY))
		{
			menu.addAndPrintScore(JOKER_ROW_SCORE);
			PlaySound(TEXT("C:\\PointSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gameBoard.cleanRow(LAST_ROW_GAME);
		}
	}
	return (body[0].getY() == LAST_ROW_GAME);
}

int Joker::cleanRows(GameBoard & gameBoard, Menu & menu) const
{
	int bodyX, bodyY;
	int counter = 0;
	for (int i = 0; i < this->getLen(); i++)
	{
		this->getBodyCellXY(i, bodyX, bodyY);
		if (gameBoard.isRowFull(bodyY))
		{
			counter++;
			PlaySound(TEXT("C:\\PointSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gameBoard.cleanRow(bodyY);
		}
	}
	counter--;
	if (counter >= 0)
		menu.addAndPrintScore(JOKER_ROW_SCORE + ROW_MULTI_BONUS*(counter));
	return counter;
}

bool Joker::improveShapeStopReactionTime(bool & getChar, char & keyPressed, GameBoard & gameBoard, Menu & menu, int & bodyX, int & bodyY) const
{
	getChar = true;
	if (_kbhit())
	{
		keyPressed = _getch();
		if (isUpperCase(keyPressed))
			keyPressed = upperToLowerCase(keyPressed);
		if (keyPressed == Shape::JOKERSTOP)
		{
			this->updateBoard(keyPressed, gameBoard, menu);
			this->getBodyCellXY(0, bodyX, bodyY);
			if (gameBoard.isRowFull(bodyY))
			{
				this->getBodyCellXY(0, bodyX, bodyY);
				gameBoard.cleanRow(bodyY);
				menu.addAndPrintScore(JOKER_ROW_SCORE);
				PlaySound(TEXT("C:\\PointSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			getChar = true;
			return true;
		}
		else
		{
			getChar = false;
			return false;
		}
	}
}


