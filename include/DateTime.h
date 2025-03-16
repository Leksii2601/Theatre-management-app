#pragma once
#include <ctime>
#include <iostream>
using namespace std;

struct DateTime {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    
    bool operator==(const DateTime& other) const;  // перевіряє чи дві дати однакові
    bool operator<(const DateTime& other) const;   // порівнює дві дати, щоб визначити яка з них раніше
    bool isOnSameDay(const DateTime& other) const; // перевіряє чи дві дати належать одному дню
    bool isFuture() const;                         // перевіряє чи дата знаходиться в майбутньому
};
