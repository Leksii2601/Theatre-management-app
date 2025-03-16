#include ""../include/DateTime.h"
#include ""../include/Perfomance.h"
#include ""../include/TheaterManager.h"
#include ""../include/Ticket.h"
void showMenu() {
    cout << "\n==== Theater Management System ====\n";
    cout << "1. Add new performance\n";
    cout << "2. Display all performances\n";
    cout << "3. Display upcoming performances\n";
    cout << "4. Search performances by actor\n";
    cout << "5. Search performances by name\n";
    cout << "6. Search performances by date\n";
    cout << "7. Generate tickets for performance\n";
    cout << "8. Display available seats\n";
    cout << "9. Sell ticket\n";
    cout << "10. Save data\n";
    cout << "11. Load data\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

// Helper function to input and validate date/time
void inputDateTime(int& day, int& month, int& year, int& hour, int& minute) {
    bool validInput = false;

    while (!validInput) {
        cout << "Enter day (1-31): ";
        cin >> day;

        cout << "Enter month (1-12): ";
        cin >> month;

        cout << "Enter year: ";
        cin >> year;

        cout << "Enter hour (0-23): ";
        cin >> hour;

        cout << "Enter minute (0-59): ";
        cin >> minute;

        // Simple validation
        if (day < 1 || day > 31 || month < 1 || month > 12 || 
            hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            cout << "Invalid date/time. Please try again.\n";
        }
        else {
            validInput = true;
        }
    }
}
int main() {
    TheaterManager manager;
    int choice = -1;
    char buffer[MAX_NAME_LENGTH];

    while (choice != 0) {
        showMenu();
        cin >> choice;
        cin.ignore(); // Clear newline

        switch (choice) {
        case 1: { // Add new performance
            Performance newPerf;

            cout << "Enter performance name: ";
            cin.getline(buffer, MAX_NAME_LENGTH);
            newPerf.setName(buffer);

            int day, month, year, hour, minute;
            cout << "Enter performance date and time:\n";
            inputDateTime(day, month, year, hour, minute);
            newPerf.setDateTime(day, month, year, hour, minute);

            cout << "Enter duration (minutes): ";
            int duration;
            cin >> duration;
            newPerf.setDuration(duration);
            cin.ignore();

            cout << "Has intermission? (1 for Yes, 0 for No): ";
            bool hasIntermission;
            cin >> hasIntermission;
            newPerf.setHasIntermission(hasIntermission);
            cin.ignore();

            cout << "Enter number of actors: ";
            int actorCount;
            cin >> actorCount;
            cin.ignore();

            for (int i = 0; i < actorCount; i++) {
                cout << "Enter actor " << (i + 1) << " name: ";
                cin.getline(buffer, MAX_NAME_LENGTH);
                newPerf.addActor(buffer);
            }

            cout << "Enter total seats: ";
            int totalSeats;
            cin >> totalSeats;
            newPerf.setTotalSeats(totalSeats);
            cin.ignore();

            cout << "Enter description: ";
            cin.getline(buffer, MAX_NAME_LENGTH);
            newPerf.setDescription(buffer);

            if (manager.addPerformance(newPerf)) {
                cout << "Performance added successfully.\n";
            }
            else {
                cout << "Failed to add performance. Check constraints (overlaps, actor availability).\n";
            }
            break;
        }

        case 2: // Display all performances
            manager.displayAllPerformances();
            break;

        case 3: // Display upcoming performances
            manager.displayUpcomingPerformances();
            break;

        case 4: { // Search by actor
            cout << "Enter actor name: ";
            cin.getline(buffer, MAX_NAME_LENGTH);
            manager.displayPerformancesByActor(buffer);
            break;
        }

        case 5: { // Search by name
            cout << "Enter performance name or part of name: ";
            cin.getline(buffer, MAX_NAME_LENGTH);
            manager.searchPerformancesByName(buffer);
            break;
        }

        case 6: { // Search by date
            int day, month, year;
            cout << "Enter date to search for:\n";
            cout << "Day: ";
            cin >> day;
            cout << "Month: ";
            cin >> month;
            cout << "Year: ";
            cin >> year;

            manager.searchPerformancesByDate(day, month, year);
            break;
        }

        case 7: { // Generate tickets
            cout << "Enter performance ID: ";
            int perfIndex;
            cin >> perfIndex;

            if (manager.generateTickets(perfIndex)) {
                cout << "Tickets generated successfully.\n";
            }
            else {
                cout << "Failed to generate tickets. Check performance ID and if tickets already exist.\n";
            }
            break;
        }

        case 8: { // Display available seats
            cout << "Enter performance ID: ";
            int perfIndex;
            cin >> perfIndex;

            manager.displayAvailableSeats(perfIndex);
            break;
        }

        case 9: { // Sell ticket
            cout << "Enter performance ID: ";
            int perfIndex;
            cin >> perfIndex;
            cin.ignore();

            cout << "Enter buyer name: ";
            cin.getline(buffer, MAX_NAME_LENGTH);

            cout << "Enter seat number: ";
            int seatNumber;
            cin >> seatNumber;

            if (manager.sellTicket(perfIndex, buffer, seatNumber)) {
                cout << "Ticket sold successfully.\n";
            }
            else {
                cout << "Failed to sell ticket. Check performance ID, seat number, and availability.\n";
            }
            break;
        }

        case 10: // Save data
            manager.saveToFiles();
            break;

        case 11: // Load data
            manager.loadFromFiles();
            break;

        case 0: // Exit
            cout << "Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
