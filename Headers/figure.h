#ifndef FIGURE_H
#define FIGURE_H

# define M_PI 3.14159265358979323846

#include "subordinate.h"
#include "entity.h"
#include "primitive.h"
#include <cstdlib>
#include <vector>
#include <thread>
#include <ctime>
#include <cmath>

extern bool blueprints[7][8];


class Figure : public Subordinate, public Entity {

	float relativeWidth;
	float relativeHeight;
	int blueprintIndex;
	int directionKey;
	float speed;

	bool collidedGround;

	float tempX, tempY;

	std::shared_ptr<Rectangle> tiles[8];


public:
	std::thread t;

public:
	Figure(float initialX, float initialY, float height, float width);
	~Figure();

	void boostDown();
	void moveNTimesBy(int x, int y);
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();
	void rotate();
	void nudge();
	int getDirection();
	float getX();
	float getY();

	void init();


	void fulfilProphecy();
	void discardProphecy();

	bool intersects(Rectangle* rec);
	Point2D* getDimensionsOfTile(int index, float angle);
	Rectangle* getRectangle();
	float getAngle();

private:
	void moveTo(int key);
	void constructCarcass();

};



#endif