#include "Driver.h"

Driver::Driver(int id, int racingTime, Mechanic* mechanic, Speedway* speedway, vector<Car*>* cars, int fixingTime) {
    this->id = id;
    this->car = nullptr;
    this->racingTime = racingTime + ((20 - (rand() % 41)) * racingTime) / 100;
    this->setState(0);
    this->mechanic = mechanic;
    this->speedway = speedway;
    this->cars = cars;
    this->runSimulation = true;
    this->fixingTime = fixingTime;
}

int Driver::getRacingTime()
{
    return this->racingTime;
}

int Driver::getPassedRacingTime()
{
    return this->passedRacingTime;
}


bool Driver::takeCar()
{
    for (int i = 0; i < this->cars->size(); i++)
    {
        if (cars->at(i)->tryToTake())
        {
            this->car = cars->at(i);
            return true;
        }
    }
    return false;
}

void Driver::releaseCar()
{
    this->car->release();
    this->state = 0;
    this_thread::sleep_for(chrono::milliseconds(4000));
}

void Driver::rideIntoMechanicsPlaceBeforeRace()
{
    unique_lock<mutex> lk(this->mechanic->mtx);
    while (!this->mechanic->getIfIsAvailable()) this->speedway->cv.wait(lk);

    this->mechanic->tryToGoIn();
    this->setState(2);
    this_thread::sleep_for(chrono::milliseconds(this->fixingTime));
}

void Driver::rideIntoMechanicsPlaceAfterRace()
{
    unique_lock<mutex> lk(this->mechanic->mtx);
    while (!this->mechanic->getIfIsAvailable()) this->speedway->cv.wait(lk);
    
    this->mechanic->tryToGoIn();
    this->setState(5);
    this_thread::sleep_for(chrono::milliseconds(this->fixingTime));
}

void Driver::goOnRace()
{
    this->setState(3);
    while(this->passedRacingTime < this->racingTime)
    {
        passedRacingTime+=50;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    passedRacingTime = 0;
}

void Driver::simulate()
{
    while (runSimulation)
    {
        if (takeCar())
        {
            this->setState(1);

            if (!this->speedway->getSlot())
            {
                unique_lock<mutex> lck(this->speedway->mtx);
                while (this->speedway->getFreeSlots() == 0) this->speedway->cv.wait(lck);

                this->rideIntoMechanicsPlaceBeforeRace();
         
                this->speedway->setFreeSlots(this->speedway->getFreeSlots() - 1);
            }
            else 
            {
                this->rideIntoMechanicsPlaceBeforeRace();
            }
            
            this->goOnRace();

            this->speedway->releaseSlot();
            this->setState(4);

            this->rideIntoMechanicsPlaceAfterRace();

            this->releaseCar();
        } 
        this_thread::sleep_for(chrono::milliseconds(600));
    }
}

void Driver::setState(int state)
{
    this->state = state;
}

int Driver::getState()
{
    return this->state;
}
