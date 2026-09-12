#include "shortlistANDregister.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <algorithm>

#include "pauseAndClear.h"
#include "title_manage.h"
#include "colour.h"
#include "read_user.h"

using namespace std;

void saveShortlist(const string& studentID, const string& studentName, 
                   string existingIDs[3], string existingStatus[3]) {
    ifstream inFile("shortlist.txt");
    string lines[1000];
    int lineCount = 0;
    string line;

    while (getline(inFile, line)) {
        string id;
        stringstream ss(line);
        getline(ss, id, ',');
        if (id != studentID) {
            lines[lineCount++] = line;
        }
    }
    inFile.close();

    string record = studentID + "," + studentName;
    for (int i = 0; i < 3; i++) {
        if (!existingIDs[i].empty()) {
            string status = existingStatus[i].empty() ? "PENDING" : existingStatus[i];
            record += "," + existingIDs[i] + "," + status;
        } else {
            record += ",,";
        }
    }
    lines[lineCount++] = record;

    ofstream outFile("shortlist.txt");
    for (int i = 0; i < lineCount; i++) {
        outFile << lines[i] << "\n";
    }
    outFile.close();
}

bool assignTitleToOption(string& targetID, string& targetStatus, 
                         int optionNo, string existingIDs[3], string existingStatus[3], bool isLast = false) {
    while (true) {
        string newID;
        cout << BRIGHT_WHITE << "\nEnter new Title ID for Option " << optionNo
             << RESET << "\n(press ENTER to skip): ";
        getline(cin, newID);

        if (newID.empty()) {
            cout << BRIGHT_YELLOW << "Skipped Option " << optionNo << ".\n" << RESET;
            return true;
        }

        if (newID[0] == 't') newID[0] = 'T';

        int idx = findTitleIndex(newID);
        if (idx == -1) {
            cout << RED << "Invalid Title ID.\n\n" << RESET;
            continue;
        }

        if (titles[idx].status == "APPROVED") {
            cout << RED << "This title is selected by others. Try another.\n\n" << RESET;
            continue;
        }

        bool alreadySelected = false;
        for (int i = 0; i < 3; i++) {
            if (existingIDs[i] == newID) {
                cout << RED << "You already selected this title in another option.\n\n" << RESET;
                alreadySelected = true;
                break;
            }
        }
        if (alreadySelected) continue;

        targetID = newID;
        targetStatus = "PENDING";
        cout << GREEN << "Option " << optionNo << " updated!\n" << RESET;

        int writePos = 0;
        for (int i = 0; i < 3; i++) {
            if (!existingIDs[i].empty()) {
                if (i != writePos) {
                    existingIDs[writePos] = existingIDs[i];
                    existingStatus[writePos] = existingStatus[i];
                    existingIDs[i] = "";
                    existingStatus[i] = "";
                }
                writePos++;
            }
        }
		if (isLast) pauseAndClear(); 
        return true;
    }
}

void shortlistANDregister(const string& studentID) {
    readTitles(titles, titleCount);
    User users[MAX_USERS];
    int count = read_users(users);

    string studentName = "";
    for (int i = 0; i < count; i++) {
        if (users[i].id == studentID) {
            studentName = users[i].name;
            break;
        }
    }

    ifstream inFile("shortlist.txt");
    string line;
    string existingIDs[3] = {"", "", ""};
    string existingStatus[3] = {"", "", ""};
    if (inFile) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, name, opt1, status1, opt2, status2, opt3, status3;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, opt1, ','); getline(ss, status1, ',');
            getline(ss, opt2, ','); getline(ss, status2, ',');
            getline(ss, opt3, ','); getline(ss, status3, ',');

            if (id == studentID) {
                existingIDs[0] = opt1; existingStatus[0] = status1;
                existingIDs[1] = opt2; existingStatus[1] = status2;
                existingIDs[2] = opt3; existingStatus[2] = status3;
                break;
            }
        }
    }

    while (true) {
        system("cls");

        cout << BRIGHT_WHITE << "================================================" << RESET << endl;
        cout << BG_BLUE << BRIGHT_WHITE << "\t--- Shortlist and Register FYP ---\n" << RESET;
        cout << BRIGHT_WHITE << "================================================" << RESET << endl;

        cout << CYAN << "Currently selected:\n" << RESET;
        for (int i = 0; i < 3; i++) {
            if (existingIDs[i].empty()) {
                cout << "Option " << (i + 1) << ": -" << "\n";
            } else {
                cout << "Option " << (i + 1) << ": "
                     << existingIDs[i] << " (" << existingStatus[i] << ")\n";
            }
        }

        cout <<BRIGHT_WHITE <<  "\n[1] Add shortlist\n";
        cout << "[2] Edit shortlist FYP\n";
        cout << "[3] Delete shortlist\n";
        cout << BRIGHT_YELLOW << "\n[0] Cancel\n" << RESET;
        cout << "Enter your choice: ";

        string option;
        getline(cin, option);

        if (option.empty()) {
            cout << RED << "\nYou pressed Enter without selecting anything. Action canceled.\n" << RESET;
            pauseAndClear();
            return;
        }

        if (option == "0") {
            cout << BRIGHT_YELLOW << "\nAction canceled.\n" << RESET;
            pauseAndClear();
            return;
        }

		if (option == "1") {
		    bool hasApproved = false;
		    for (int i = 0; i < 3; i++) {
		        if (existingStatus[i] == "APPROVED") {
		            hasApproved = true;
		            break;
		        }
		    }
		
		    if (hasApproved) {
		        cout << GREEN << "\nYou already have an APPROVED title. You cannot add more.\n" << RESET;
		        pauseAndClear();
		        continue;
		    }
			for (int opt = 0; opt < 3; opt++) {
			    if (!existingIDs[opt].empty()) continue;
			
			    bool isLast = (opt == 2);  
			    bool success = assignTitleToOption(
			        existingIDs[opt], existingStatus[opt], opt + 1,
			        existingIDs, existingStatus, isLast
			    );
			
			    if (success) {
			        pauseAndClear();
			        break;            
			    } else {
			        break;         
			    }
			}

		}
		else if (option == "2") {
		    bool hasApproved = false;
		    for (int i = 0; i < 3; i++) {
		        if (existingStatus[i] == "APPROVED") {
		            hasApproved = true;
		            break;
		        }
		    }
		
		    if (hasApproved) {
		        cout << GREEN << "\nYou already have an APPROVED title. No edits allowed.\n" << RESET;
		        pauseAndClear();
		        continue;
		    }
		
		    int choice = -1;
		    while (true) {
		        cout << BRIGHT_YELLOW << "\nSelect option [1-3] to edit (C to cancel):" << RESET;
		        string choiceStr;
		        getline(cin, choiceStr);
		
		        if (choiceStr == "c" || choiceStr == "C") {
		            cout << BRIGHT_YELLOW << "Edit cancelled.\n" << RESET;
		            pauseAndClear();
		            return;
		        }
		
		        if (choiceStr.empty() || choiceStr.size() > 1 || !isdigit(choiceStr[0])) {
		            cout << RED << "Invalid input. Please enter 1, 2, or 3.\n\n" << RESET;
		            continue;
		        }
		
		        choice = stoi(choiceStr);
		        if (choice < 1 || choice > 3 || existingIDs[choice - 1].empty()) {
		            cout << RED << "Invalid choice. Only filled options can be edited.\n\n" << RESET;
		            continue;
		        }
		        if (existingStatus[choice - 1] == "REJECTED") {
		            cout << RED << "Option " << choice << " has status [REJECTED]. You cannot edit this option.\n" << RESET;
		            pauseAndClear();
		            choice = -1;
		        }
		        break;
		    }
		
		    if (choice != -1) {
		        bool success = assignTitleToOption(
		            existingIDs[choice - 1],
		            existingStatus[choice - 1],
		            choice,
		            existingIDs,
		            existingStatus
		        );
		        if (success) 
            		pauseAndClear();
		    }
		}

        // ========== DELETE ==========
		else if (option == "3") {
		    bool hasApproved = false;
		    for (int i = 0; i < 3; i++) {
		        if (existingStatus[i] == "APPROVED") {
		            hasApproved = true;
		            break;
		        }
		    }
		
		    if (hasApproved) {
		        cout << GREEN << "\nYou already have an APPROVED title. Deletion is not allowed.\n" << RESET;
		        pauseAndClear();
		        continue;
		    }
		
		    int choice = -1;
		    while (true) {
		        cout << BRIGHT_CYAN
		             << "\nWhich option do you want to delete? [1, 2, or 3, 'c' to cancel] : "
		             << RESET;
		        string choiceStr;
		        getline(cin, choiceStr);
		
		        if (choiceStr == "c" || choiceStr == "C") {
		            cout << BRIGHT_YELLOW << "Delete cancelled.\n" << RESET;
		            pauseAndClear();
		            break;
		        }
		
		        if (choiceStr.empty() || choiceStr.size() > 1 || !isdigit(choiceStr[0])) {
		            cout << RED << "Invalid input. Please enter 1, 2, or 3.\n\n" << RESET;
		            continue;
		        }
		
		        choice = stoi(choiceStr);
		        if (choice < 1 || choice > 3) {
		            cout << RED << "Invalid choice. You can only delete Option 1, 2, or 3.\n\n" << RESET;
		            continue;
		        }
		
		        if (existingIDs[choice - 1].empty()) {
		            cout << RED << "Option " << choice << " is empty. Nothing to delete.\n\n" << RESET;
		            continue;
		        }
		
		        if (existingStatus[choice - 1] != "PENDING") {
		            cout << RED << "Option " << choice << " cannot be deleted because it is "
		                 << existingStatus[choice - 1] << ".\n\n" << RESET;
		            continue;
		        }
		
		        string confirm;
		        cout << BRIGHT_RED << "Are you sure you want to delete Option " << choice << BRIGHT_WHITE
		             << " [" << existingIDs[choice - 1] << "]? " << BRIGHT_RED << "(Y/N): " << RESET;
		        getline(cin, confirm);
		
		        if (!confirm.empty() && (confirm[0] == 'Y' || confirm[0] == 'y')) {
		            for (int i = choice - 1; i < 2; i++) {
		                existingIDs[i] = existingIDs[i + 1];
		                existingStatus[i] = existingStatus[i + 1];
		            }
		
		            existingIDs[2] = "";
		            existingStatus[2] = "";
		
		            cout << GREEN << "Option " << choice << " deleted successfully!\n" << RESET;
		            pauseAndClear();
		        } else {
		            cout << BRIGHT_YELLOW << "\nDeletion cancelled.\n" << RESET;
		            pauseAndClear();
		        }
		        break;
		    }
		}

        else {
            cout << RED << "Invalid choice. Please try again.\n" << RESET;
            pauseAndClear();
            continue;
        }
        saveShortlist(studentID, studentName, existingIDs, existingStatus);
    }
}

