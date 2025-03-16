#pragma once
#include <fstream>

extern const int MAX_NAME_LENGTH;

struct Ticket {
    int id;
    int performanceIndex;                 // індекс вистави
    char buyerName[MAX_NAME_LENGTH];
    int seatNumber;
    bool sold;                           // чи продано квиток
    
    Ticket();
    void saveToFile(std::ofstream& file) const;
    bool loadFromFile(std::ifstream& file);
};
