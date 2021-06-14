#include "Car.h"

Car::Car(int id)
{
    this->id = id;
    this->isAvailable = true;
}

bool Car::tryToTake()
{
	if (this->mtx.try_lock())
	{
		if (this->isAvailable)
		{
			this->isAvailable = false;
			this->mtx.unlock();
			return true;
		}
		this->mtx.unlock();
	}

	return false;
}

void Car::release()
{
	this->mtx.lock();
	this->isAvailable = true;
	this->mtx.unlock();
}

int Car::getId()
{
	return this->id;
}

bool Car::getAvailability()
{
	return this->isAvailable;
}
