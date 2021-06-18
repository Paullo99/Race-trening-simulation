#include "Simulation.h"
#include <ncurses.h>
#define WAITING_FOR_CAR 1
#define WAITING_FOR_MECHANIC 2
#define BY_MECHANIC_BEFORE_RACE 3
#define ON_RACE 4
#define LEAVING_RACE 5
#define BY_MECHANIC_AFTER_RACE 6
#define FREE_CAR 7

#define CAR_PARK 10
#define MECHANIC 20
#define SPEEDWAY 30
#define BACKGROUND 99

Simulation::Simulation(int carsAmount, int driversAmount, int speedwayCapacity, int racingTime, int fixingTime)
{
	this->carsAmount = carsAmount;
	this->fixingTime = fixingTime;
	this->driversAmount = driversAmount;
	this->speedwayCapacity = speedwayCapacity;
	this->racingTime = racingTime;
	this->drivers = new vector<Driver*>;
	this->cars = new vector<Car*>;
	this->threads = new vector<thread*>;
	this->initialize();
	this->displaying = true;
}

void Simulation::start()
{
	this->initializeThreads();
	initscr();
	this->displayThread = new thread(&Simulation::display, this);
}

void Simulation::stop()
{
	for (int i = 0; i < driversAmount; i++)
	{
		this->drivers->at(i)->runSimulation = false;
		this->threads->at(i)->join();
	}
	this->displaying = false;
	this->displayThread->join();
	clear();
	endwin();
}


void Simulation::initializeColors()
{
	init_pair(WAITING_FOR_CAR, COLOR_BLUE, COLOR_WHITE);
    init_pair(WAITING_FOR_MECHANIC, COLOR_BLACK, COLOR_RED);
    init_pair(BY_MECHANIC_BEFORE_RACE, COLOR_BLACK, COLOR_CYAN);
    init_pair(ON_RACE, COLOR_BLACK, COLOR_GREEN);
    init_pair(LEAVING_RACE, COLOR_WHITE, COLOR_BLUE);
    init_pair(BY_MECHANIC_AFTER_RACE, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(CAR_PARK, COLOR_WHITE, COLOR_BLUE);
    init_pair(MECHANIC, COLOR_BLACK, COLOR_YELLOW);
    init_pair(SPEEDWAY, COLOR_WHITE, COLOR_BLACK);
	init_pair(FREE_CAR, COLOR_GREEN, COLOR_BLACK);
	init_pair(BACKGROUND, COLOR_BLACK, COLOR_WHITE);
}

void Simulation::prepareBackground()
{
	bkgd(COLOR_PAIR(BACKGROUND));
    attron(COLOR_PAIR(CAR_PARK));

	for(int i=0; i<15; i++)
	{
		mvhline(LINES-i,50,' ',  COLS-100);
	}
	printw("PARKING");

	attron(COLOR_PAIR(MECHANIC));
	for(int i=15; i<27; i++)
	{
		mvhline(LINES-i,95,' ',  COLS-190);
	}
	printw("MECHANIK");

	attron(COLOR_PAIR(SPEEDWAY));
	mvhline(LINES-25,40,' ',  55);
	mvhline(LINES-26,40,' ',  55);
	for(int i=27; i<34; i++)
	{
		mvhline(LINES-i,40,' ',  COLS-80);
	}
	for(int i=34; i<42; i++)
	{
		mvhline(LINES-i,40,' ',  18);
		mvhline(LINES-i,COLS-58,' ',  18);
	}
	for(int i=42; i<LINES; i++)
	{
		mvhline(LINES-i,40,' ',  COLS-80);
	}
	printw("TOR (pojemnosc: %d)", this->speedwayCapacity);
}

void Simulation::display()
{
	start_color();
	this->initializeColors();


	while (displaying)
	{
		clear();
		this->prepareBackground();

		int waiting_index = 0;
		int leaving_index = 0;

		for(int i=0; i<this->drivers->size(); i++)
		{
			int currentTime = this->drivers->at(i)->getPassedRacingTime(); 
			int partTime = this->drivers->at(i)->getRacingTime()/8;
			switch(this->drivers->at(i)->getState())
			{
				case 0:
					attron(COLOR_PAIR(WAITING_FOR_CAR));
					move((LINES-12)+i%10,51+(i/10)*4);
					printw("K%02d",i);
					break;

				case 1:
					attron(COLOR_PAIR(WAITING_FOR_MECHANIC));
					move((LINES-14)+waiting_index,102);
					printw("<K%02d]",i);
					waiting_index++;
					break;

				case 2:
					attron(COLOR_PAIR(BY_MECHANIC_BEFORE_RACE));
					move(LINES-18,100);
					printw("<K%02d]",i);
					break;
					
				case 3:
					attron(COLOR_PAIR(ON_RACE));
					if(currentTime < partTime)
					{
						move(LINES-30+i%3,96 + (currentTime*50)/partTime + (i%3)*3);
						printw("|K%02d>",i);
					}
					if(partTime <= currentTime && currentTime < partTime * 2)
					{
						move(LINES-30 +i%3 - ((currentTime-partTime)*8)/partTime,146 + (i%3)*3);
						printw("|K%02d|",i);
					}
					if(partTime*2 <= currentTime && currentTime < partTime * 3)
					{
						move(LINES-37 +i%3 - ((currentTime-partTime*2)*8)/partTime,146 + (i%3)*3);
						printw("|K%02d|",i);
					}
					if(partTime*3 <= currentTime && currentTime < partTime * 4)
					{
						move(LINES-46 +i%3, 146 - ((currentTime-partTime*3)*50)/partTime + (i%3)*3);
						printw("<K%02d|",i);
					}
					if(partTime*4 <= currentTime && currentTime < partTime * 5)
					{
						move(LINES-46 +i%3, 96 - ((currentTime-partTime*4)*50)/partTime + (i%3)*3);
						printw("<K%02d|",i);
					}
					if(partTime*5 <= currentTime && currentTime < partTime * 6)
					{
						move(LINES-46+i%3 + ((currentTime-partTime*5)*8)/partTime,46 + (i%3)*3);
						printw("|K%02d|",i);
					}
					if(partTime*6 <= currentTime && currentTime < partTime * 7)
					{
						move(LINES-38+i%3 + ((currentTime-partTime*6)*8)/partTime,46 + (i%3)*3);
						printw("|K%02d|",i);
					}
					if(partTime*7 <= currentTime && currentTime < partTime * 8)
					{
						move(LINES-30 + i%3,46 + ((currentTime-partTime*7)*40)/partTime + (i%3)*3);
						printw("|K%02d>",i);
					}
					break;

				case 4:
					attron(COLOR_PAIR(LEAVING_RACE));
					move(LINES-26,89 - leaving_index*6);
					printw("[K%02d>",i);
					leaving_index++;
				 	break;
				
				case 5:
					attron(COLOR_PAIR(BY_MECHANIC_AFTER_RACE));
					move(LINES-23,98);
					printw("[K%02d>",i);
					break;
				default:
					break;
			}
		}

		for(int i=0; i<this->cars->size(); i++)
		{
			if(this->cars->at(i)->getAvailability())
			{
				attron(COLOR_PAIR(WAITING_FOR_CAR));
				move((LINES-12)+i%10,COLS-54-(i/10)*4);
				printw("< ]",i);
			}
		}

		move(LINES-1,0);
		attron(COLOR_PAIR(BACKGROUND));
		printw("Pawel Macionczyk, 248837");

		move(0,0);
		refresh();
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void Simulation::initialize()
{
	this->speedway = new Speedway(speedwayCapacity);
	this->mechanic = new Mechanic();

	for (int i = 0; i < this->driversAmount; i++)
		this->drivers->push_back(new Driver(i, racingTime, this->mechanic, this->speedway, this->cars, this->fixingTime));

	for (int i = 0; i < this->carsAmount; i++)
		this->cars->push_back(new Car(i));
	
}

void Simulation::initializeThreads()
{
	for (int i = 0; i < this->driversAmount; i++)
	{
		this->threads->push_back(new thread(&Driver::simulate, drivers->at(i)));
	}
}
