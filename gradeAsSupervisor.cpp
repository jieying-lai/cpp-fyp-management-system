// gradeAsSupervisor.cpp
#include "gradeAsSupervisor.h"
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


void showSupervisorMarks(const MarksRecord &r) {
    cout << BRIGHT_CYAN << "\n--- Current Marks (Supervisor View) ---\n" << RESET;

    cout << BRIGHT_WHITE << left << setw(25)  << "Component (30% + 70%)" 
         << "| " << setw(15) << "Supervisor" << RESET <<"\n";
    cout << string(45, '-') << "\n";

    cout << left << setw(25) << "FYP1 Report       (15%)" 
         << "| " << r.fyp1_report_s << "\n";
    cout << left << setw(25) << "FYP1 Presentation (10%)" 
         << "| " << r.fyp1_pres_s << "\n";
    cout << left << setw(25) << "FYP1 Effort       ( 5%)" 
         << "| " << r.fyp1_effort_s << "\n";

    cout << string(45, '-') << "\n";

    cout << left << setw(25) << "FYP2 Report       (20%)" 
         << "| " << r.fyp2_report_s << "\n";
    cout << left << setw(25) << "FYP2 Demo         (35%)" 
         << "| " << r.fyp2_demo_s << "\n";
    cout << left << setw(25) << "FYP2 Presentation (10%)" 
         << "| " << r.fyp2_pres_s << "\n";
    cout << left << setw(25) << "FYP2 Effort       ( 5%)" 
         << "| " << r.fyp2_effort_s << "\n";

    cout << string(45, '-') << "\n";
}

void gradeAsSupervisor(const string& supervisorId) {
    MarksRecord records[MAX_MARKS];
    int count = 0;
    readMarks(records, count);

    
    int choice = 0;
    
    while (true) {
		system("cls");
		cout << BRIGHT_WHITE << "\t=====================================" << RESET << endl;
	   	cout << BG_BLUE << BRIGHT_WHITE << "\t\t--- Submitted FYP ---\n" << RESET ;
	    cout << BRIGHT_WHITE << "\t=====================================" << RESET << endl;
	    cout << CYAN << "\nStudents who submitted under your supervision:\n" << RESET;
	
		cout << BRIGHT_WHITE << left << setw(5) << "No."
		     << setw(15) << "Student ID"
		     << setw(20) << "Student Name"
		     << setw(12) << "Title ID"
		     << setw(30) << "Title Name" << "\n";
		cout << string(100, '-') << "\n" << RESET; 
		
		int indexes[MAX_MARKS];
    	int n = 0;
	
		for (int i = 0; i < count; i++) {
		    if (records[i].supervisorId == supervisorId) {
		        indexes[n] = i;
		
		        string title = records[i].titleName;
		        if (title.length() > 27) {
		            title = title.substr(0, 27) + "...";
		        }
		
		        cout << left << setw(5)  << (n + 1)
		             << setw(15) << records[i].studentId
		             << setw(20) << records[i].studentName
		             << setw(12) << records[i].titleId
		             << setw(30) << title
		             << "\n";
		
		        n++;
		    }
		}

	   if (n == 0) {
	       cout << BRIGHT_RED << "No submissions under your supervision.\n" << RESET;
	       pauseAndClear();
	       return;
	   }
	   string choiceStr;
	   
	 	while(true){
	 	   cout << "\nSelect a student " << BRIGHT_YELLOW <<"(or C to cancel): "<< RESET;
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
			
			if (choice < 1 || choice > n) {
			    cout << RED << "Invalid selection. Please choose between 1 and " << n << ".\n" << RESET;
				continue;
			}
			break;
		}
		while (true) {
			system ("cls");
		    MarksRecord &r = records[indexes[choice - 1]];
		    cout << CYAN << "Selected Student:\n" << RESET;
		    cout << BRIGHT_WHITE << "ID: " << r.studentId << "\nName: " << r.studentName
		         << "\nTitle: " << r.titleId << " < " << r.titleName << " >\n";
		
		    showSupervisorMarks(r);
	    
	        cout << BRIGHT_YELLOW << "\nWhich FYP component do you want to grade?\n"
	             << BRIGHT_WHITE << "\n[1] FYP 1\n[2] FYP 2\n\n" << BRIGHT_YELLOW << "[0] Back to student list\n"
				 << BRIGHT_GREEN << "Choice: " << RESET;
				 
	        string opt;
	        getline(cin, opt);
		
	        if (opt == "0") break;
	        
	        if (opt.empty()) {
	            cout << RED << "\nYou pressed Enter without selecting anything.\nPlease try again.\n" << RESET;
	            pauseAndClear();
				continue;
	        }
	        if (opt != "1" && opt !="2" && opt != "0") {
	            cout << RED << "\nInvalid choice.\nPlease try again.\n" << RESET;
	            pauseAndClear();
				continue;
	        }
	        
	        if (opt == "1") {
	            cout << BRIGHT_CYAN << "\n---FYP 1 Components---\n" << RESET;
	            cout << "[1] Report       (15%)\n[2] Presentation (10%)\n[3] Effort       ( 5%)\n";
	            
	            while(true){
				
					cout <<BRIGHT_GREEN << "\nChoice " << BRIGHT_YELLOW << "('C' to cancel action and save the marks entered): " << RESET;
		            string comp;
		            getline(cin, comp);
		            
		            if (comp == "C" || comp == "c"){
		            	
		            	break;
					}
		
		            if (comp == "1") {
		                cout << "Enter Report mark (0-15): ";
		                int mark; 
						while (!getValidMark(mark, 15)) { 
							cout << RED << "Invalid mark.\nTry again: " << RESET; 
						}
		                r.fyp1_report_s = mark;
		                cin.ignore(numeric_limits<streamsize>::max(), '\n');
		                
		            } else if (comp == "2") {
		                cout << "Enter Presentation mark (0-10): ";
		                int mark; 
						while (!getValidMark(mark, 10)) { 
							cout << RED << "Invalid mark.\nTry again: " << RESET;  
						}
		                r.fyp1_pres_s = mark;
		                
		            } else if (comp == "3") {
		                cout << "Enter Effort mark (0-5): ";
		                int mark; 
						while (!getValidMark(mark, 5)) { 
							cout << RED << "Invalid mark.\nTry again: " << RESET; 
						}
		                r.fyp1_effort_s = mark;
		                
		            } else{
		            	cout << RED <<"Invalid choice.\nPlaese try again.\n" << RESET;
						continue;
					}
				}
	        }
	        if (opt == "2") {
	            cout << BRIGHT_CYAN << "\n---FYP 2 Components---\n" << RESET;
	            cout << "[1] Report       (20%)\n[2] Demo         (35%)\n[3] Presentation (10%)\n[4] Effort       ( 5%)\n";
				
				while(true){
				
					cout <<BRIGHT_GREEN << "\nChoice " << BRIGHT_YELLOW << "('C' to cancel action and save the marks entered): " << RESET;
		            string comp;
		            getline(cin, comp);
		            
		            if (comp == "C" || comp == "c"){
		            	
		            	break;
					}
		
		            if (comp == "1") {
		                cout << "Enter Report mark (0-20): ";
		                int mark; while (!getValidMark(mark, 20)) { 
							cout << RED << "Invalid mark.\nTry again: " << RESET; 
						}
		                r.fyp2_report_s = mark;
		                
		            } else if (comp == "2") {
		                cout << "Enter Demo mark (0-35): ";
		                int mark; 
						while (!getValidMark(mark, 35)) { 
							cout << RED << "Invalid mark.\nTry again: " << RESET; 
							}
		                r.fyp2_demo_s = mark;
		                
		            } else if (comp == "3") {
		                cout << "Enter Presentation mark (0-10): ";
		                int mark; 
						while (!getValidMark(mark, 10)) { 
							cout << RED << "Invalid mark.\nTry again: " << RESET; 
							}
		                r.fyp2_pres_s = mark;
		            } else if (comp == "4") {
		                cout << "Enter Effort mark (0-5): ";
		                int mark; 
						while (!getValidMark(mark, 5)) { 
							cout << RED << "Invalid mark.\nTry again: " << RESET; 
							}
		                r.fyp2_effort_s = mark;
		                
		            } else{
		            	cout << RED <<"Invalid choice.\nPlaese try again.\n" << RESET;
						continue;
					}
		        }
	        }
	        saveMarks(records, count);
        	cout << GREEN << "Marks saved successfully.\n" << RESET;
        	pauseAndClear();
		}
        
        cout <<  BLINK << "Press Enter to continue..." << RESET;
        
	    string dummy;
	    getline(cin, dummy);
    }

    cout << BRIGHT_YELLOW << "\nExiting supervisor grading...\n" << RESET;
    pauseAndClear();
}

