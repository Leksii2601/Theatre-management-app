#pragma once
#include "Performance.h"
#include "Ticket.h"
#include <iostream>

const int MAX_PERFORMANCES = 100;
const int MAX_TICKETS = 1000;

class TheaterManager {
private:
    Performance performances[MAX_PERFORMANCES];
    int performanceCount;
    Ticket tickets[MAX_TICKETS];
    int ticketCount;
    
    bool isActorBusy(const char* actorName, const DateTime& startTime, const DateTime& endTime) const;
    void displayPerformance(int index) const;    // показує виставу за індексом.
    
public:
    TheaterManager();
    
    bool addPerformance(const Performance& perf);           // додає нову виставу, перевіряючи обмеження (перетин за часом, зайняті актори).
    void displayAllPerformances() const;                    // показує всі вистави.
    void displayUpcomingPerformances() const;               // показує майбутні вистави.
    void displayPerformancesByActor(const char* actorName) const;  // показує вистави, в яких бере участь актор.
    void searchPerformancesByName(const char* name) const;   // шукає вистави за назвою.
    void searchPerformancesByDate(int day, int month, int year) const;  // шукає вистави за датою.
    bool generateTickets(int perfIndex);                    // генерує квитки для вистави.
    bool sellTicket(int perfIndex, const char* buyerName, int seatNumber);  // продає квиток зберігаючи інформацію про покупця.
    void displayAvailableSeats(int perfIndex) const;        // показує доступні місця для вистави.
    
    void saveToFiles() const;
    void loadFromFiles();
};
