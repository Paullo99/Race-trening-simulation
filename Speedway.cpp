#include "Speedway.h"

Speedway::Speedway(int capacity)
{
    this->capacity = capacity;
    this->freeSlots = capacity;
}

int Speedway::getCapacity()
{
    return this->capacity;
}

void Speedway::setCapacity(int capacity)
{
    this->capacity = capacity;
}

int Speedway::getFreeSlots()
{
    return this->freeSlots;
}

void Speedway::setFreeSlots(int freeSlots)
{
     this->freeSlots = freeSlots;
}

void Speedway::releaseSlot()
{
    this->freeSlots++;
    cv.notify_one();
}

bool Speedway::getSlot()
{
	if (this->freeSlots > 0 && this->mtx.try_lock())
	{
        this->freeSlots--;
        mtx.unlock();
        return true;
	}

	return false;
}
