#include "figure.h"


std::string* putTogetherPath(char* a, int index, char* b) {
	std::string* tmp = new std::string(a);
	*tmp += std::to_string(index);
	*tmp += b;
	return tmp;
}


Figure::Figure(float initialX, float initialY, float height, float width) {
	for (int a = 0; a < 8; ++a) {
		addToTextures(putTogetherPath("Textures/BMan/Front/Bman_F_f0", a, ".png"));
	}
	for (int a = 0; a < 8; ++a) {
		addToTextures(putTogetherPath("Textures/BMan/LSide/Bman_F_f0", a, ".png"));
	}
	for (int a = 0; a < 8; ++a) {
		addToTextures(putTogetherPath("Textures/BMan/Back/Bman_B_f0", a, ".png"));
	}
	for (int a = 0; a < 8; ++a) {
		addToTextures(putTogetherPath("Textures/BMan/RSide/Bman_F_f0", a, ".png"));
	}

	this->relativeHeight = height;
	this->relativeWidth = width;

	tempX = initialX;
	tempY = initialY;
	mX = tempX;
	mY = tempY;
	outline();
	constructCarcass();

	isRunning = true;
	mov = new std::thread(&Figure::moveSmoothly, this);
}

Figure::~Figure() {
	isRunning = false;
	mov->join();
	delete mov;
	std::cout << "destroy fig" << std::endl;
}



void Figure::nudge() {

}



void Figure::moveTo(int key) {
	directionKey = key;

	if (key == ' ') {
		placeBomb();
	}
	
}



void Figure::placeBomb() {
	makeRemark("bombPlantedAt", new Point2D(mX, mY));

}

void Figure::moveRight() {
	textureIndexOffset = 24;
}

void Figure::moveLeft() {
	textureIndexOffset = 8;
}

void Figure::moveDown() {
	textureIndexOffset = 0;
}

void Figure::moveUp() {
	textureIndexOffset = 16;
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

void Figure::assistMovement(float dispX, float dispY) {
	typedef std::chrono::high_resolution_clock clock_;
	std::chrono::time_point<clock_> texPause = clock_::now();
	int steps = 13;
	for (int a = 0; a < steps; ++a) {
		if (dispX != 0)
		{
			tempX += dispX / ((float)steps);
			qX -= dispX / ((float)steps);
		}

		if (dispY != 0)
		{
			tempY += dispY / ((float)steps);
			qY -= dispY / ((float)steps);
		}

		vecX = -dispX / ((float)steps);
		vecY = -dispY / ((float)steps);
		makeRemark("moveTo", 0);


		if (clock_::now() - texPause > std::chrono::duration<double>(0.025f)) {
			++indexTexture;
			if (indexTexture >= 8)indexTexture = 0;
			texPause = clock_::now();
		}


		std::chrono::time_point<clock_> pause = clock_::now();
		while (clock_::now() - pause < std::chrono::duration<double>(0.25f / steps)) {}; //0.15

	}

 
}

void Figure::moveSmoothly() {
	typedef std::chrono::high_resolution_clock clock_;
	while (isRunning) {
		if (directionKey == 'D') {
			moveRight();
			assistMovement(relativeWidth, 0);
		}
		if (directionKey == 'A') {
			moveLeft();
			assistMovement(-relativeWidth, 0);
		}
		if (directionKey == 'W') {
			moveUp();
			assistMovement(0, relativeHeight);
		}
		if (directionKey == 'S') {
			moveDown();
			assistMovement(0, -relativeHeight);
		}
	}
}



void Figure::fulfilProphecy() {
	mX = tempX;
	mY = tempY;
}




void Figure::discardProphecy() {
	qX -= mX - tempX;
	qY -= mY - tempY;
	tempX = mX;
	tempY = mY;

}

