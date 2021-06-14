#pragma once
#include "Simulation.h"
#include "Driver.h"
#include "Car.h"
#include "Mechanic.h"
#include "Speedway.h"
#include <vector>
#include <thread>

class Simulation {
private:
	int driversAmount;
	int carsAmount;
	int speedwayCapacity;
	int racingTime;
	int fixingTime;
	Mechanic* mechanic;
	Speedway* speedway;
	vector<Driver*>* drivers;
	vector<Car*>* cars;
	vector<thread*>* threads;
	thread* displayThread;
	void display();
	void initialize();
	void initializeThreads();
	void initializeColors();
	void prepareBackground();

public:
	atomic<bool> displaying;
	Simulation(int carsAmount, int driversAmount, int speedwayCapacity, int racingTime, int fixingTime);
	void start();
	void stop();
};