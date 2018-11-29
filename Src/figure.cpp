#include "figure.h"




Figure::Figure(float initialX, float initialY, float height, float width) {

	// addTexture("Textures/Bman_F_f00.png");
	//texturePath="Textures/Bman_F_f00.png";
	texturePath = "Textures/Bman_F_f00.png";
	this->relativeHeight = height;
	this->relativeWidth = width;

	tempX = initialX;
	tempY = initialY;
	//	collidedGround = false;
	blueprintIndex = 0;
	mX = tempX;
	mY = tempY;
	outline();
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
	if (isRunning)return;
	//if (key == 'E') { collidedGround = true; makeRemark("immovable", 0); } //always called from main thread
	directionKey = key;
	makeRemark("moveTo", 0);
}

void Figure::moveRight() {
	tempX += relativeWidth * speedCoefficient;
}

void Figure::moveLeft() {
	tempX -= relativeWidth * speedCoefficient;
}

void Figure::moveDown() {
	tempY -= relativeHeight * speedCoefficient;
}

void Figure::moveUp() {
	tempY += relativeHeight * speedCoefficient;
}

void Figure::boostDown() {
	speedCoefficient = 0;
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
	carcass.push_back(new Rectangle(0, relativeHeight, relativeWidth, relativeHeight * 2));

	assemble(carcass, 4);

}


Rectangle * Figure::getRectangle()
{
	return new Rectangle(tempX, tempY, relativeWidth, relativeHeight);
}
bool Figure::intersects(Rectangle* rec) {
	return *getRectangle() == *rec;
}



void Figure::moveSmoothly()
{
	isRunning = true;
	typedef std::chrono::high_resolution_clock clock_;


	int steps = 3;
	for (int a = 0; a < steps; ++a) {
		if (tempX != vecX)
			mX += (tempX-vecX) / ((float)steps);
		if (tempY != vecY)
			mY += (tempY-vecY) / ((float)steps);
		std::cout << a << ", ";
		setFlag("redraw", true);
		std::chrono::time_point<clock_> pause = clock_::now();
		while (clock_::now() - pause < std::chrono::duration<double>(0.05)) {};

	}

	vecX = tempX;
	vecY = tempY;

	isRunning = false;
}

void Figure::fulfilProphecy() {
	if (!isRunning)
		t = new std::thread(&Figure::moveSmoothly, this);
	//mX = tempX;
	//mY = tempY;
	outline();
}




void Figure::discardProphecy() {
	tempX = mX;
	tempY = mY;
}

float Figure::getAngle() {
	return angle;
}