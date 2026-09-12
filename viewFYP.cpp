#include "viewFYP.h"
#include "aboutMarks.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>

#include "pauseAndClear.h"
#include "title_manage.h"
#include "colour.h"
#include "read_user.h"

using namespace std;

void viewFYP(const string& userId, bool isLecturer) {
	User users[MAX_USERS];
	int userCount = read_users(users);
	
	auto getUserName = [&](const string& id) -> string {
	    for (int i = 0; i < userCount; i++) {
	        if (users[i].id == id) return users[i].name;
	    }
	    return "Unknown";
	};
	
    MarksRecord records[MAX_MARKS];
    int count = 0;
    readMarks(records, count);
	string searchId;
	    if (isLecturer) {
	      
	        cout << BRIGHT_WHITE << "\n\tStudents you have graded:\n" << RESET;
	        int listIndex = 0;
	        int indexes[MAX_MARKS];
	        for (int i = 0; i < count; i++) {
	            if (records[i].supervisorId == userId || records[i].moderatorId == userId) {
	                cout << "[" << listIndex + 1 << "] " << records[i].studentId 
	                     << " - " << records[i].studentName << "\n";
	                indexes[listIndex] = i;
	                listIndex++;
	            }
	        }
	
	        if (listIndex == 0) {
	            cout << BRIGHT_RED << "You have not graded any student yet.\n" << RESET;
	            pauseAndClear();
	            return;
	        }
	
	        string choiceStr;
	        int choice = 0;
	        while (true) {
	            cout << BRIGHT_YELLOW << "Enter number to view student (or C to cancel): " << RESET;
	            getline(cin, choiceStr);
	
	            if (choiceStr == "C" || choiceStr == "c") return;
	
	            bool isNumber = !choiceStr.empty() && all_of(choiceStr.begin(), choiceStr.end(), ::isdigit);
	            if (!isNumber) {
	                cout << RED << "Invalid input. Enter a number.\n" << RESET;
	                continue;
	            }
	
	            choice = stoi(choiceStr);
	            if (choice < 1 || choice > listIndex) {
	                cout << RED << "Invalid selection. Choose between 1 and " << listIndex << ".\n" << RESET;
	                continue;
	            }
	            break;
	        }
	
	        searchId = records[indexes[choice - 1]].studentId;
	    } else {
	        searchId = userId;
	    }

	bool found = false;
    for (int i = 0; i < count; i++) {
        MarksRecord &r = records[i];

        if (isLecturer && !(r.supervisorId == userId || r.moderatorId == userId)) continue;
        if (r.studentId != searchId) continue;

        found = true;
        system("cls");

        cout << BRIGHT_WHITE << "\t=======================================" << RESET << endl;
        cout << BG_BLUE << BRIGHT_WHITE << "\t\t--- FYP Result for " << r.studentName << " ---\n" << RESET;
        cout << BRIGHT_WHITE << "\t=======================================" << RESET << endl;

		cout << BRIGHT_CYAN << "Student ID     : " << RESET << r.studentId << "\n"
		     << BRIGHT_CYAN << "Student Name   : " << RESET << r.studentName << "\n"
		     << BRIGHT_CYAN << "Title ID       : " << RESET << r.titleId << "\n"
		     << BRIGHT_CYAN << "Title Name     : " << RESET << r.titleName << "\n"
		     << BRIGHT_CYAN << "Supervisor ID  : " << RESET << r.supervisorId << "\n"
		     << BRIGHT_CYAN << "Supervisor Name: " << RESET << getUserName(r.supervisorId) << "\n"
		     << BRIGHT_CYAN << "Moderator ID   : " << RESET << r.moderatorId << "\n"
		     << BRIGHT_CYAN << "Moderator Name : " << RESET << getUserName(r.moderatorId) << "\n\n";
				     
        cout << BRIGHT_YELLOW << left << setw(30) << "Component"
		     << setw(15) << "Supervisor"
		     << setw(15) << "Moderator"
		     << BRIGHT_RED << setw(10) << (isLecturer ? "Difference" : "") << "\n" << RESET;
		cout << string(70, '-') << "\n";

        auto calcAvg = [](int sup, int mod) -> double {
            if (sup >= 0 && mod >= 0) return (sup + mod) / 2.0;
            else if (sup >= 0) return sup;
            else if (mod >= 0) return mod;
            return 0;
        };

		auto printMark = [&](int sup, int mod, const std::string& comp, double &avg) {
            string supStr = (sup >= 0) ? to_string(sup) : "Not Graded";
            string modStr = (mod >= 0) ? to_string(mod) : "Not Graded";
            int diff = (sup >= 0 && mod >= 0) ? abs(sup - mod) : 0;

            avg = (sup >= 0 && mod >= 0) ? (sup + mod) / 2.0 : (sup >= 0 ? sup : (mod >= 0 ? mod : 0));

            cout << left << setw(30) << comp
                 << setw(15) << supStr
                 << setw(15) << modStr;

            if (isLecturer) {
                if (diff > 5) cout << RED << "Alert!" << RESET;
                else cout << setw(10) << diff;
            }
            cout << "\n";
        };
        
        auto printEffort = [&](int sup, const std::string& comp, double &avg) {
	    string supStr = (sup >= 0) ? to_string(sup) : "Not Graded";
	    string modStr = "-"; 
	    avg = sup;      
	
	    cout << left << setw(30) << comp
	         << setw(15) << supStr
	         << setw(15) << modStr << "\n";
	};


        printMark(r.fyp1_report_s, r.fyp1_report_m, "FYP1 Report       (15%)", r.fyp1_report_avg);
        printMark(r.fyp1_pres_s, r.fyp1_pres_m, 	"FYP1 Presentation (10%)", r.fyp1_pres_avg);
        printEffort(r.fyp1_effort_s, 				"FYP1 Effort       ( 5%)", r.fyp1_effort_avg);

        printMark(r.fyp2_report_s, r.fyp2_report_m, "FYP2 Report       (20%)", r.fyp2_report_avg);
        printMark(r.fyp2_demo_s, r.fyp2_demo_m, 	"FYP2 Demo         (35%)", r.fyp2_demo_avg);
        printMark(r.fyp2_pres_s, r.fyp2_pres_m, 	"FYP2 Presentation (10%)", r.fyp2_pres_avg);
        printEffort(r.fyp2_effort_s, 				"FYP2 Effort       ( 5%)", r.fyp2_effort_avg);

        cout << string(70, '-') << "\n";

        r.fyp1_total = r.fyp1_report_avg + r.fyp1_pres_avg + r.fyp1_effort_avg;
        r.fyp2_total = r.fyp2_report_avg + r.fyp2_demo_avg + r.fyp2_pres_avg + r.fyp2_effort_avg;
        r.overall = r.fyp1_total + r.fyp2_total;
        string grade = getLetterGrade(r.overall);

        cout << BRIGHT_GREEN << fixed << setprecision(2);
        cout << "FYP1 Total: " << r.fyp1_total << "\n";
        cout << "FYP2 Total: " << r.fyp2_total << "\n";
        cout << "Overall Total: " << r.overall << "\n";
        cout << "Grade: " << grade << RESET << "\n\n";

        saveMarks(records, count);
    }

    if (!found) {
        cout << BRIGHT_RED << "No records found.\n" << RESET;
    }

    pauseAndClear();
}

