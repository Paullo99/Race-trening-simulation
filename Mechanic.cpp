#include "Mechanic.h"

Mechanic::Mechanic()
{
    this->isAvailable = true;
}

bool Mechanic::tryToGoIn()
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

void Mechanic::goOut()
{
	this->mtx.lock();
	this->isAvailable = true;
	this->mtx.unlock();
	cv.notify_one();
}

bool Mechanic::getIfIsAvailable()
{
	return this->isAvailable;
}
