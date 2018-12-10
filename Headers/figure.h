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

	float relativeWidth, relativeHeight;
	int directionKey;

	bool isRunning = true;

	float tempX, tempY;




public:
	float vecX = 0, vecY = 0;

	std::thread* mov = nullptr;
public:
	Figure(float initialX, float initialY, float height, float width);
	~Figure();

 
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();
	void placeBomb();
	void nudge();
	int getDirection();
	float getX();
	float getY();
 


	void fulfilProphecy();
	void discardProphecy();

	bool intersects(Rectangle* rec);

	Rectangle* getRectangle();

private:
	void assistMovement(float dispX, float dispY);
	void moveSmoothly();
	void moveTo(int key);
	void constructCarcass();

};



#endif