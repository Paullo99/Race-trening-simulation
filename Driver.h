#pragma once
#include <chrono>
#include <thread>
#include <iostream>
#include <atomic>
#include<vector>
#include "Mechanic.h"
#include "Speedway.h"
#include "Car.h"

using namespace std;

class Driver {
private:
	int id;
	/*
	* 0 - waiting for car
	* 1 - waiting for mechanic
	* 2 - fixing before entry
	* 3 - on road
	* 4 - leaving speedway & waiting for mechanic
	* 5 - fixing after race
	*/
	Car* car;
	vector<Car*> *cars;
	Mechanic* mechanic;
	Speedway* speedway;
	int racingAmounts = 0;
	int racingTime;
	int passedRacingTime = 0;
	int fixingTime;
	int state;
public:
	atomic<bool> runSimulation;
	Driver(int id, int racingTime, Mechanic* mechanic, Speedway* speedway, vector<Car*>* cars, int fixingTime);
	bool takeCar();
	void releaseCar();
	void rideIntoMechanicsPlaceBeforeRace();
	void rideIntoMechanicsPlaceAfterRace();
	void goOnRace();
	void leaveRace();
	int getRacingTime();
	int getPassedRacingTime();
	void simulate();

	void setState(int state);
	int getState();
};