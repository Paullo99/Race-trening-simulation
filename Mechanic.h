#pragma once
#include <mutex>
#include <condition_variable>

using namespace std;

class Mechanic {
private:
	bool isAvailable;
public:
	mutex mtx;
	condition_variable cv;
	Mechanic();
	bool tryToGoIn();
	void goOut();
	bool getIfIsAvailable();
};