#include "searchTitle.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include "pauseAndClear.h"
#include "title_manage.h"
#include "colour.h"
#include "read_user.h" 

using namespace std;

void searchTitle() {
	readTitles(titles, titleCount);
    string option;
    while (true) {
        system("cls");
        cout << BRIGHT_WHITE << "==================================" << RESET << endl;
        cout << BG_BLUE << BRIGHT_WHITE << "\t--- Search Titles ---\n" << RESET;
        cout << BRIGHT_WHITE << "==================================" << RESET << endl;

        cout << "[1] Search by Title ID\n";
        cout << "[2] Search by Title Name\n";
        cout << "[3] Search by Field\n";
        cout << BRIGHT_YELLOW << "[0] Cancel\n" << RESET;
        cout << "Enter your choice: ";
        getline(cin, option);

        if (option.empty() || option == "0") {
            cout << BRIGHT_YELLOW << "\nSearch canceled.\n" << RESET;
            pauseAndClear();
            return;
        }

        if (option != "1" && option != "2" && option != "3") {
            cout << RED << "\nInvalid choice! Please enter 0-3.\n" << RESET;
            pauseAndClear();
            continue;
        }
        break;
    }

    string keyword;
    cout << BRIGHT_WHITE << "Enter keyword" << BRIGHT_YELLOW" (or enter 'c' to cancel): "<<RESET;
    getline(cin, keyword);

    if (keyword.empty() || keyword == "C" || keyword == "c") {
        cout << BRIGHT_YELLOW << "\nSearch canceled.\n" << RESET;
        pauseAndClear();
        return;
    }

    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    system("cls");
    cout << BRIGHT_WHITE << "\n\t\t\t======================================" << RESET << endl;
    cout << BG_BLUE << BRIGHT_WHITE << "\t\t\t\t--- Search Results ---\n" << RESET;
    cout << BRIGHT_WHITE << "\t\t\t======================================" << RESET << endl;

    cout << BRIGHT_CYAN << left << setw(6) << "No."
         << setw(10) << "ID"
         << setw(62) << "Title Name"
         << setw(12) << "Status" << RESET << endl;
    cout << string(85, '-') << endl;

    int matchedIndexes[MAX_TITLES];
    int matchedCount = 0;

    for (int i = 0; i < titleCount; i++) {
        string data;
        if (option == "1") data = titles[i].id;
        else if (option == "2") data = titles[i].name;
        else if (option == "3") data = titles[i].field;

        string lowerData = data;
        transform(lowerData.begin(), lowerData.end(), lowerData.begin(), ::tolower);

        if (lowerData.find(keyword) != string::npos) {
            matchedIndexes[matchedCount] = i;
            matchedCount++;

            cout << left << setw(6) << matchedCount
                 << setw(10) << titles[i].id
                 << setw(62) << titles[i].name.substr(0, 60)
                 << setw(12) << titles[i].status << endl;
        }
    }

    if (matchedCount == 0) {
        cout << RED << "\nNo matching titles found.\n" << RESET;
        pauseAndClear();
        return;
    }

    int choice;
    while (true) {
    	cout << CYAN << "\nEnter the number to view details [0 to cancel]: " << RESET;
		string line;
	    getline(cin, line);
	    if (!line.empty() && line.back() == '\r') line.pop_back(); // handle CR on Windows
	
	    auto trim = [](string &s) {
	        size_t start = s.find_first_not_of(" \t\n\r");
	        if (start == string::npos) { s.clear(); return; }
	        size_t end = s.find_last_not_of(" \t\n\r");
	        s = s.substr(start, end - start + 1);
	    };
	    trim(line);
	
	    if (line.empty()) {
	        cout << RED << "You pressed Enter without input. Please enter a number.\n" << RESET;
	        continue; 
	    }
	
	    bool allDigits = true;
	    for (char c : line) {
	        if (!isdigit(static_cast<unsigned char>(c))) { allDigits = false; break; }
	    }
	    if (!allDigits) {
	        cout << RED << "Invalid input! Please enter a number.\n" << RESET;
	        continue;
	    }
	
	    try {
	        choice = stoi(line);
	    } catch (...) {
	        cout << RED << "Invalid number. Try again.\n" << RESET;
	        continue;
	    }
	
	    if (choice == 0) {
	        cout << BRIGHT_YELLOW << "\nSelection canceled.\n" << RESET;
	        pauseAndClear();
	        return;
	    }
	
	    if (choice < 1 || choice > matchedCount) {
	        cout << RED << "Invalid choice! Enter between 1 and " << matchedCount << ".\n" << RESET;
	        continue;
	    }
	
	    break;
	}

    int idx = matchedIndexes[choice - 1];
    Title t = titles[idx];

    User users[MAX_USERS];
    int userCount = read_users(users);
    string supervisorName = "N/A";
    string supervisorEmail = "N/A";

    for (int i = 0; i < userCount; i++) {
        if (users[i].id == t.supervisorId) {
            supervisorName = users[i].name;
            supervisorEmail = users[i].email;
            break;
        }
    }

    system("cls");
    cout << BRIGHT_MAGENTA << "\t--- Title Details ---\n" << RESET;
    cout << BRIGHT_CYAN << "Title ID: " << RESET << t.id << endl;
    cout << BRIGHT_CYAN << "Title Name: " << RESET << t.name << endl;
    cout << BRIGHT_CYAN << "Description: " << RESET << t.description << endl;
    cout << BRIGHT_CYAN << "Field: " << RESET << t.field << endl;
    cout << BRIGHT_CYAN << "Prerequisites: " << RESET << t.prerequisites << endl;
    cout << BRIGHT_CYAN << "Supervisor ID: " << RESET << t.supervisorId << endl;
    cout << BRIGHT_CYAN << "Supervisor Name: " << RESET << supervisorName << endl;
    cout << BRIGHT_CYAN << "Supervisor Email: " << RESET << supervisorEmail << endl;
    cout << BRIGHT_CYAN << "Status: " << RESET << t.status << endl;

    pauseAndClear();
}

