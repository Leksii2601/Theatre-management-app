TheaterManager::TheaterManager() : performanceCount(0), ticketCount(0) {}

bool TheaterManager::isActorBusy(const char* actorName, const DateTime& startTime, const DateTime& endTime) const {
    for (int i = 0; i < performanceCount; i++) {
        if (performances[i].hasActor(actorName)) {
            // Check if same day
            if (performances[i].getDateTime().isOnSameDay(startTime)) {
                // Check if this performance ends less than 1 hour before the new one starts
                // or starts less than 1 hour after the new one ends
                DateTime perfEnd = performances[i].getEndTime();

                // Simple time comparison (not perfect but workable)
                if ((perfEnd < startTime &&
                    (startTime.hour - perfEnd.hour < 1 ||
                        (startTime.hour - perfEnd.hour == 1 && startTime.minute < perfEnd.minute))) ||
                    (endTime < performances[i].getDateTime() &&
                        (performances[i].getDateTime().hour - endTime.hour < 1 ||
                            (performances[i].getDateTime().hour - endTime.hour == 1 && performances[i].getDateTime().minute < endTime.minute)))) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool TheaterManager::addPerformance(const Performance& perf) {
    // Check if maximum performances reached
    if (performanceCount >= MAX_PERFORMANCES) {
        return false;
    }

    // Check constraints
    if (perf.getTotalSeats() <= 0) {
        return false;
    }

    // Check for overlapping performances
    for (int i = 0; i < performanceCount; i++) {
        if (performances[i].overlapsWith(perf)) {
            return false;
        }
    }

    // Check for actor constraints
    DateTime perfStart = perf.getDateTime();
    DateTime perfEnd = perf.getEndTime();

    for (int i = 0; i < perf.getActorCount(); i++) {
        if (isActorBusy(perf.getActor(i), perfStart, perfEnd)) {
            return false;
        }
    }

    // Add performance
    performances[performanceCount] = perf;
    performanceCount++;
    return true;
}

void TheaterManager::displayAllPerformances() const {
    if (performanceCount == 0) {
        cout << "No performances found.\n";
        return;
    }

    for (int i = 0; i < performanceCount; i++) {
        displayPerformance(i);
    }
}

void TheaterManager::displayUpcomingPerformances() const {
    bool found = false;

    for (int i = 0; i < performanceCount; i++) {
        if (performances[i].getDateTime().isFuture()) {
            displayPerformance(i);
            found = true;
        }
    }

    if (!found) {
        cout << "No upcoming performances found.\n";
    }
}

void TheaterManager::displayPerformancesByActor(const char* actorName) const {
    bool found = false;

    for (int i = 0; i < performanceCount; i++) {
        if (performances[i].hasActor(actorName)) {
            displayPerformance(i);
            found = true;
        }
    }

    if (!found) {
        cout << "No performances found for actor: " << actorName << "\n";
    }
}

void TheaterManager::searchPerformancesByName(const char* name) const {
    bool found = false;

    for (int i = 0; i < performanceCount; i++) {
        // Simple substring search
        if (strstr(performances[i].getName(), name) != nullptr) {
            displayPerformance(i);
            found = true;
        }
    }

    if (!found) {
        cout << "No performances found matching name: " << name << "\n";
    }
}

void TheaterManager::searchPerformancesByDate(int day, int month, int year) const {
    bool found = false;

    for (int i = 0; i < performanceCount; i++) {
        const DateTime& dt = performances[i].getDateTime();
        if (dt.day == day && dt.month == month && dt.year == year) {
            displayPerformance(i);
            found = true;
        }
    }

    if (!found) {
        cout << "No performances found on date: "
            << day << "/" << month << "/" << year << "\n";
    }
}

bool TheaterManager::generateTickets(int perfIndex) {
    if (perfIndex < 0 || perfIndex >= performanceCount) {
        return false;
    }

    // Check if tickets already generated
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].performanceIndex == perfIndex) {
            return false; // Already generated
        }
    }

    int totalSeats = performances[perfIndex].getTotalSeats();
    if (ticketCount + totalSeats > MAX_TICKETS) {
        return false; // Not enough space for all tickets
    }

    // Generate tickets
    for (int seat = 1; seat <= totalSeats; seat++) {
        tickets[ticketCount].id = ticketCount + 1; // IDs start at 1
        tickets[ticketCount].performanceIndex = perfIndex;
        tickets[ticketCount].seatNumber = seat;
        tickets[ticketCount].sold = false;
        tickets[ticketCount].buyerName[0] = '\0';
        ticketCount++;
    }

    return true;
}

bool TheaterManager::sellTicket(int perfIndex, const char* buyerName, int seatNumber) {
    if (perfIndex < 0 || perfIndex >= performanceCount) {
        return false;
    }

    // Find the ticket
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].performanceIndex == perfIndex &&
            tickets[i].seatNumber == seatNumber) {

            if (tickets[i].sold) {
                return false; // Already sold
            }

            // Sell the ticket
            tickets[i].sold = true;
            strncpy_s(tickets[i].buyerName, MAX_NAME_LENGTH, buyerName, MAX_NAME_LENGTH - 1);
            tickets[i].buyerName[MAX_NAME_LENGTH - 1] = '\0';
            return true;
        }
    }

    return false; // Ticket not found
}
void TheaterManager::displayAvailableSeats(int perfIndex) const {
    if (perfIndex < 0 || perfIndex >= performanceCount) {
        cout << "Invalid performance index.\n";
        return;
    }

    bool ticketsGenerated = false;
    int totalSeats = performances[perfIndex].getTotalSeats();
    int availableSeats = 0;

    cout << "Available seats for performance \"" << performances[perfIndex].getName() << "\":\n";

    // Check if tickets have been generated for this performance
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].performanceIndex == perfIndex) {
            ticketsGenerated = true;
            break;
        }
    }

    if (!ticketsGenerated) {
        cout << "No tickets have been generated for this performance yet.\n";
        return;
    }

    // Display available seats
    cout << "Seat numbers available: ";
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].performanceIndex == perfIndex && !tickets[i].sold) {
            cout << tickets[i].seatNumber << " ";
            availableSeats++;
        }
    }

    cout << "\n\nTotal available seats: " << availableSeats << " out of " << totalSeats << "\n";
}

void TheaterManager::displayPerformance(int index) const {
    if (index < 0 || index >= performanceCount) {
        cout << "Invalid performance index.\n";
        return;
    }

    const Performance& perf = performances[index];
    const DateTime& dt = perf.getDateTime();
    const DateTime& endTime = perf.getEndTime();

    cout << "====================================\n";
    cout << "Performance ID: " << index << "\n";
    cout << "Name: " << perf.getName() << "\n";
    cout << "Date & Time: " << dt.day << "/" << dt.month << "/" << dt.year
        << " at " << dt.hour << ":" << (dt.minute < 10 ? "0" : "") << dt.minute << "\n";
    cout << "End Time: " << endTime.day << "/" << endTime.month << "/" << endTime.year
        << " at " << endTime.hour << ":" << (endTime.minute < 10 ? "0" : "") << endTime.minute << "\n";
    cout << "Duration: " << perf.getDuration() << " minutes\n";
    cout << "Intermission: " << (perf.getHasIntermission() ? "Yes" : "No") << "\n";
    cout << "Total Seats: " << perf.getTotalSeats() << "\n";

    // Count available seats
    int availableSeats = perf.getTotalSeats();
    bool ticketsGenerated = false;

    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].performanceIndex == index) {
            ticketsGenerated = true;
            if (tickets[i].sold) {
                availableSeats--;
            }
        }
    }

    if (ticketsGenerated) {
        cout << "Available Seats: " << availableSeats << "\n";
    }
    else {
        cout << "Tickets have not been generated yet.\n";
    }

    cout << "Cast:\n";
    for (int i = 0; i < perf.getActorCount(); i++) {
        cout << "  - " << perf.getActor(i) << "\n";
    }

    cout << "Description: " << perf.getDescription() << "\n";
    cout << "====================================\n\n";
}

void TheaterManager::saveToFiles() const {
    // Save performances
    ofstream perfFile("performances.txt");
    if (!perfFile) {
        cout << "Error opening performances file for writing.\n";
        return;
    }

    perfFile << performanceCount << "\n";
    for (int i = 0; i < performanceCount; i++) {
        performances[i].saveToFile(perfFile);
    }
    perfFile.close();

    // Save tickets
    ofstream ticketFile("tickets.txt");
    if (!ticketFile) {
        cout << "Error opening tickets file for writing.\n";
        return;
    }

    ticketFile << ticketCount << "\n";
    for (int i = 0; i < ticketCount; i++) {
        tickets[i].saveToFile(ticketFile);
    }
    ticketFile.close();

    cout << "Data saved successfully.\n";
}

void TheaterManager::loadFromFiles() {
    // Load performances
    ifstream perfFile("performances.txt");
    if (!perfFile) {
        cout << "Performances file not found. Starting with empty database.\n";
        return;
    }

    if (!(perfFile >> performanceCount)) {
        cout << "Error reading performance count.\n";
        performanceCount = 0;
        return;
    }
    perfFile.ignore(); // Consume newline

    for (int i = 0; i < performanceCount; i++) {
        if (!performances[i].loadFromFile(perfFile)) {
            cout << "Error loading performance " << i << ".\n";
            performanceCount = i;
            break;
        }
    }
    perfFile.close();

    // Load tickets
    ifstream ticketFile("tickets.txt");
    if (!ticketFile) {
        cout << "Tickets file not found. Starting with no tickets.\n";
        return;
    }

    if (!(ticketFile >> ticketCount)) {
        cout << "Error reading ticket count.\n";
        ticketCount = 0;
        return;
    }
    ticketFile.ignore(); // Consume newline

    for (int i = 0; i < ticketCount; i++) {
        if (!tickets[i].loadFromFile(ticketFile)) {
            cout << "Error loading ticket " << i << ".\n";
            ticketCount = i;
            break;
        }
    }
    ticketFile.close();

    cout << "Data loaded successfully: " << performanceCount << " performances and "
        << ticketCount << " tickets.\n";
}
