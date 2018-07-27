#pragma once

#include "shape.h"
#include "Point.h"

#define ZSHAPE_LEN 4

class zShape : public Shape
{
private:
	ShapeDir shapeDir = Shape::ORIGINAL;
	Point body[ZSHAPE_LEN];
	char c = MATERIAL;
	int zShapeLen = ZSHAPE_LEN;
public:
	virtual inline int getLen() const override{return zShapeLen;}
	virtual void getBodyCellXY(int index, int &x, int &y) const override
	{
		x = body[index].getX();
		y = body[index].getY();
	}
	zShape(ShapeDir shapeDir = Shape::ORIGINAL, char material = Shape::MATERIAL);
	virtual void draw() override;
	virtual bool move(ARROWS key, GameBoard& gameBoard, Menu& menu) override;
	Shape::ShapeDir getShapeDir() const;
	virtual void rotateRight(GameBoard & gameBoard, Menu &menu) override;
	virtual void immidiateDown(GameBoard &gameBoard, Menu& menu) override;
	virtual void updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN] = NULL) const override;
	virtual Shape::ShapeType getShapeType() const override { return Shape::ZSHAPE; }
	virtual int getStartY() const override { return STARTY + 1; }
	virtual bool hasReachedBottom(GameBoard &gameBoard, Menu& menu) override;
	virtual bool isGameOver() const override;
	~zShape() { }
};
