#include ""../include/DateTime.h"

bool DateTime::operator==(const DateTime& other) const {
    return day == other.day && month == other.month &&
        year == other.year && hour == other.hour &&
        minute == other.minute;
}

bool DateTime::operator<(const DateTime& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hour != other.hour) return hour < other.hour;
    return minute < other.minute;
}

bool DateTime::isOnSameDay(const DateTime& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool DateTime::isFuture() const {
    time_t now = time(nullptr);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);

    if (year > timeinfo.tm_year + 1900) return true;
    if (year < timeinfo.tm_year + 1900) return false;

    if (month > timeinfo.tm_mon + 1) return true;
    if (month < timeinfo.tm_mon + 1) return false;

    if (day > timeinfo.tm_mday) return true;
    if (day < timeinfo.tm_mday) return false;

    if (hour > timeinfo.tm_hour) return true;
    if (hour < timeinfo.tm_hour) return false;

    return minute > timeinfo.tm_min;
}
