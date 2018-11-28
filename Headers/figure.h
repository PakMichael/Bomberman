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
 


class Figure : public Subordinate, public Entity {

	float relativeWidth;
	float relativeHeight;
	int blueprintIndex;
	int directionKey;
	float speedCoefficient=1;

	bool isRunning=false;

	float tempX, tempY;

	std::shared_ptr<Rectangle> tiles[8];


public:
	std::thread* t=nullptr;

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
 
	Rectangle* getRectangle();
	float getAngle();

private:
	void moveSmoothly();
	void moveTo(int key);
	void constructCarcass();

};



#endif