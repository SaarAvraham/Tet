#include "shape.h"
#include "Point.h"
#include "TetrisGame.h"
#include "GameBoard.h"
#include <stdbool.h>

Shape::ShapeDir Shape::getShapeDir() const
{
	 return Shape::ORIGINAL; 
}

int Shape::cleanRows(GameBoard & gameBoard, Menu & menu) const
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
		menu.addAndPrintScore(ROW_SCORE + ROW_MULTI_BONUS*(counter));
	return counter;
}



