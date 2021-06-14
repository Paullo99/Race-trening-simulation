#pragma once
#include<mutex>
#include<atomic>

using namespace std;

class Car {
private:
	int id;
	atomic<bool> isAvailable;
	mutex mtx;
public:
	Car(int id);
	bool tryToTake();
	void release();
	int getId();
	bool getAvailability();
};