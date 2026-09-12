#include "submitFYP.h"
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

struct StudentShortlist {
    string studentId, studentName;
    string opt1, status1;
    string opt2, status2;
    string opt3, status3;
};

void submitFYP(const string &id) {
    // ===== Read shortlist =====
    ifstream shortlistFile("shortlist.txt");
    if (!shortlistFile) {
        cout << RED << "No shortlist records found.\n" << RESET;
        pauseAndClear();
        return;
    }

    StudentShortlist record;
    bool found = false;

    string line;
    while (getline(shortlistFile, line)) {
        stringstream ss(line);
        StudentShortlist s;
        getline(ss, s.studentId, ',');
        getline(ss, s.studentName, ',');
        getline(ss, s.opt1, ',');
        getline(ss, s.status1, ',');
        getline(ss, s.opt2, ',');
        getline(ss, s.status2, ',');
        getline(ss, s.opt3, ',');
        getline(ss, s.status3);

        if (s.studentId == id) {
            record = s;
            found = true;
            break;
        }
    }
    shortlistFile.close();

    if (!found) {
        cout << RED << "No shortlist record found.\n" << RESET;
        pauseAndClear();
        return;
    }
       // ===== Find APPROVED title =====
    string approvedId, approvedStatus;
    if (record.status1 == "APPROVED") approvedId = record.opt1;
    else if (record.status2 == "APPROVED") approvedId = record.opt2;
    else if (record.status3 == "APPROVED") approvedId = record.opt3;
    
    if (approvedId.empty()) {
        cout << YELLOW << "You do not have any approved titles yet.\n" << RESET;
        pauseAndClear();
        return;
    }

	// ===== Check if already submitted =====
    ifstream marksCheck("marks.txt");
    string checkLine;
    bool alreadySubmitted = false;
    while (getline(marksCheck, checkLine)) {
        stringstream ss(checkLine);
        string studentId, titleId;
        getline(ss, studentId, ','); // studentId
        getline(ss, checkLine, ','); // studentName (skip)
        getline(ss, titleId, ',');   // titleId
        if (studentId == id && titleId == approvedId) {
            alreadySubmitted = true;
            break;
        }
    }
    marksCheck.close();
    
    if (alreadySubmitted) {
        cout << YELLOW << "You have already submitted this approved FYP!\n" << RESET;
        pauseAndClear();
        return;
    }

	readTitles(titles, titleCount);

	string titleName, supervisorId, supervisorName;
	for (int i = 0; i < titleCount; i++) {
	    if (titles[i].id == approvedId) {
	        titleName = titles[i].name;
	        supervisorId = titles[i].supervisorId;
	        break;
	    }
	}
	
	User users[MAX_USERS];
	int userCount = read_users(users);
	for (int i = 0; i < userCount; i++) {
	    if (users[i].id == supervisorId) {
	        supervisorName = users[i].name;
	        break;
	    }
	}

    // ===== Show student + title info =====
    cout << CYAN << "\nApproved Title Found!\n" << RESET;
    cout << BRIGHT_GREEN << "Student ID: " << BRIGHT_WHITE << record.studentId << "\n";
    cout << BRIGHT_GREEN << "Student Name: " << BRIGHT_WHITE << record.studentName << "\n";
    cout << BRIGHT_GREEN << "Title ID: " << BRIGHT_WHITE <<approvedId << "\n";
    cout << BRIGHT_GREEN << "Title Name: " << BRIGHT_WHITE <<titleName << "\n";
    cout << BRIGHT_GREEN << "Supervisor ID: " << BRIGHT_WHITE << supervisorId << "\n";
    cout << BRIGHT_GREEN << "Supervisor Name: " << BRIGHT_WHITE << supervisorName << "\n";
    cout << BRIGHT_GREEN << "Moderator ID: " << BRIGHT_WHITE << "(Not assigned yet)\n" << RESET;
    cout << BRIGHT_GREEN << "Moderator Name: " << BRIGHT_WHITE << "(Not assigned yet)\n" << RESET;

    // ===== Confirm submission =====
    string confirm;
	while (true) {
	    cout << BRIGHT_YELLOW << "\nDo you want to submit? (Y/N): " << RESET;
	    getline(cin, confirm);
	
	    if (confirm.empty()) {
	        cout << RED << "Input cannot be empty. Please enter Y or N.\n" << RESET;
	        continue;
	    }
	
	    char c = tolower(confirm[0]);
	    if (c == 'y') {
	        break; 
	    } else if (c == 'n') {
	        cout << BRIGHT_YELLOW << "Submission cancelled.\n" << RESET;
	        pauseAndClear();
	        return;
	    } else {
	        cout << RED << "Invalid input. Please enter Y or N.\n" << RESET;
	    }
	}

    bool newFile = false;
    ifstream testFile("marks.txt");
    if (!testFile.good()) newFile = true;
    testFile.close();

    ofstream marksFile("marks.txt", ios::app);
    if (!marksFile) {
        cout << RED << "Error creating marks file.\n" << RESET;
        return;
    }

    if (newFile) {
        marksFile << "StudentID,StudentName,TitleID,TitleName,SupervisorID,ModeratorID,"
                  << "FYP1_Report_S,FYP1_Report_M,FYP1_Report_Avg,"
                  << "FYP1_Pres_S,FYP1_Pres_M,FYP1_Pres_Avg,"
                  << "FYP1_Effort_S,FYP1_Effort_M,FYP1_Effort_Avg,"
                  << "FYP1_Total,"
                  << "FYP2_Report_S,FYP2_Report_M,FYP2_Report_Avg,"
                  << "FYP2_Demo_S,FYP2_Demo_M,FYP2_Demo_Avg,"
                  << "FYP2_Pres_S,FYP2_Pres_M,FYP2_Pres_Avg,"
                  << "FYP2_Effort_S,FYP2_Effort_M,FYP2_Effort_Avg,"
                  << "FYP2_Total,Overall\n";
    }

    // ===== Write blank marks entry =====
    marksFile << record.studentId << ","
              << record.studentName << ","
              << approvedId << ","
              << titleName << ","
              << supervisorId << ","
              << "" << ","   // Moderator blank
              << 0 << "," << 0 << "," << 0 << ","  // FYP1_Report
              << 0 << "," << 0 << "," << 0 << ","  // FYP1_Pres
              << 0 << "," << 0 << "," << 0 << ","  // FYP1_Effort
              << 0 << ","                          // FYP1_Total
              << 0 << "," << 0 << "," << 0 << ","  // FYP2_Report
              << 0 << "," << 0 << "," << 0 << ","  // FYP2_Demo
              << 0 << "," << 0 << "," << 0 << ","  // FYP2_Pres
              << 0 << "," << 0 << "," << 0 << ","  // FYP2_Effort
              << 0 << ","                          // FYP2_Total
              << 0                                 // Overall
              << "\n";

    marksFile.close();

    cout << GREEN << "\nFYP successfully submitted! Marks record created.\n" << RESET;
    pauseAndClear();
}

