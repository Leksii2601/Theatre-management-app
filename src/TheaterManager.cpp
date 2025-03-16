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
