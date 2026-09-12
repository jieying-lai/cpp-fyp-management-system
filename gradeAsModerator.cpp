// gradeAsModerator.cpp
#include "gradeAsModerator.h"
#include "aboutMarks.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <iomanip>
#include <algorithm>

#include "pauseAndClear.h"
#include "title_manage.h"
#include "colour.h"
#include "read_user.h"

using namespace std;

// Display current marks for moderator (excluding Effort)
void showModeratorMarks(const MarksRecord &r) {
    cout << BRIGHT_CYAN << "\n--- Current Marks (Moderator View) ---\n" << RESET;
    
    cout << BRIGHT_WHITE << left << setw(25)  << "Component (30% + 70%)" 
         << "| " << setw(15) << "Moderator" << RESET <<"\n";
    cout << string(45, '-') << "\n";
    
    cout << left << setw(25) << "FYP1 Report       (15%)" 
         << "| " << r.fyp1_report_m << "\n";
    cout << left << setw(25) << "FYP1 Presentation (10%)" 
         << "| " << r.fyp1_pres_m << "\n";
    
    cout << string(45, '-') << "\n";

    cout << left << setw(25) << "FYP2 Report       (20%)" 
         << "| " << r.fyp2_report_m << "\n";
    cout << left << setw(25) << "FYP2 Demo         (35%)" 
         << "| " << r.fyp2_demo_m << "\n";
    cout << left << setw(25) << "FYP2 Presentation (10%)" 
         << "| " << r.fyp2_pres_m << "\n";
    
    cout << string(45, '-') << "\n";
}

// Main Moderator Grading
void gradeAsModerator(const string& moderatorId) {
    MarksRecord records[MAX_MARKS];
    int count = 0;
    readMarks(records, count);

    int availableIndexes[MAX_MARKS], selectedIndexes[MAX_MARKS];
    int nAvailable = 0, nSelected = 0;

    system("cls");
    cout << BRIGHT_WHITE << "\t===============================================" << RESET << endl;
    cout << BG_BLUE << BRIGHT_WHITE << "\t\t--- FYP Grading (Moderator) ---\n" << RESET;
    cout << BRIGHT_WHITE << "\t===============================================" << RESET << endl;
    
    for (int i = 0; i < count; i++) {
        if (!records[i].supervisorId.empty() && records[i].supervisorId != moderatorId) {
            if (records[i].moderatorId.empty()) {
                availableIndexes[nAvailable++] = i;
            } else if (records[i].moderatorId == moderatorId) {
                selectedIndexes[nSelected++] = i;
            }
        }
    }
    
    if (nAvailable == 0 && nSelected == 0) {
        cout << BRIGHT_RED << "No projects available for moderator grading.\n" << RESET;
        pauseAndClear();
        return;
    }

	if (nAvailable > 0) {
        cout << CYAN << "\n--- Projects available for selection ---\n" << RESET;
        cout << BRIGHT_WHITE << left 
             << setw(5) << "No." 
             << setw(15) << "Student ID" 
             << setw(20) << "Student Name" 
             << setw(12) << "Title ID" 
             << setw(30) << "Title Name" << "\n";
        cout << string(100, '-') << "\n";

        for (int i = 0; i < nAvailable; i++) {
        auto &r = records[availableIndexes[i]];

        // truncate title name if too long
        string title = r.titleName;
        if (title.length() > 27) {
            title = title.substr(0, 27) + "...";
        }

        cout << left << setw(5)  << (i + 1)
             << setw(15) << r.studentId
             << setw(20) << r.studentName
             << setw(12) << r.titleId
             << setw(30) << title
             << "\n";
        }
    }
    
    if (nSelected > 0) {
        cout << CYAN << "\n--- Projects you have already selected ---\n" << RESET;
        cout << BRIGHT_WHITE << left 
             << setw(5) << "No." 
             << setw(15) << "Student ID" 
             << setw(20) << "Student Name" 
             << setw(12) << "Title ID" 
             << setw(30) << "Title Name" << "\n";
        cout << string(100, '-') << "\n";

        for (int i = 0; i < nSelected; i++) {
            auto &r = records[selectedIndexes[i]];
            cout << left << setw(5) << (i + 1 + nAvailable)
                 << setw(15) << r.studentId
                 << setw(20) << r.studentName
                 << setw(12) << r.titleId
                 << setw(30) << r.titleName << "\n";
        }
    }

    // Select a project
    int choice = 0;
    string choiceStr;
    int totalProjects = nAvailable + nSelected;
    
    while (true) {
        cout << "\nSelect a project " << BRIGHT_YELLOW << "(or C to cancel): " << RESET;
        getline(cin, choiceStr);

        if (choiceStr == "C" || choiceStr == "c") {
            cout << BRIGHT_YELLOW << "Cancelled.\n" << RESET;
            pauseAndClear();
            return;
        }

        bool isNumber = !choiceStr.empty() && all_of(choiceStr.begin(), choiceStr.end(), ::isdigit);
        if (!isNumber) {
            cout << RED << "Invalid input. Please enter a number.\n" << RESET;
            continue;
        }

        choice = stoi(choiceStr);
        if (choice < 1 || choice > totalProjects) {
            cout << RED << "Invalid selection. Please choose between 1 and " << totalProjects << ".\n" << RESET;
            continue;
        }
        break;
    }
	MarksRecord &r = (choice <= nAvailable) ? records[availableIndexes[choice - 1]]
                                           : records[selectedIndexes[choice - nAvailable - 1]];

	bool isNewSelection = (choice <= nAvailable && r.moderatorId.empty());
	
	if (isNewSelection) {
	    
	    string confirm;
	    while (true) {
	        cout << CYAN << "You selected:\n";
	        cout << BRIGHT_WHITE << "FYP ID: " << r.titleId << "\nTitle: " << r.titleName 
	             << "\nStudent ID: " << r.studentId << "\nName: " << r.studentName << "\n";
	        cout << BRIGHT_YELLOW << "Confirm grade as moderator? (Y/N): " << RESET;
	        getline(cin, confirm);
	
	        if (confirm == "Y" || confirm == "y") {
	            r.moderatorId = moderatorId;
	            cout << GREEN << "Moderator assigned to this project.\n" << RESET;
	            pauseAndClear();
	            break;
	        } else if (confirm == "N" || confirm == "n") {
	            cout << "Cancelled. Returning to FYP selection.\n";
	            pauseAndClear();
	            return;
	        } else {
	            cout << "Invalid input. Enter Y or N.\n";
	        }
	    }
	} else {
	    
	    cout << BRIGHT_YELLOW << "You are editing marks for a previously selected project.\n" << RESET;
	}

    // Grading loop
    while (true) {
        system("cls");
        cout << CYAN << "Selected Project:\n" << RESET;
        cout << BRIGHT_WHITE << "ID: " << r.studentId << "\nName: " << r.studentName
             << "\nTitle: " << r.titleId << " < " << r.titleName << " >\n";

        showModeratorMarks(r);
        cout << BRIGHT_YELLOW << "\nWhich FYP component do you want to grade?\n"
             << BRIGHT_WHITE << "\n[1] FYP 1\n[2] FYP 2\n\n" << BRIGHT_YELLOW << "[0] Cancel\n"
			 << BRIGHT_GREEN << "Choice: " << RESET;
			 
		    string fypChoice;
		    getline(cin, fypChoice);
		    
		    if (fypChoice == "0") return;
		    
		    if (fypChoice.empty()) {
	            cout << RED << "\nYou pressed Enter without selecting anything.\nPlease try again.\n" << RESET;
	            pauseAndClear();
				continue;
	        }
		
		    if (fypChoice != "1" && fypChoice != "2") {
		        cout << RED << "Invalid choice. Try again.\n" << RESET;
		        pauseAndClear();
		        continue;
		    }
		
		    string compChoice;
		    int mark;
		    if (fypChoice == "1") {
		        cout << BRIGHT_CYAN << "\n---FYP 1 Components---\n" << RESET;
            	cout << "[1] Report       (15%)\n[2] Presentation (10%)\n";
            
		    } else {
		        cout << BRIGHT_CYAN << "\n---FYP 2 Components---\n" << RESET;
            	cout << "[1] Report       (20%)\n[2] Demo         (35%)\n[3] Presentation (10%)\n";
		    }
		
		    while (true) {
		        cout << BRIGHT_GREEN << "\nChoice " << BRIGHT_YELLOW << "('C' to cancel action and save the marks entered): " << RESET;
		        getline(cin, compChoice);
		        if (compChoice == "C" || compChoice == "c"){
	            	break;
				}
		
		        if (fypChoice == "1") {
		            if (compChoice == "1") {
		                cout << "Enter FYP1 Report mark (0-15): ";
		                while (!getValidMark(mark, 15)) cout << RED << "Invalid mark.\nTry again: " << RESET;
		                
		                r.fyp1_report_m = mark;
		                
		            } else if (compChoice == "2") {
		                cout << "Enter FYP1 Presentation mark (0-10): ";
		                
		                while (!getValidMark(mark, 10)) cout << RED << "Invalid mark.\nTry again: " << RESET;
		                
		                r.fyp1_pres_m = mark;
		                
		            } else {
		                cout << RED <<"Invalid choice.\nPlaese try again.\n" << RESET;
						continue;
		            }
		            
		        } else { // FYP2
		            if (compChoice == "1") {
		                cout << "Enter FYP2 Report mark (0-20): ";
		                while (!getValidMark(mark, 20)) cout << RED << "Invalid mark.\nTry again: " << RESET;
		                
		                r.fyp2_report_m = mark;
		                
		            } else if (compChoice == "2") {
		                cout << "Enter FYP2 Demo mark (0-35): ";
		                while (!getValidMark(mark, 35)) cout << RED << "Invalid mark.\nTry again: " << RESET;
		                
		                r.fyp2_demo_m = mark;
		                
		            } else if (compChoice == "3") {
		                cout << "Enter FYP2 Presentation mark (0-10): ";
		                while (!getValidMark(mark, 10)) cout << RED << "Invalid mark.\nTry again: " << RESET;
		                
		                r.fyp2_pres_m = mark;
		                
		            } else {
		                cout << RED <<"Invalid choice.\nPlaese try again.\n" << RESET;
						continue;
		            }
		        }
		    }
	        saveMarks(records, count);
	        cout << GREEN << "Marks saved successfully!\n" << RESET;
	        pauseAndClear();
		}

        saveMarks(records, count);
        cout << GREEN << "Marks saved successfully! Moderator ID assigned.\n" << RESET;
        showModeratorMarks(r);
        
        cout << BLINK << "Press Enter to continue..." << RESET;
        string dummy; getline(cin, dummy);
    

    cout << BRIGHT_YELLOW << "\nExiting moderator grading...\n" << RESET;
    pauseAndClear();
}

