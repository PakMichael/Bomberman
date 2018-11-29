#include "figure.h"


std::string* putTogetherPath(char* a, int index, char* b) {
	std::string* tmp = new std::string(a);
	*tmp += std::to_string(index);
	*tmp += b;
	return tmp;
}


Figure::Figure(float initialX, float initialY, float height, float width) {

	for (int a = 0; a < 8; ++a) {
		addToTextures(putTogetherPath("Textures/BMan/Front/Bman_F_f0",a, ".png"));
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



	//texturePath="Textures/Bman_F_f00.png";
	//texturePath = "Textures/Bman_F_f00.png";
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


void Figure::placeBomb(){
	makeRemark("bombPlantedAt",new Point2D(mX,mY));

}

void Figure::moveRight() {
	tempX += relativeWidth * speedCoefficient;
	textureIndexOffset = 24;
}

void Figure::moveLeft() {
	tempX -= relativeWidth * speedCoefficient;
	textureIndexOffset = 8;
}

void Figure::moveDown() {
	tempY -= relativeHeight * speedCoefficient;
	textureIndexOffset = 0;
}

void Figure::moveUp() {
	tempY += relativeHeight * speedCoefficient;
	textureIndexOffset = 16;
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

	std::chrono::time_point<clock_> texPause = clock_::now();

	int steps = 12;
	for (int a = 0; a < steps; ++a) {
		if (tempX != vecX) {
			mX += (tempX - vecX) / ((float)steps);
			qX -= (tempX - vecX) / ((float)steps);
			makeRemark("stepped", new Point2D((-tempX + vecX) / ((float)steps), 0));
		}
		if (tempY != vecY) {
			mY += (tempY - vecY) / ((float)steps);
			qY -= (tempY - vecY) / ((float)steps);
			makeRemark("stepped", new Point2D(0, (-tempY + vecY) / ((float)steps)));
		}
		std::cout << a << ", ";
		//makeRemark("stepped", new Point2D(vecX-tempX, vecY- tempY));
		if (clock_::now() - texPause > std::chrono::duration<double>(0.05f)) {
			++indexTexture;
			if (indexTexture >= 8)indexTexture = 0;
			texPause = clock_::now();
		}


		std::chrono::time_point<clock_> pause = clock_::now();
		while (clock_::now() - pause < std::chrono::duration<double>(0.15f / steps)) {};

	}

	vecX = tempX;
	vecY = tempY;

	isRunning = false;
}

void Figure::smoothTextureTransitions()
{
	typedef std::chrono::high_resolution_clock clock_;

	do {
		++indexTexture;
		makeRemark("redraw", 0);
		if (indexTexture >= allTexturePaths.size())indexTexture = 0;
		std::chrono::time_point<clock_> pause = clock_::now();
		while (clock_::now() - pause < std::chrono::duration<double>(0.0125f)) {};
	} while (!isRunning);
}



void Figure::fulfilProphecy() {
	if (!isRunning) {
		t = new std::thread(&Figure::moveSmoothly, this);
	}
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