#include "TetrisGame.h"
#include <cstdlib> 
#include <ctime> 
#include "Line.h"
#include "shape.h"
#include "Square.h"
#include "Bomb.h"
#include "Joker.h"
#include "TShape.h"
#include "ZShape.h"
#include "LShape.h"
void TetrisGame::run()
{
	int score = 0, bodyX, bodyY;
	bool clear = true;
	Menu menu;
	GameBoard gameBoard;
	bool getChar;
	bool stopGame = false;
	bool isHitGround = false;
	int randomNum[NUM_OF_RANDS];
	char keyPressed = 0;
	Point p;
	int counter = 0;
	bool isAbleToMove;

	srand((unsigned)time(0));
	randomNum[0] = (rand() % RAND_RANGE);
	randomNum[1] = 14; //(rand() % RAND_RANGE);

	for (int i = 0; i < NUM_OF_RANDS; i++)
	{
		if (randomNum[i] >= LINE_RANGE_RAND_START && randomNum[i] <= LINE_RANGE_RAND_END)
			randomNum[i] = Shape::LINE;
		else if (randomNum[i] >= SQUARE_RANGE_RAND_START && randomNum[i] <= SQUARE_RANGE_RAND_END)
			randomNum[i] = Shape::SQUARE;
		else if (randomNum[i] >= TSHAPE_RANGE_RAND_START && randomNum[i] <= TSHAPE_RANGE_RAND_END)
			randomNum[i] = Shape::TSHAPE;
		else if (randomNum[i] >= LSHAPE_RANGE_RAND_START && randomNum[i] <= LSHAPE_RANGE_RAND_END)
			randomNum[i] = Shape::LSHAPE; 
		else if (randomNum[i] >= ZSHAPE_RANGE_RAND_START && randomNum[i] <= ZSHAPE_RANGE_RAND_END)
			randomNum[i] = Shape::ZSHAPE; 
		else if (randomNum[i] <= JOKER_RANGE_RAND_START)
			randomNum[i] = Shape::JOKER;
		else
			randomNum[i] = Shape::BOMB;
	}

	while (stopGame == false)
	{
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == Menu::ControlKeys::START)
			{
				PlaySound(TEXT("C:\\MenuSound.wav"), NULL, SND_FILENAME | SND_ASYNC);

				while (clear == true)
				{
					Joker joker(Shape::MATERIAL);
					Square square(Shape::MATERIAL);
					Bomb bomb(Shape::BOMB_MATERIAL);
					tShape t(Shape::ORIGINAL, Shape::MATERIAL);
					zShape z(Shape::ORIGINAL, Shape::MATERIAL);
					lShape l;
					Line line;
    				keyPressed = 0;
					bool pause = 0;
					Sleep(250);
					
					Shape* shape;
					switch (randomNum[0]) 
					{
					case Shape::ShapeType::SQUARE:
					{
						shape = &square;
						break;
					}
					case Shape::ShapeType::LINE:
					{
						shape = &line;
						break;
					}

					case Shape::ShapeType::JOKER:
					{					
						shape = &joker;
						break;
					}

					case Shape::ShapeType::BOMB:
					{
						shape = &bomb;
						break;
					}
					case Shape::ShapeType::TSHAPE:
					{
						shape = &t;
						break;
					}
					case Shape::ShapeType::ZSHAPE:
					{
						shape = &z;
						break;
					}
					case Shape::ShapeType::LSHAPE:
					{
						shape = &l;
						break;
					}
					}
					shape->draw();
					menu.addAndPrintParts();
					menu.printNextShape((int)((Shape::ShapeType)randomNum[1]));

					while (_kbhit()) //in case the last key pressed was S, just when the joker arrived at the bottom
					{
						keyPressed = _getch();
						if (isUpperCase(keyPressed))
							keyPressed = upperToLowerCase(keyPressed);
						if (keyPressed == Shape::JOKERSTOP)
						{
							keyPressed = 0;
						}
						else
						{
							if (MenuKeysManager(&menu, keyPressed, stopGame, clear, pause))
								break;
						}
					}

					while (clear == true)
					{
						if (shape->improveShapeStopReactionTime(getChar, keyPressed, gameBoard, menu, bodyX, bodyY))//This function improves the joker stop ('S') reaction time for better gameplay.
							break;																				   //we decided to make this function generic, in case we will want to add a new shapes
																												   //in the future which will behave similarly to joker
						if (!(shape->move(Shape::DOWN, gameBoard, menu))) //can't move down, there's a shape under.
						{
							if (shape->isGameOver())
							{
								clear = false;
								stopGame = true;
								break;
							}

						shape->cleanRows(gameBoard, menu);
						break;
						}
						else 
							shape->updateBoard(Shape::DOWN,gameBoard, menu); 
						if (shape->hasReachedBottom(gameBoard,menu))
						{
							counter = shape->cleanRows(gameBoard, menu);
							break;
						}
						if (_kbhit() || (getChar == false))
						{
							if (getChar)
							{
								keyPressed = _getch();
								if (isUpperCase(keyPressed))
									keyPressed = upperToLowerCase(keyPressed);
							}

							if (MenuKeysManager(&menu, keyPressed, stopGame, clear, pause))
								break;
							if (keyPressed == Shape::IMMIDIATE_DOWN)
							{
								shape->immidiateDown(gameBoard, menu);
								shape->cleanRows(gameBoard, menu);
								break;
							}
							if (keyPressed == Shape::CHANGER)
							{
								shape->rotateRight(gameBoard, menu);
								shape->updateBoard(keyPressed, gameBoard, menu);

							}
							if ((keyPressed == Shape::LEFT) || (keyPressed == Shape::CHANGER) || (keyPressed == Shape::DOWN) || (keyPressed == Shape::RIGHT))
							{
								isAbleToMove = shape->move((Shape::ARROWS)keyPressed,gameBoard, menu);
								if (isAbleToMove == true)
									shape->updateBoard(keyPressed, gameBoard, menu);    
							}
						}
						Sleep(menu.getSpeedMovement());


					}

					randomNum[0] = randomNum[1];
					randomNum[1] = (rand() % RAND_RANGE);
					if (randomNum[1] >= LINE_RANGE_RAND_START && randomNum[1] <= LINE_RANGE_RAND_END)
						randomNum[1] = Shape::LINE;
					else if (randomNum[1] >= SQUARE_RANGE_RAND_START && randomNum[1] <= SQUARE_RANGE_RAND_END)
						randomNum[1] = Shape::SQUARE;
					else if (randomNum[1] >= TSHAPE_RANGE_RAND_START && randomNum[1] <= TSHAPE_RANGE_RAND_END)
						randomNum[1] = Shape::TSHAPE;
					else if (randomNum[1] >= LSHAPE_RANGE_RAND_START && randomNum[1] <= LSHAPE_RANGE_RAND_END)
						randomNum[1] = Shape::LSHAPE;
					else if (randomNum[1] >= ZSHAPE_RANGE_RAND_START && randomNum[1] <= ZSHAPE_RANGE_RAND_END)
						randomNum[1] = Shape::ZSHAPE;
					else if (randomNum[1] <= JOKER_RANGE_RAND_START)
						randomNum[1] = Shape::JOKER;
					else
						randomNum[1] = Shape::BOMB;
				}


			}
		}
	}
}


bool TetrisGame::MenuKeysManager(Menu *menu, char keyPressed, bool &stopGame, bool& clear, bool& pause)
{
	if (keyPressed == Menu::ControlKeys::EXIT)
	{
		PlaySound(TEXT("C:\\MenuSound.wav"), NULL, SND_FILENAME | SND_ASYNC);

		clear = false;
		stopGame = true;
		return true;
	}
	if (keyPressed == Menu::ControlKeys::SPEED_DOWN)
	{
		menu->speedDownMovement();
		PlaySound(TEXT("C:\\SpeedDown.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	if (keyPressed == Menu::ControlKeys::SPEED_UP)
	{
		menu->speedUpMovement();
		PlaySound(TEXT("C:\\SpeedUp.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	if (keyPressed == Menu::ControlKeys::PAUSE_OR_RESUME)
	{
		if (pause == 0)
		{
			PlaySound(TEXT("C:\\Pause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pause = 1;
		}
		while (pause == 1)
		{
			if (_kbhit())
			{
				keyPressed = _getch();
				if (keyPressed == Menu::ControlKeys::PAUSE_OR_RESUME)
				{
					pause = 0;
					PlaySound(TEXT("C:\\MenuSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
			}
		}
	}
	return false;
}
