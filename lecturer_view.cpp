#include "lecturer_view.h"

#include "colour.h"
#include "pauseAndClear.h"
#include "menu.h"

#include "update_profile.h"
#include "modifyTitle.h"
#include "searchTitle.h"
#include "viewAllTitles.h"
#include "createTitle.h"
#include "registerANDconfirm.h"
#include "gradeAsSupervisor.h"
#include "gradeAsModerator.h"
#include "viewFYP.h"
#include "list.h"
#include "summaryFYP.h"

#include <iostream>
#include <string>

using namespace std; 

void lecturer_view(const string &id){
	string input;
	while (true){
        system("cls");
        menu();
        cout << BG_CYAN << BLACK << "\n\t=== Lecturer Menu ===\n\n" << RESET;
        
        cout << BG_MAGENTA << UNDERLINE << BRIGHT_WHITE << "\n\t{ Manage FYP }" << RESET << endl;
    
        cout << BRIGHT_WHITE << "[1] Create New FYP Title\n";
        cout << "[2] Search FYP Titles\n";
        cout << "[3] Modify My FYP Titles\n";
        cout << "[4] View All Titles\n";
        cout << "[5] Register and Confirm Student for Title Selection\n";
        cout << "[6] Student under my supervision / moderation\n";
        
        cout << BG_MAGENTA << UNDERLINE << BRIGHT_WHITE << "\n\t{ FYP Grating }" << RESET << endl;
        cout << BRIGHT_WHITE << "[7] Grade Projects as Supervisor\n";
        cout << "[8] Grade Projects as Moderator\n";
        cout << "[9] View Student FYP Results\n";
        cout << "[10] Summary of Results\n";
        
        cout << BG_MAGENTA << UNDERLINE << BRIGHT_WHITE << "\n\t{ Profile Update }" << RESET << endl;
        cout << BRIGHT_WHITE << "[U]pdate My Profile\n";
        
        cout <<  BRIGHT_YELLOW << "\n[0] Log Out\n" << RESET;
        cout << "Enter your choice: ";

        getline(cin, input);

        if (input.empty()) {
            cout << RED << "\nYou pressed Enter without selecting anything. Please try again.\n" << RESET;
            pauseAndClear();
            continue;
        }
		
		if (input.empty()) {
		    cout << RED << "\nYou pressed Enter without selecting anything. Please try again.\n" << RESET;
		    pauseAndClear();
		    continue;
		}
		
		if (input == "0"){
			cout << BRIGHT_RED <<"\nAre you sure you want to log out? [Y/N]: " << RESET;
			    string confirm;
			    getline(cin, confirm);
			    if (!confirm.empty()) {
			        char c = tolower(confirm[0]);
			        if (c == 'y') {
			            cout << BRIGHT_CYAN << "\nLogging out...\n" << RESET;
			            pauseAndClear();
			            return;
			        }
			    }
			    cout << YELLOW << "\nLogout canceled.\n" << RESET;
			    pauseAndClear();
		}
		else if (input == "1") createTitle(id);
		else if (input == "2") searchTitle();
		else if (input == "3") modifyTitle(id);
		else if (input == "4") viewAllTitles();
		else if (input == "5") registerANDconfirm(id);
		else if (input == "6") listSupervisionOrModerationByLecturer(id);
		else if (input == "7") gradeAsSupervisor(id);
		else if (input == "8") gradeAsModerator(id);
		else if (input == "9") viewFYP(id, true);
		else if (input == "10") summaryFYPResults(id,false);
		else if (input == "U" || input == "u") updateProfile(id);
		else {
		    cout << RED << "Invalid selection.\n" << RESET;
		    pauseAndClear();
		}
	}
}

