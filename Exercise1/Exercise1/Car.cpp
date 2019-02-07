#include "stdafx.h"
#include "Car.h"




Car::Car(int bilId)
{
	Car::id = bilId;
}

Car::Car(const Car & car)
{
	this->id = car.id;
	this->bottom = car.bottom;
	this->left = car.left;
	this->right = car.right;
	this->top = car.top;
	this->retning = car.retning;
}

Car::~Car()
{
}

int Car::getId()
{
	return Car::id;
}

int Car::getRetning()
{
	return Car::retning;
}

int Car::getTop()
{
	return Car::top;
}

int Car::getLeft()
{
	return Car::left;
}

int Car::getRight()
{
	return Car::right;
}

int Car::getBottom()
{
	return Car::bottom;
}

void Car::setTop(int t)
{
	Car::top = t;
}

void Car::setLeft(int l)
{
	Car::left = l;
}

void Car::setRight(int r)
{
	Car::right = r;
}

void Car::setBottom(int b)
{
	Car::bottom = b;
}

void Car::setRetning(int r) {
	Car::retning = r;
}

bool Car::operator==(Car &car1) const
{
	bool resultat = this->id == car1.getId();
	return resultat;
}

bool operator==(Car  & car1, Car  & car2)
{
	return car1.getId() == car2.getId();
}
