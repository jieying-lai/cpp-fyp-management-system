#include "modifyTitle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "title_manage.h"

#include "pauseAndClear.h"
#include "colour.h"

using namespace std;

void modifyTitle(const string& supervisorId) {
    
    readTitles(titles, titleCount);

    int lecturerIndexes[MAX_TITLES];
    int lecturerCount = 0;
    
    system("cls");
    cout << BRIGHT_WHITE << "===================================" << RESET << endl;
    cout << BG_BLUE << BRIGHT_WHITE << "\t--- Your Titles ---\n" << RESET ;
    cout << BRIGHT_WHITE << "===================================" << RESET << endl;
    
    for (int i = 0; i < titleCount; i++) {
        if (titles[i].supervisorId == supervisorId) {
            lecturerIndexes[lecturerCount++] = i;
            string displayName = titles[i].name;
        	if (displayName.length() > 30) {
            	displayName = displayName.substr(0, 30) + "...";
        	}

        cout << "[" << lecturerCount << "] " << titles[i].id << " - " << displayName << "\n";
    	}
    }

    if (lecturerCount == 0) {
        cout << BRIGHT_RED << "\nYou have not created any titles yet.\n" << RESET;
        pauseAndClear();
        return;
    }

    string choice;
    int selectedIndex = -1;
    while (true) {
        cout << "\nSelect title number to modify (0 to cancel): ";
        getline(cin, choice);

        if (choice.empty()) {
            cout << BRIGHT_RED << "You pressed Enter without input. Please try again.\n" << RESET;
            continue;
        }

        if (choice == "0") return;

        int num = 0;
        bool isNumber = true;
        
        for (char c : choice) if (!isdigit(c)) isNumber = false;
        if (isNumber) num = stoi(choice);

        if (num >= 1 && num <= lecturerCount) {
            selectedIndex = lecturerIndexes[num - 1];
            break;
        } else {
            cout << BRIGHT_RED << "Invalid choice. Try again.\n" << RESET;
        }
	}
	Title &t = titles[selectedIndex];

    cout <<  BRIGHT_YELLOW << "\nSelected Title: <" << t.name << ">\n" << RESET ;
    
    cout << BRIGHT_GREEN << "Original Description: " << BRIGHT_WHITE << t.description << "\n" << RESET; 
    cout << BRIGHT_GREEN << "Original Field: " << BRIGHT_WHITE << t.field << "\n" << RESET; 
    cout << BRIGHT_GREEN << "Original Prerequisites: " << BRIGHT_WHITE << t.prerequisites << "\n" << RESET; 
    cout << BRIGHT_GREEN << "Original Status: " << BRIGHT_WHITE << t.status << "\n\n" << RESET;

	cout << "[1] Update Title Name\n";
    cout << "[2] Update Description\n";
    cout << "[3] Update Field\n";
    cout << "[4] Update Prerequisites\n";
    cout << BRIGHT_RED << "[5] Delete this Title\n" << RESET;
    cout << BRIGHT_YELLOW << "\n[0] Cancel\n" << RESET;

    string actionStr;
    int action = -1;
    while (true) {
	    cout << "\nEnter your choice: ";
	    getline(cin, actionStr);
	
	    if (actionStr.empty()) {
	        cout << BRIGHT_RED << "You pressed Enter without input. Try again.\n" << RESET;
	        continue;
	    }
	
	    bool isNumber = true;
	    for (char c : actionStr) if (!isdigit(c)) isNumber = false;

        if (isNumber) action = stoi(actionStr);

        if (action >= 0 && action <= 6) break;
	
	    cout << BRIGHT_RED << "Invalid choice!\n" << RESET;
	}

    if (action == 0) {
        cout << BRIGHT_YELLOW <<"\nAction canceled.\n" << RESET;
        pauseAndClear();
        return;
    }

    if (action == 5) {
        string confirm;
        cout << BRIGHT_RED << "Are you sure you want to delete this title <" << BRIGHT_CYAN << t.name << BRIGHT_RED << "> ? (Y/N): " << RESET;
        getline(cin, confirm);
        
        if (!confirm.empty() && (confirm[0] == 'Y' || confirm[0] == 'y')) {
            for (int i = selectedIndex; i < titleCount - 1; i++)
                titles[i] = titles[i + 1];
            titleCount--;
            saveTitles(titles, titleCount);
            cout << BRIGHT_GREEN << "\nTitle deleted successfully!\n" << RESET ;
        } 
		else {
            cout << BRIGHT_YELLOW << "\nDeletion canceled.\n" << RESET;
            pauseAndClear();
            return;
        }
    } 
        
    string newValue;
    cout << "Enter new value (or 'C' to cancel): ";
    getline(cin, newValue);

    if (newValue.empty() || newValue == "C" || newValue == "c") {
        cout << BRIGHT_YELLOW << "\nUpdate canceled.\n" << RESET;
        pauseAndClear();
        return;
    }
	
	cout << BRIGHT_CYAN << "New Value: " << newValue << "\n" << RESET;

    switch (action) {
        case 1: t.name = newValue; break;
        case 2: t.description = newValue; break;
        case 3: t.field = newValue; break;
        case 4: t.prerequisites = newValue; break;
        case 5: t.status = newValue; break;
    }

    saveTitles(titles, titleCount);
    cout << BRIGHT_GREEN << "\nTitle updated successfully!\n" << RESET;
    
    cout << BRIGHT_YELLOW << "\n--- Updated Title Details ---\n" << RESET;
    cout << BRIGHT_GREEN << "ID: " << BRIGHT_WHITE << t.id << "\n" << RESET;
    cout << BRIGHT_GREEN << "Title Name: " << BRIGHT_WHITE << t.name << "\n" << RESET;
    cout << BRIGHT_GREEN << "Description: " << BRIGHT_WHITE << t.description << "\n" << RESET;
    cout << BRIGHT_GREEN << "Field: " << BRIGHT_WHITE << t.field << "\n";
    cout << BRIGHT_GREEN << "Prerequisites: " << BRIGHT_WHITE << t.prerequisites << "\n" << RESET;
    cout << BRIGHT_GREEN << "Status: " << BRIGHT_WHITE << t.status << "\n" << RESET;
        

    pauseAndClear();
}
