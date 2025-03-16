#pragma once
#include "DateTime.h"
#include <fstream>

const int MAX_NAME_LENGTH = 256;
const int MAX_ACTORS = 20;

class Performance {
private:
    char name[MAX_NAME_LENGTH];                   // назва вистави
    DateTime dateTime;                            // дата та час початку вистави
    int duration;                                 // тривалість вистави у хвилинах
    bool hasIntermission;                         // чи є антракт
    char actors[MAX_ACTORS][MAX_NAME_LENGTH];     // актори, які беруть участь у виставі
    int actorCount;                               // кількість акторів
    int totalSeats;                               // загальна кількість місць
    char description[MAX_NAME_LENGTH];            // опис вистави

public:
    Performance();
    void setName(const char* _name);
    void setDateTime(int day, int month, int year, int hour, int minute);
    void setDuration(int _duration);
    void setHasIntermission(bool _hasIntermission);
    bool addActor(const char* actor);
    void setTotalSeats(int _totalSeats);
    void setDescription(const char* _description);
    
    const char* getName() const;
    const DateTime& getDateTime() const;
    int getDuration() const;
    bool getHasIntermission() const;
    int getActorCount() const;
    const char* getActor(int index) const;
    int getTotalSeats() const;
    const char* getDescription() const;
    DateTime getEndTime() const;
    
    bool hasActor(const char* actorName) const;           // перевіряє чи актор бере участь у виставі
    bool overlapsWith(const Performance& other) const;    // перевіряє чи вистава перекривається з іншою
    
    void saveToFile(std::ofstream& file) const;
    bool loadFromFile(std::ifstream& file);
};
