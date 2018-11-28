#include "primitive.h"



Point2D::Point2D(float x, float y) {
	vertices = 1;
	this->x = x;
	this->y = y;
}

int Point2D::getVertices() {
	return vertices;
}

float Point2D::getX() {
	return x;
}
float Point2D::getY() {
	return y;
}

void Point2D::setX(float pX) {
	x = pX;
}
void Point2D::setY(float pY) {
	y = pY;
}
bool Point2D :: operator==(Point2D& b) {
	if (fabs(x - b.getX()) < 0.01 && fabs(y - b.getY()) < 0.01) return true;
	return false;
}

Square::Square() {
	vertices = 4;
}

Square::Square(float x, float y, float sidesSize) {
	vertices = 4;

	this->sidesSize = sidesSize;
	this->x = x;
	this->y = y;

	build();
}

Square::~Square() {
	//std::cout << "squre destroyed" << std::endl;
}

float Square::getVertexAt(int index) {
	return matrix[index];
}
float Square::getX() {
	return x;
}
float Square::getY() {
	return y;
}
void Square::setX(float pX) {
	x = pX;
}
void Square::setY(float pY) {
	y = pY;
}
int Square::getVertices() {
	return vertices;
}
float Square::getSize() {
	return sidesSize;
}

void Square::build() {
	int index = 0;
	for (int a = 0; a < 2; ++a) //ver
		for (int b = 0; b < 2; ++b)//horiz
		{
			matrix[index++] = x + sidesSize * b; //x
			matrix[index++] = y - sidesSize * a; //y
			matrix[index++] = 0;//z			
		}
}

bool Square::operator==(Square& b) {
	return fabs(this->getX() - b.getX()) < 0.01 && fabs(this->getY() - b.getY()) < 0.01;
}

Rectangle::Rectangle(float x, float y, float width, float height) {
	vertices = 4;

	this->height = height;
	this->width = width;
	this->x = x;
	this->y = y;

	build();
}

Rectangle::~Rectangle() {
	//std::cout << "rectangle rEkt" << std::endl;
}

void Rectangle::build() {
	int index = 0;
	for (int a = 0; a < 2; ++a) //ver
		for (int b = 0; b < 2; ++b)//horiz
		{
			matrix[index++] = x + width * b; //x
			matrix[index++] = y - height * a; //y
			matrix[index++] = 0;//z			

			if (index == 3) {
				matrix[index++] = -1.0f;
				matrix[index++] = 1.0f;
			}
			if (index == 8) {
				matrix[index++] = 1.0f;
				matrix[index++] = 1.0f;
			}
			if (index == 13) {
				matrix[index++] = -1.0f;
				matrix[index++] = -1.0f;
			}
			if (index == 18) {
				matrix[index++] = 1.0f;
				matrix[index++] = -1.0f;
			}
		}
}

 