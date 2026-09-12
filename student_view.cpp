#include "student_view.h"

#include "colour.h"
#include "pauseAndClear.h"
#include "menu.h"

#include "update_profile.h"
#include "searchTitle.h"
#include "viewAllTitles.h"
#include "shortlistANDregister.h"
#include "editShortlist.h"
#include "submitFYP.h"
#include "viewFYP.h"

#include <iostream>
#include <string>

using namespace std; 

void student_view(const string &id){
	string input;
	while (true){
        system("cls");
        menu();
        cout << BG_CYAN << BLACK << "\n\t=== Student Menu ===\n\n" << RESET;
        
        cout << BG_MAGENTA << UNDERLINE << BRIGHT_WHITE << "\n\t{ Register FYP }" << RESET << endl;
    
        cout << BRIGHT_WHITE << "[1] Search FYP Titles\n";
        cout << "[2] View All Titles\n";
        cout << "[3] Shortlist and Register FYP \n";
   
        cout << BG_MAGENTA << UNDERLINE << BRIGHT_WHITE << "\n\t{ FYP Result }" << RESET << endl;
        cout << BRIGHT_WHITE << "[4] Submission FYP Project\n";
        cout << BRIGHT_WHITE << "[5] View FYP Result\n";
        
        cout << BG_MAGENTA << UNDERLINE << BRIGHT_WHITE << "\n\t{ Profile Update }" << RESET << endl;
        cout << BRIGHT_WHITE << "[6] Update My Profile\n";
        
        cout <<  BRIGHT_YELLOW << "\n[0] Log Out\n" << RESET;
        cout << "Enter your choice: ";

        getline(cin, input);

        if (input.empty()) {
            cout << RED << "\nYou pressed Enter without selecting anything. Please try again.\n" << RESET;
            pauseAndClear();
            continue;
        }
        char choice = input[0];

        switch(choice) {
            case '1':
                searchTitle();
                break; 
            case '2':
                viewAllTitles();
                break;
            case '3':
                shortlistANDregister(id);
                break;
            case '4':
                submitFYP(id);
                break;
            case '5':
                viewFYP(id,false);
                break;
			case '6':
                updateProfile(id); 
                break;
            case '0': {
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
			    break;
			}
			default:
                cout << RED << "\nInvalid choice. Please try again.\n" << RESET;
                pauseAndClear();
                break;
		}
	}
}

