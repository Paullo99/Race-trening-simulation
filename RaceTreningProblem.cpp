#include <iostream>
#include "Simulation.h"
#include <curses.h>
#include <limits.h>

using namespace std;

int main()
{
    char input = '0';
    int cars = 7;   //zmienić na INT_MAX
    int drivers = 12;
    int capacity = 4;
    int racingTime = 12000;
    int fixingTime = 1000;


    // cout << "Podaj liczbe kierowcow: ";
    // cin >> drivers;

    // while (cars >= drivers)
    // {
    //     cout << "Podaj liczbe samochodow (mniejsza niz liczba kierowcow): ";
    //     cin >> cars;
    // }

    // cout << "Podaj pojemnosc toru wyscigowego: ";
    // cin >>capacity;

    // cout << "Podaj czas przebywania na torze [ms]: ";
    // cin >> racingTime;

    // cout << "Podaj czas przebywania u mechanika [ms]: ";
    // cin >> fixingTime;

    srand(time(NULL));

    Simulation* simulation = new Simulation(cars, drivers, capacity, racingTime, fixingTime);
    simulation->start();

    while (input != 'q')
        input = getch();

    simulation->stop();

    return 0;
}