#include "admin_view.h"

#include <iostream>
#include <cstdlib>

#include "editUserInfo.h"
#include "menu.h"
#include "pauseAndClear.h"
#include "colour.h"
#include "read_user.h"
#include "admin_view.h"
#include "editUserInfo.h"
#include "summaryFYP.h"

using namespace std;

void admin_view(const string&id) {
    while(true){
        system("cls");
        menu();
        
        cout << BG_CYAN << BLACK << "\n\t=== Admin Menu ===\n\n" << RESET;
        cout << "[1] Edit User Information\n";
        cout << "[2] Summary of Result FYP Project";
        cout << BRIGHT_YELLOW << "\n\n[0] Logout\n" << RESET;
        cout << "Enter your choice: ";

        string input;
        getline(cin, input);

        if (input.empty()) {
            cout << RED << "You pressed Enter without typing anything! Try again.\n" << RESET;
            pauseAndClear();
            continue;
        }

        if (input == "1"){
            search_user();
            continue;
        }
        if (input == "2"){
            summaryFYPResults(id,true);
            continue;
        }

        else if (input == "0"){
		    cout << BRIGHT_RED <<"\nAre you sure you want to log out? (Y/N): " << RESET;
		    string confirm;
		    getline(cin, confirm);
		    if (!confirm.empty()) {
		        char c = tolower(confirm[0]);
		        if (c == 'y') {
		            cout << YELLOW << "\nLogging out...\n" << RESET;
		            pauseAndClear();
		            return;
		        }
		    }
		    cout << BRIGHT_YELLOW << "\nLogout canceled.\n" << RESET;
		    pauseAndClear();
		    break;
		}
        else{
            cout << RED << "Invalid choice. Try again.\n" << RESET;
            pauseAndClear();
            continue;
        }
    } 
}

