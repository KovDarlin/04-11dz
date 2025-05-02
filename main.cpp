#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>

using namespace std;

struct Printed {

    string user;
    int priority;
    time_t requestTime;

    bool operator<(const Printed& other) const {
        return priority > other.priority;
    }
};

struct Printing {
    string user;
    time_t printTime;
};

string formatTime(time_t t) {
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &t);
    return string(buffer);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Ukrainian");

    priority_queue<Printed> printQueue;
    vector<Printing> printHistory;

    printQueue.push({ "Marina", 4, time(nullptr) });
    printQueue.push({ "Darina", 2, time(nullptr) });
    printQueue.push({ "Bonia", 1, time(nullptr) });
    printQueue.push({ "Chloe", 3, time(nullptr) });

    while (!printQueue.empty()) {
        Printed job = printQueue.top();
        printQueue.pop();

        time_t now = time(nullptr);
        cout << "В черзі користувач " << job.user<< " (пріоритет: " << job.priority << ") о "<< formatTime(now);

        printHistory.push_back({ job.user, now });
    }

    cout << "\n--- Статистика друку ---\n";
    for (const auto& log : printHistory) {
        cout << "Користувач: " << log.user << ", Час друку: " << formatTime(log.printTime);
    }

    return 0;
}
