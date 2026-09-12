#include "editShortlist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>

#include "pauseAndClear.h"
#include "title_manage.h"
#include "colour.h"
#include "read_user.h"
using namespace std;

void editShortlist(const string& studentID){

	system("cls");
	
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
    bool alreadyExists = false;
    
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name;
        getline(ss, id, ',');
        getline(ss, name, ',');

        if (id == studentID) {
            alreadyExists = true;
            for (int i = 0; i < 3; i++) {
                string opt, status;
                getline(ss, opt, ',');
                getline(ss, status, ',');
                existingIDs[i] = opt;
            }
            break;
        }
    }
    inFile.close();
    
	bool allEmpty = true;
	for (int i = 0; i < 3; i++) {
	    if (!existingIDs[i].empty()) {
	        allEmpty = false;
	        break;
	    }
	}
	
	if (!alreadyExists || allEmpty) {
	    cout << RED << "No shortlist found for this student. Use shortlist first.\n" << RESET;
	    pauseAndClear();
	    return;
	}
    
    cout << CYAN << "Current shortlist for " << studentName << ":\n" << RESET;
    for (int i = 0; i < 3; i++) {
        cout << "Option " << (i + 1) << ": "
             << (existingIDs[i].empty() ? "-" : existingIDs[i]) << "\n";
    }
    
    int choice = -1;
    
	while(true){
		cout << BRIGHT_YELLOW << "\nWhich option do you want to edit? \n('c' to cancel): " << RESET;

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
	    else{
	    	break;
		}
		break;
	}

    while(true){
    	string newID;
    	cout << "Enter new Title ID for Option " << choice 
         << "\n('c' to cancel): ";
	    getline(cin, newID);
		
	    if (newID == "C" || newID == "c") {
	    	cout << BRIGHT_YELLOW << "Cancelled adding.\n" << RESET;
	        pauseAndClear();
	        return; 
	    }
	
	    if (newID.empty()) {
	        cout << RED << "Option cannot be empty. Please try again.\n\n" << RESET;
	        continue;
	    }
	    if (newID[0] == 't') {
	        newID[0] = 'T';
	    }
	    
		bool found = false, duplicate = false;
		    for (int i = 0; i < titleCount; i++) {
		        if (titles[i].id == newID) {
		            found = true;
		            if (titles[i].status != "PENDING") {
		                cout << RED << "This title is selected by others. Try another.\n\n" << RESET;
		                continue;
		            }
		            break;
		        }
		    }
	    if (!found) {
	        cout << RED << "Invalid Title ID.\n\n" << RESET;
	        continue;
	    }
	
	    for (int i = 0; i < 3; i++) {
	        if (existingIDs[i] == newID) {
	            duplicate = true;
	            break;
	        }
	    }
	    if (duplicate) {
	        cout << RED << "You already selected this title in another option.\n\n" << RESET;
	        continue;
	    }
	
	    existingIDs[choice - 1] = newID;
	    cout << GREEN << "Option " << choice << " updated!\n" << RESET;
	    break;
	}
    

    ifstream inFile2("shortlist.txt");
    string lines[1000];
    int lineCount = 0;
    
    while (getline(inFile2, line)) {
        string id;
        stringstream ss(line);
        getline(ss, id, ',');
        if (id != studentID) {
            lines[lineCount++] = line;
        }
    }
    inFile2.close();

    string record = studentID + "," + studentName;
    for (int i = 0; i < 3; i++) {
        if (!existingIDs[i].empty())
            record += "," + existingIDs[i] + ",PENDING";
        else
            record += ",,PENDING";
    }
    lines[lineCount++] = record;

    ofstream outFile("shortlist.txt");
    for (int i = 0; i < lineCount; i++) {
        outFile << lines[i] << "\n";
    }
    outFile.close();

    cout << GREEN << "\nShortlist updated successfully!\n" << RESET;
    for (int i = 0; i < 3; i++) {
        cout << "Option " << (i + 1) << ": "
             << (existingIDs[i].empty() ? "-" : existingIDs[i]) << "\n";
    }

    pauseAndClear();
}
