#include <iostream>
#include <queue>
#include <ctime>
#include <vector>
#include <random>
#include <windows.h>

using namespace std;

struct MyStruct
{
	int arrival;
};

int getRandom(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Ukrainian");
    
    const int Time = 1000;
    const int max_people = 20;
    const int min_seat = 7;
    const int max_seat = 15;

    int Interval_Passenger = 2;
    int Interval_Minibus = 7;

    queue<MyStruct> stopQueue;

    int nextPassengerTime = getRandom(Interval_Passenger - 1, Interval_Passenger + 1);
    int nextMinibusTime = getRandom(Interval_Minibus - 2, Interval_Minibus + 2);

    int totalWaitTime = 0;
    int servedPassengers = 0;
    size_t maxPeopleOnStop = 0;

    for (int currentTime = 0; currentTime < Time; ++currentTime) {
        if (currentTime == nextPassengerTime) {
            stopQueue.push({ currentTime });
            nextPassengerTime = currentTime + getRandom(Interval_Passenger - 1, Interval_Passenger + 1);
        }
        if (currentTime == nextMinibusTime) {
            int seats = getRandom(min_seat, max_seat);
            while (!stopQueue.empty() && seats > 0) {
                MyStruct p = stopQueue.front();
                stopQueue.pop();
                totalWaitTime += (currentTime - p.arrival);
                servedPassengers++;
                seats--;
            }
            nextMinibusTime = currentTime + getRandom(Interval_Minibus - 2, Interval_Minibus + 2);
        }

        if (stopQueue.size() > maxPeopleOnStop)
            maxPeopleOnStop = stopQueue.size();
    }

    cout << "Всього пасажирів: " << servedPassengers << endl;
    cout << "Середній час очікування: " << (servedPassengers ? (totalWaitTime / servedPassengers) : 0) << " хвилин" << endl;
    cout << "Максимум людей на зупинці: " << maxPeopleOnStop << endl;
    cout << "Рекомендований інтервал прибуття маршруток: "
        << (Interval_Minibus * maxPeopleOnStop / max_people) << " хв" << endl;

    return 0;
}