#pragma once
#include <fstream>
#include <iostream>
using namespace std;


#define MAX_NAME_LENGTH 100

struct Ticket {
    int id;
    int performanceIndex;                 // індекс вистави
    char buyerName[MAX_NAME_LENGTH];      // ім'я покупця
    int seatNumber;                       // номер місця
    bool sold;                           // чи продано квиток

    Ticket();
    void saveToFile(std::ofstream& file) const;
    bool loadFromFile(std::ifstream& file);
};
