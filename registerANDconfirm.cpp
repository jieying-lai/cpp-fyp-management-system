#include "registerANDconfirm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <iomanip>

#include "pauseAndClear.h"
#include "title_manage.h"
#include "colour.h"
#include "read_user.h"

using namespace std;

#define MAX_SHORTLIST 200
struct StudentShortlist {
    string studentId, studentName;
    string opt1, status1;
    string opt2, status2;
    string opt3, status3;
};
struct PendingRequest {
    int studentIndex;
    int titleIndex;
    int option;
};


void registerANDconfirm(const string& supervisorId) {
    readTitles(titles, titleCount);

    int lecturerIndexes[MAX_TITLES];
    int lecturerCount = 0;
    
    ifstream inFile("shortlist.txt");
    if (!inFile) {
        cout << RED << "\nNo shortlist records found.\n" << RESET;
        pauseAndClear();
        return;
    }
    
    StudentShortlist shortlists[MAX_SHORTLIST];
    int shortlistCount = 0;
    string line;
    
    while (getline(inFile, line) && shortlistCount < MAX_SHORTLIST) {
        stringstream ss(line);
        StudentShortlist &s = shortlists[shortlistCount];

        getline(ss, s.studentId, ',');
        getline(ss, s.studentName, ',');
        getline(ss, s.opt1, ',');
        getline(ss, s.status1, ',');
        getline(ss, s.opt2, ',');
        getline(ss, s.status2, ',');
        getline(ss, s.opt3, ',');
        getline(ss, s.status3, ',');

        shortlistCount++;
    }
    inFile.close();

    struct PendingRequest {
        int studentIndex;
        int titleIndex;
        int option; 
    };
    PendingRequest pending[MAX_SHORTLIST];
    int pendingCount = 0;
    
	for (int s = 0; s < shortlistCount; s++) {
	    for (int i = 0; i < titleCount; i++) {
	        if (titles[i].supervisorId != supervisorId) continue;
	
	        if (shortlists[s].opt1 == titles[i].id && shortlists[s].status1 == "PENDING") {
	            pending[pendingCount++] = {s, i, 1};
	        } 
	        else if (shortlists[s].opt2 == titles[i].id && shortlists[s].status2 == "PENDING" &&
	                 shortlists[s].status1 == "REJECTED") {
	            pending[pendingCount++] = {s, i, 2};
	        } 
	        else if (shortlists[s].opt3 == titles[i].id && shortlists[s].status3 == "PENDING" &&
	                 shortlists[s].status1 == "REJECTED" && shortlists[s].status2 == "REJECTED") {
	            pending[pendingCount++] = {s, i, 3};
	        }
	    }
	}
	
	if (pendingCount == 0) {
	    cout << BRIGHT_RED << "\nNo pending student requests for your titles.\n" << RESET;
	    pauseAndClear();
	    return;
	}
	
	system("cls");
	cout << CYAN << "Your Titles with Pending Student Requests:\n\n" << RESET;
	
	cout << BRIGHT_CYAN << left
	     << setw(6)  << "No."
	     << setw(12) << "Title ID"
	     << setw(35) << "Title Name"
	     << setw(20) << "Student"
	     << setw(10) << "Option"
	     << RESET << endl;
	cout << string(90, '-') << endl;
	
	for (int idx = 0; idx < pendingCount; idx++) {
	    int s = pending[idx].studentIndex;
	    int i = pending[idx].titleIndex;
	    int opt = pending[idx].option;
	
	    string studentInfo = shortlists[s].studentId + " - " + shortlists[s].studentName;
	
	    cout << left
	         << setw(6)  << idx + 1
	         << setw(12) << titles[i].id
	         << setw(35) << titles[i].name.substr(0, 33)   // truncate long names
	         << setw(20) << studentInfo.substr(0, 18)      // truncate if too long
	         << setw(10) << opt
	         << endl;
	}
	int choiceIndex;
	while (true) {
	    cout << "\nEnter the number to approve/reject (or 0 to cancel): ";
	
	    string input;
	    getline(cin, input);  
	
	    if (input.empty()) {
	        cout << RED << "Input cannot be empty! Please enter a number.\n" << RESET;
	        continue;
	    }
	
	    stringstream ss(input);
	    if (!(ss >> choiceIndex) || !(ss.eof())) {
	        cout << RED << "Invalid input! Please enter a number.\n" << RESET;
	        continue;
	    }
	    if (choiceIndex == 0) {
	        cout << YELLOW << "\nOperation cancelled. Returning...\n" << RESET;
	        pauseAndClear();
	        return;  
	    }
	
	    if (choiceIndex < 1 || choiceIndex > pendingCount) {
	        cout << RED << "Invalid choice! Enter between 1 and "
	             << pendingCount << ".\n" << RESET;
	        continue;
	    }
	
	    break; 
	}

    PendingRequest selected = pending[choiceIndex - 1];
    StudentShortlist &stud = shortlists[selected.studentIndex];
    Title &title = titles[selected.titleIndex];

    string *statusPtr = nullptr;
    if (selected.option == 1) statusPtr = &stud.status1;
    else if (selected.option == 2) statusPtr = &stud.status2;
    else if (selected.option == 3) statusPtr = &stud.status3;

    string action;
    while (true) {
	    cout << BRIGHT_YELLOW << "Approve or Reject this request? ([a]pprove / [r]eject / Enter to cancel): " << RESET;
	    
	    getline(cin, action);

	    if (action.empty()) {
	        cout << YELLOW << "Action cancelled.\n" << RESET;
	        pauseAndClear();
	        return; 
	    }
	
	    if (action == "a" || action == "A" || action == "R" || action == "r") break;
	    else {
	    	cout << RED << "Invalid choice! PLease try again. " << RESET;
		}
	
	}

    if (action == "A" || action == "a") {
        *statusPtr = "APPROVED";
        title.status = "APPROVED";
	    if (selected.option != 1 && !stud.opt1.empty() && stud.status1 == "PENDING")
	        stud.status1 = "VOID";
	    if (selected.option != 2 && !stud.opt2.empty() && stud.status2 == "PENDING")
	        stud.status2 = "VOID";
	    if (selected.option != 3 && !stud.opt3.empty() && stud.status3 == "PENDING")
	        stud.status3 = "VOID";
	        
        for (int s = 0; s < shortlistCount; s++) {
	        if (s == selected.studentIndex) continue; 
	
	        if (shortlists[s].opt1 == title.id && shortlists[s].status1 == "PENDING")
	            shortlists[s].status1 = "REJECTED";
	        if (shortlists[s].opt2 == title.id && shortlists[s].status2 == "PENDING")
	            shortlists[s].status2 = "REJECTED";
	        if (shortlists[s].opt3 == title.id && shortlists[s].status3 == "PENDING")
	            shortlists[s].status3 = "REJECTED";
	    }

        cout << GREEN << "\nRequest approved for " << stud.studentName << ".\n" << RESET;
	} else {
	    *statusPtr = "REJECTED";
	    cout << YELLOW << "\nRequest rejected for " << stud.studentName << ".\n" << RESET;
	}

    ofstream outTitles("titles.txt");
    for (int i = 0; i < titleCount; i++) {
        outTitles << titles[i].id << "," << titles[i].name << "," << titles[i].description << ","
                  << titles[i].field << "," << titles[i].prerequisites << ","
                  << titles[i].supervisorId << "," << titles[i].status << "\n";
    }
    outTitles.close();

    ofstream outShortlist("shortlist.txt");
    for (int s = 0; s < shortlistCount; s++) {
        outShortlist << shortlists[s].studentId << "," << shortlists[s].studentName << ","
                     << shortlists[s].opt1 << "," << shortlists[s].status1 << ","
                     << shortlists[s].opt2 << "," << shortlists[s].status2 << ","
                     << shortlists[s].opt3 << "," << shortlists[s].status3 << "\n";
    }
    outShortlist.close();

    pauseAndClear();
}
