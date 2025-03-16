#include "DateTime.h"
#include "Perfomance.h"
#include "TheatherManager.h"
#include "Ticket.h"
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
        if (day < 1  day > 31  month < 1  month > 12 
            hour < 0  hour > 23  minute < 0 || minute > 59) {
            cout << "Invalid date/time. Please try again.\n";
        }
        else {
            validInput = true;
        }
    }
}
int main (){

  

  
  return 0;
}
