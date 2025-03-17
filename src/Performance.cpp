#include "../include/Performance.h"
#include <cstring>

Performance::Performance() : duration(0), hasIntermission(false), actorCount(0), totalSeats(0) {
    name[0] = '\0';
    description[0] = '\0';
}

void Performance::setName(const char* _name) {
    strncpy_s(name, MAX_NAME_LENGTH, _name, MAX_NAME_LENGTH - 1);
    name[MAX_NAME_LENGTH - 1] = '\0';
}

void Performance::setDateTime(int day, int month, int year, int hour, int minute) {
    dateTime.day = day;
    dateTime.month = month;
    dateTime.year = year;
    dateTime.hour = hour;
    dateTime.minute = minute;
}

void Performance::setDuration(int _duration) {
    duration = _duration;
}

void Performance::setHasIntermission(bool _hasIntermission) {
    hasIntermission = _hasIntermission;
}

bool Performance::addActor(const char* actor) {
    if (actorCount >= MAX_ACTORS) {
        return false;
    }

    strncpy_s(actors[actorCount], MAX_NAME_LENGTH, actor, MAX_NAME_LENGTH - 1);
    actors[actorCount][MAX_NAME_LENGTH - 1] = '\0';
    actorCount++;
    return true;
}

void Performance::setTotalSeats(int _totalSeats) {
    totalSeats = _totalSeats;
}

void Performance::setDescription(const char* _description) {
    strncpy_s(description, MAX_NAME_LENGTH, _description, MAX_NAME_LENGTH - 1);
    description[MAX_NAME_LENGTH - 1] = '\0';
}

const char* Performance::getName() const {
    return name;
}

const DateTime& Performance::getDateTime() const {
    return dateTime;
}

int Performance::getDuration() const {
    return duration;
}

bool Performance::getHasIntermission() const {
    return hasIntermission;
}

int Performance::getActorCount() const {
    return actorCount;
}

const char* Performance::getActor(int index) const {
    if (index >= 0 && index < actorCount) {
        return actors[index];
    }
    return "";
}

int Performance::getTotalSeats() const {
    return totalSeats;
}

const char* Performance::getDescription() const {
    return description;
}

DateTime Performance::getEndTime() const {
    DateTime end = dateTime;
    end.minute += duration;

    
    while (end.minute >= 60) {
        end.minute -= 60;
        end.hour++;
    }

   
    while (end.hour >= 24) {
        end.hour -= 24;
        end.day++;
    }

    
    const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    
    int maxDays = daysInMonth[end.month];
    if (end.month == 2 && ((end.year % 4 == 0 && end.year % 100 != 0) || end.year % 400 == 0)) {
        maxDays = 29;
    }

    
    while (end.day > maxDays) {
        end.day -= maxDays;
        end.month++;

        if (end.month > 12) {
            end.month = 1;
            end.year++;
        }

        maxDays = daysInMonth[end.month];
        if (end.month == 2 && ((end.year % 4 == 0 && end.year % 100 != 0) || end.year % 400 == 0)) {
            maxDays = 29;
        }
    }

    return end;
}

bool Performance::hasActor(const char* actorName) const {
    for (int i = 0; i < actorCount; i++) {
        if (strcmp(actors[i], actorName) == 0) {
            return true;
        }
    }
    return false;
}

bool Performance::overlapsWith(const Performance& other) const {
    
    if (!dateTime.isOnSameDay(other.dateTime) &&
        !dateTime.isOnSameDay(other.getEndTime()) &&
        !getEndTime().isOnSameDay(other.dateTime)) {
        return false;
    }

    
    if (dateTime < other.getEndTime() && other.dateTime < getEndTime()) {
        return true;
    }

    return false;
}

void Performance::saveToFile(std::ofstream& file) const {
    file << name << '\n';
    file << dateTime.day << ' ' << dateTime.month << ' ' << dateTime.year << ' ';
    file << dateTime.hour << ' ' << dateTime.minute << '\n';
    file << duration << '\n';
    file << (hasIntermission ? "1" : "0") << '\n';
    file << actorCount << '\n';

    for (int i = 0; i < actorCount; i++) {
        file << actors[i] << '\n';
    }

    file << totalSeats << '\n';
    file << description << '\n';
}

bool Performance::loadFromFile(std::ifstream& file) {
    if (!file.getline(name, MAX_NAME_LENGTH)) return false;

    if (!(file >> dateTime.day >> dateTime.month >> dateTime.year >>
        dateTime.hour >> dateTime.minute)) return false;
    file.ignore(); // Consume newline

    if (!(file >> duration)) return false;
    file.ignore();

    char intermissionStr[2];
    if (!file.getline(intermissionStr, 2)) return false;
    hasIntermission = (intermissionStr[0] == '1');

    if (!(file >> actorCount)) return false;
    file.ignore();

    for (int i = 0; i < actorCount; i++) {
        if (!file.getline(actors[i], MAX_NAME_LENGTH)) return false;
    }

    if (!(file >> totalSeats)) return false;
    file.ignore();

    if (!file.getline(description, MAX_NAME_LENGTH)) return false;

    return true;
}
