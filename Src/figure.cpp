#include "figure.h"

bool blueprints[7][8] = {   /* sorry for this :C */
		{ 1, 0, 0, 0, 0, 0, 0, 0 }

};



Figure::Figure(float initialX, float initialY, float height, float width) {

	this->relativeHeight = height;
	this->relativeWidth = width;

	tempX = initialX;
	tempY = initialY;
	collidedGround = false;
	blueprintIndex = 0;
	fulfilProphecy();
	constructCarcass();

}

Figure::~Figure() {

	std::cout << "destroy fig" << std::endl;
}

void Figure::init() {
	//t = std::thread(&Figure::freeFall, this);
}


void Figure::nudge() {

}



void Figure::moveTo(int key) {
	if (key == 'E') { collidedGround = true; makeRemark("immovable", 0); } //always called from main thread
	directionKey = key;
	makeRemark("moveTo", 0);
}

void Figure::moveRight() {
	tempX += relativeWidth;
}

void Figure::moveLeft() {
	tempX -= relativeWidth;
}

void Figure::moveDown() {
	tempY -= relativeHeight;
}

void Figure::moveUp() {
	tempY += relativeHeight;
}

void Figure::boostDown() {
	speed = 0;
}

void Figure::rotate() {
	if (angle == 0)
	{
		angle = M_PI / 2;
	}
	else
	{
		angle = 0.0;
	}

}

void Figure::moveNTimesBy(int x, int y) {
	tempX += relativeHeight * x;
	tempY += relativeWidth * y;
}

int Figure::getDirection() {
	return directionKey;
}
float Figure::getX() {
	return mX;
}

float Figure::getY() {
	return mY;
}
void Figure::constructCarcass() {

	std::vector<Primitive*> carcass;
	carcass.push_back(new Rectangle(0, 0, relativeWidth, relativeHeight));

	assemble(carcass, 4);

}

Point2D* Figure::getDimensionsOfTile(int index, float angle) {
	if (!blueprints[blueprintIndex][index])return 0;
	float tmpX = index * relativeWidth - relativeWidth * 4 * (index / 4);
	float tmpY = -(index / 4)*relativeHeight;
	if (!Arithmetics::floatEquals(angle, 0))
	{
		float temp = tmpX - relativeHeight;
		tmpX = -tmpY;
		tmpY = temp;
	}
	return new Point2D(tmpX + mX, tmpY + mY);
}
Rectangle * Figure::getRectangle()
{
	return new Rectangle(tempX, tempY, relativeWidth, relativeHeight);
}
bool Figure::intersects(Rectangle* rec) {
	return *getRectangle() == *rec;
}



void Figure::fulfilProphecy() {
	mX = tempX;
	mY = tempY;

	outline();
}

void Figure::discardProphecy() {
	tempX = mX;
	tempY = mY;
}

float Figure::getAngle() {
	return angle;
}