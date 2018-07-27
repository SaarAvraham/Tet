#pragma once

#include "shape.h"
#include "Point.h"

#define LSHAPE_LEN 4

class lShape : public Shape
{
private:
	ShapeDir shapeDir = Shape::ORIGINAL;
	Point body[LSHAPE_LEN];
	char c = MATERIAL;
	int lShapeLen = LSHAPE_LEN;
public:
	inline int getLen() const override{return lShapeLen;}
	virtual void getBodyCellXY(int index, int &x, int &y) const override
	{
		x = body[index].getX();
		y = body[index].getY();
	}
	lShape(ShapeDir shapeDir = Shape::ORIGINAL, char material = Shape::MATERIAL);
	virtual void draw() override;
	bool move(ARROWS key, GameBoard& gameBoard, Menu& menu);
	Shape::ShapeDir getShapeDir() const;
	virtual void rotateRight(GameBoard & gameBoard, Menu &menu) override;
	virtual void immidiateDown(GameBoard &gameBoard, Menu& menu) override;
	virtual void updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN] = NULL) const override;
	virtual Shape::ShapeType getShapeType() const override { return Shape::LSHAPE; }
	virtual int getStartY() const override { return STARTY + 1; }
	virtual bool hasReachedBottom(GameBoard &gameBoard, Menu& menu)  override;
	virtual bool isGameOver() const override;
	~lShape() { }

};
