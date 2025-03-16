#include "../include/Ticket.h"
#include <cstring>

Ticket::Ticket() : id(0), performanceIndex(-1), seatNumber(0), sold(false) {
    buyerName[0] = '\0';
}

void Ticket::saveToFile(std::ofstream& file) const {
    file << id << ' ' << performanceIndex << ' ' << seatNumber << ' ';
    file << (sold ? "1" : "0") << '\n';
    file << buyerName << '\n';
}

bool Ticket::loadFromFile(std::ifstream& file) {
    if (!(file >> id >> performanceIndex >> seatNumber)) return false;

    char soldStr[2];
    file >> soldStr;
    sold = (soldStr[0] == '1');
    file.ignore();

    if (!file.getline(buyerName, MAX_NAME_LENGTH)) return false;

    return true;
}
