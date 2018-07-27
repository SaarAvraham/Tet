#pragma once
#include "shape.h"

#define LINE_LEN 4

class Line : public Shape
{
private:
	ShapeDir shapeDir;
	Point body[LINE_LEN];
	char c = MATERIAL;
	int lineLen = LINE_LEN;
public:
	virtual inline int getLen() const override  {return lineLen;}
	virtual void getBodyCellXY (int index, int &x, int &y) const override
	{
		x = body[index].getX();
		y = body[index].getY();
	}
	Line(ShapeDir shapedir = Shape::ORIGINAL, char material = Shape::MATERIAL);
	virtual void draw() override;
	virtual bool move(ARROWS key, GameBoard& gameBoard, Menu& menu) override;
	Shape::ShapeDir getShapeDir() const;
	virtual void rotateRight(GameBoard & gameBoard, Menu &menu) override;
	virtual void immidiateDown(GameBoard &gameBoard, Menu& menu) override;
	virtual void updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN] = NULL) const override;
	virtual Shape::ShapeType getShapeType() const override { return Shape::LINE; }
	virtual int getStartY() const override { return STARTY; }
	virtual bool hasReachedBottom(GameBoard &gameBoard, Menu& menu)  override;
	virtual inline bool isGameOver() const override;
	~Line() { }

};
