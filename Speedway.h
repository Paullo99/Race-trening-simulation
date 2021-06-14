#pragma once

#include <condition_variable>
#include <mutex>
#include <atomic>
#include<iostream>

using namespace std;

class Speedway {
private:
	int capacity;
	int freeSlots;
public:
	mutex mtx;
	Speedway(int capacity);
	condition_variable cv;
	int getCapacity();
	void setCapacity(int capacity);
	int getFreeSlots();
	void setFreeSlots(int freeSlots);
	void releaseSlot();
	bool getSlot();
};