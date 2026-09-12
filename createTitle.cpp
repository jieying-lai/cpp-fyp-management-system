#include "createTitle.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include "title_manage.h"

#include "pauseAndClear.h"
#include "colour.h"

using namespace std;

// Helper to get validated input
string getInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);

        while (!input.empty() && isspace(input.front())) input.erase(0,1);
        while (!input.empty() && isspace(input.back())) input.pop_back();

        if (input.empty()) {
            cout << BRIGHT_RED << "Input cannot be empty. Please enter again.\n" << RESET;
        } else if (input == "c" || input == "C") {
            return "";  // cancel
        }
    } while (input.empty());

    return input;
}

void createTitle(const string& supervisorId) {
    system("cls");
    Title t;

    cout << BRIGHT_WHITE << "=====================================" << RESET << endl;
    cout << BG_BLUE << BRIGHT_WHITE << "\t--- Add New Title ---\n" << RESET ;
    cout << BRIGHT_WHITE << "=====================================" << RESET << endl;
    cout << BRIGHT_YELLOW << "(Type 'c' anytime to cancel)\n\n" << RESET;

    t.id = generateNextId();
    t.supervisorId = supervisorId;
    t.status = "PENDING";

    string input = getInput("\nEnter Title Name: ");
    if (input.empty()) { cout << BRIGHT_YELLOW << "Adding title canceled.\n" << RESET; pauseAndClear(); return; }
    t.name = input;

    input = getInput("\nEnter Description: ");
    if (input.empty()) { cout << BRIGHT_YELLOW << "Adding title canceled.\n" << RESET; pauseAndClear(); return; }
    t.description = input;

    input = getInput("\nEnter Field: ");
    if (input.empty()) { cout << BRIGHT_YELLOW << "Adding title canceled.\n" << RESET; pauseAndClear(); return; }
    t.field = input;

    input = getInput("\nEnter Prerequisites: ");
    if (input.empty()) { cout << BRIGHT_YELLOW << "Adding title canceled.\n" << RESET; pauseAndClear(); return; }
    t.prerequisites = input;

    // Add to global array and save
    if (titleCount < MAX_TITLES) {
        titles[titleCount++] = t;
        saveTitles(titles, titleCount); // safe save
    } else {
        cout << BRIGHT_RED << "Error: Title list is full!\n" << RESET;
        pauseAndClear();
        return;
    }

    cout << BRIGHT_GREEN << "\nFYP Title added successfully!\n" << RESET;
    cout << BRIGHT_WHITE << "===================================\n" << RESET;
    cout << BG_BLUE << BRIGHT_WHITE << "\t--- New FYP Added ---\n" << RESET ;
    cout << BRIGHT_WHITE << "===================================\n" << RESET;

    cout << "ID: " << t.id << "\n";
    cout << "Title Name: " << t.name << "\n";
    cout << "Description: " << t.description << "\n";
    cout << "Field: " << t.field << "\n";
    cout << "Prerequisites: " << t.prerequisites << "\n";
    cout << "Supervisor ID: " << t.supervisorId << "\n";
    cout << "Status: " << t.status << "\n";

    pauseAndClear();
}

