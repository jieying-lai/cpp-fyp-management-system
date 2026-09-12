#include <iostream>
#include <ctime>
#include <string>
#include <limits>

#include "menu.h"
#include "colour.h"
#include "pauseAndClear.h"
#include "register_user.h"
#include "login.h"
#include "lecturer_view.h"
#include "admin_view.h"
#include "student_view.h"

using namespace std;

int main() {
	bool condition = true;
    do {
        system("cls");
        menu();

        cout << BRIGHT_YELLOW << "\n[L]ogin\t\t" << RESET 
			 << YELLOW 		  << "[N]ew User\t\t" << RESET 
			 << BRIGHT_RED 	  << "[E]xit" << RESET << endl;
        cout << "Enter your choice: ";
        
        string input;
        getline(cin, input);

		if (!input.empty() && input.back() == '\r') {
			input.pop_back();
		}

        if (input.empty()) {
            cout << RED << "\nYou pressed Enter without typing anything! Please enter [L, N, or E]\n" << RESET;
            pauseAndClear();
            continue;
        }

        if (input.length() > 1) {
            cout << RED << "\nInvalid input! Only one character is allowed [L, N, or E].\n" << RESET;
            pauseAndClear();
            continue;
        }

        if (input == "L" || input == "l") {
        	string id, role;
			if (login(id, role)) {
			    pauseAndClear();
			    if (role == "Lecturer") {
			        lecturer_view(id);
			    } 
				else if (role == "Student") {
			        student_view(id);
			    }
			    else if (role == "Admin"){
			    	admin_view(id);
				}
			    
			} else {
			    cout << RED << "Login failed. Returning to menu...\n" << RESET;
			    pauseAndClear();
			}
    	}
           
        else if (input == "N" || input == "n") {
            register_user();
            
        }
        
        else if (input == "E" || input == "e") {
            cout << BRIGHT_GREEN << "\nExiting program..." << RESET << endl;
            condition = false;
        }
        
        else {
            cout << RED << "\nInvalid choice, please enter [L, N, or E]\n" << RESET;
            pauseAndClear();
        }

    } while (condition == true);

    return 0;
}
