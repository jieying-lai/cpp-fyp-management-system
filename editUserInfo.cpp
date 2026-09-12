#include "editUserInfo.h"
#include "pauseAndClear.h"
#include "register_user.h"
#include "getMaskedPassword.h"
#include "colour.h"
#include "read_user.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;


int findUsers(const string &keyword, User users[], int count, int matches[]) {
    int matchCount = 0;
    for (int i = 0; i < count; i++) {
        if (users[i].id == keyword || users[i].name == keyword || users[i].email == keyword) {
            matches[matchCount++] = i;  
        }
    }
    return matchCount; 
}

void editUserInfo(User users[], int &userCount, int matches[], int matchCount) {
	if (matchCount == 0) {
        cout << RED << "No users to edit.\n" << RESET;
        pauseAndClear();
        return;
    }
	ifstream file("users.txt");
    string line;
    cout << "\nSelect user number to modify ";
    cout << BRIGHT_YELLOW << "(0 to cancel)" << RESET << ": " ;
    string input;
    getline(cin, input);

    if (input.empty()) {
        cout << BRIGHT_YELLOW << "\nYou pressed Enter. Cancelling...\n" << RESET;
        pauseAndClear();
        return;
    }
    
    int choice = stoi(input);

    if (choice == 0) {
        cout << BRIGHT_YELLOW << "\nAction canceled.\n" << RESET;
        pauseAndClear();
        return;
    }

    if (choice < 1 || choice > matchCount) {
        cout << RED << "Invalid choice!\n" << RESET;
        return;
    }

    int index = matches[choice - 1];
    User &u = users[index];
    
    cout << BRIGHT_GREEN << "\nSelected User: " << u.name << "\n" << RESET;
    cout << "[1] Update ID\n";
    cout << "[2] Update Name\n";
    cout << "[3] Update Email\n";
    cout << "[4] Update Password\n";
    cout << "[5] Update Role\n";
    cout << BRIGHT_RED << "[6] Delete this User\n\n" << RESET;
    cout << BRIGHT_YELLOW << "[0] Cancel\n" << RESET;
    
    int action;
    while (true) {
        cout << "Enter your choice: ";
        string input;
        getline(cin, input);
        if (input.empty()) continue;
        
        stringstream ss(input);
        ss >> action;
        if (action >= 0 && action <= 6) break;
    }
    
    if (action == 0) {
        cout << BRIGHT_YELLOW << "\nUpdate canceled.\n" << RESET;
        pauseAndClear();
        return;
    }

    if (action == 6) {
        string confirm;
        cout << BRIGHT_RED << "Are you sure you want to delete this user " << BRIGHT_WHITE << u.name << BRIGHT_RED << "? (Y/N): " << RESET;
        getline(cin, confirm);
        
        if (!confirm.empty() && tolower(confirm[0]) == 'y') {
            for (int i = index; i < userCount - 1; i++) {
            	users[i] = users[i + 1];
            }
            userCount--;
            cout << BRIGHT_GREEN << "\nUser deleted successfully!\n" << RESET;
            pauseAndClear();
        } else {
            cout << BRIGHT_YELLOW << "\nDeletion canceled.\n" << RESET;
            pauseAndClear();
            return;
        }
    } 
	else {
        string newValue;
        if (action == 1) { 
           while (true) {
           		cout << BRIGHT_CYAN << "Original ID: " << u.id << "\n" << RESET;
                cout << "Enter new ID ";
                cout << BRIGHT_YELLOW << "(or 'C' to cancel)" << RESET << ": " ;
                getline(cin, newValue);
                if (newValue == "C" || newValue == "c") { 
					pauseAndClear(); 
					return; 
				}
                if (newValue.empty()) { 
					cout << RED << "ID cannot be empty.\nPlease try again.\n" << RESET; 
					continue; 
					}
                if (!all_of(newValue.begin(), newValue.end(), ::isdigit)) { 
					cout << RED << "ID must be numeric.\nPlease try again.\n" << RESET; 
					continue; 
				}
                bool duplicate = false;
                
                
	            while (getline(file, line)) {
	                string userID;
	                int column = 0;
	                for (char c : line) {
	                    if (c == ',') {
	                        column++;
	                        continue;
	                    }
	                    if (column == 2) userID += c;
	                }
	                if (userID == newValue) {
	                    duplicate = true;
	                    break;
	                }
	            }
	            file.close();
	
	            if (duplicate) {
	                cout << RED << "ID already exists. Please try again.\n" << RESET;
	                pauseAndClear();
	                continue;
	            }
                u.id = newValue;
                break;
            }
        }
        else if (action == 2) { 
            while (true) {
            	cout << BRIGHT_CYAN << "Original Name: " << u.name << "\n" << RESET;
                cout << "Enter new Name ";
                cout << BRIGHT_YELLOW << "(or 'C' to cancel)" << RESET << ": " ;
                getline(cin, newValue);
                if (newValue == "C" || newValue == "c") { 
					pauseAndClear(); 
					return; 
				}
                
                if (newValue.empty()) { 
					cout << RED << "Name cannot be empty.\nPlease try again." << RESET; 
					continue; 
				}
				for (char &c : newValue) c = toupper(c);
                u.name = newValue;
                break;
            }
    	}
        else if (action == 3) { 
            while (true) {
            	cout << BRIGHT_CYAN << "Original Email: " << u.email << "\n" << RESET;
                cout << "Enter new Email ";
                cout << BRIGHT_YELLOW << "(or 'C' to cancel)" << RESET << ": " ;
                getline(cin, newValue);
                if (newValue == "C" || newValue == "c") { 
					pauseAndClear(); 
					return; 
				}
                if (newValue.empty()) { 
					cout << RED << "Email cannot be empty.\nPlease try again.\n\n" << RESET; 
					continue; 
				}
                bool duplicate = false;
	            while (getline(file, line)) {
	                string userEmail;
	                int column = 0;
	                for (char c : line) {
	                    if (c == ',') {
	                        column++;
	                        continue;
	                    }
	                    if (column == 2) userEmail += c;
	                }
	                if (userEmail == newValue) {
	                    duplicate = true;
	                    break;
	                }
	            }
	            file.close();
	
	            if (duplicate) {
	                cout << RED << "Email already exists. Please try again.\n" << RESET;
	                pauseAndClear();
	                continue;
	            }
                if (newValue.find('@') == string::npos || newValue.find('.') == string::npos) {
	                cout << RED << "Invalid email format. Must contain '@' and '.'\n" << RESET;
	                pauseAndClear();
	                continue;
	            }
	            
	            for (char &c : newValue) c = tolower(c);
                u.email = newValue;
                break;
            }
        }
        else if (action == 4) { 
        
        	while (true) {
        		cout << BRIGHT_CYAN << "Original Password: " << users[index].password << "\n" << RESET;
	            cout << "Enter new Password " << BRIGHT_YELLOW << "(or 'C' to cancel)" << RESET << ": ";
	            newValue = getMaskedPassword();
	
	            if (newValue == "C" || newValue == "c") {
	                pauseAndClear();
	                continue;
	            }
	            if (newValue.empty()) {
	                cout << RED << "Password cannot be empty.\n" << RESET;
	                pauseAndClear();
	                continue;
	            }
	            if (newValue.length() < 8) {
	                cout << RED << "Password must be at least 8 characters.\n" << RESET;
	                pauseAndClear();
	                continue;
	            }
	
	            cout << "Confirm Password: ";
	            string confirmPassword = getMaskedPassword();
	            if (newValue != confirmPassword) {
	                cout << RED << "Passwords do not match. Try again.\n" << RESET;
	                pauseAndClear();
	                continue;
	            }
	            u.password = newValue;
                break;
			}
        }
        else if (action == 5) {
            while (true) {
            	cout << BRIGHT_CYAN << "Original Role: " << u.role << "\n" << RESET;
                cout << "Select new role:\n[1] Admin\n[2] Lecturer\n[3] Student\nEnter choice: ";
                int r; cin >> r; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (r == 1) { 
					u.role = "Admin"; 
					break; 
				}
                else if (r == 2) { 
					u.role = "Lecturer"; 
					break; 
				}
                else if (r == 3) { 
					u.role = "Student"; 
					break; 
				}
                else { 
					cout << RED << "Invalid choice.\nPlease try again.\n\n" << RESET; 
					continue;
					}
            }
        }
        
        ofstream outFile("users.txt", ios::trunc);
        for (int i = 0; i < userCount; i++) {
            outFile << users[i].id << ","
                    << users[i].name << ","
                    << users[i].email << ","
                    << users[i].password << ","
                    << users[i].role << "\n";
        }
        outFile.close();
        cout << BRIGHT_GREEN << "\nProfile updated successfully!\n" << RESET;
        pauseAndClear();
    }
}    

void finding(int mode) {
    User users[MAX_USERS];
    int count = read_users(users);
	int matches[MAX_USERS];  
	
    string keyword;
    cout << "Enter keyword: ";
    getline(cin, keyword);

    if (keyword.empty()) {
        cout << RED << "\nKeyword cannot be empty. Try again.\n" << RESET;
        pauseAndClear();
        return;
    }

    int matchCount = 0;

    if (mode == 1) {  // search by ID
        for (int i = 0; i < count; i++) {
            if (users[i].id == keyword) {
                matches[matchCount++] = i;
            }
        }
    } else if (mode == 2) {  // search by Name
        string upperKeyword = keyword;
        for (char &c : upperKeyword) c = toupper(c);

        for (int i = 0; i < count; i++) {
            string nameUpper = users[i].name;
            for (char &c : nameUpper) c = toupper(c);
            if (nameUpper == upperKeyword) {
                matches[matchCount++] = i;
            }
        }
    } else if (mode == 3) {  
        string lowerKeyword = keyword;
        for (char &c : lowerKeyword) c = tolower(c);

        for (int i = 0; i < count; i++) {
            string emailLower = users[i].email;
            for (char &c : emailLower) c = tolower(c);
            if (emailLower == lowerKeyword) {
                matches[matchCount++] = i;
            }
        }
    }

    if (matchCount == 0) {
        cout << RED << "\nNo matching user found.\n" << RESET;
        pauseAndClear();
        return;
    }

    system("cls");
    cout << BRIGHT_WHITE << "======================================" << RESET << endl;
    cout << BG_BLUE << BRIGHT_WHITE << "\t--- Matching Users ---\n" << RESET;
    cout << BRIGHT_WHITE << "======================================" << RESET << endl;

    cout << BRIGHT_CYAN << left << setw(5) << "No"
         << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(25) << "Email"
         << setw(15) << "Role" << RESET << endl;
    cout << BRIGHT_WHITE << string(70, '-') << RESET << endl;

    for (int i = 0; i < matchCount; i++) {
        int idx = matches[i];
        cout << setw(5) << (i + 1)
             << setw(10) << users[idx].id
             << setw(15) << users[idx].name
             << setw(25) << users[idx].email
             << setw(15) << users[idx].role << endl;
    }

    cout << BLINK << "\nPress Enter to continue..." << RESET;
    cin.get();
    editUserInfo(users, count, matches, matchCount);

}

void search_user() {
    while (true) {
        system("cls");
        cout << BRIGHT_WHITE << "===========================================" << RESET << endl;
        cout << BG_BLUE << BRIGHT_WHITE << "\t--- Search User to Modify ---\n" << RESET;
        cout << BRIGHT_WHITE << "===========================================" << RESET << endl;

        cout << "[1] Search by ID\n";
        cout << "[2] Search by Name\n";
        cout << "[3] Search by Email\n";
        cout << BRIGHT_CYAN << "[4] Show All Users\n" << RESET;
        cout << BRIGHT_YELLOW << "\n[0] Cancel\n" << RESET;

        string input;
        cout << "Enter your choice: ";
        getline(cin, input);

        if (input.empty()) {
            cout << RED << "\nYou pressed Enter without selecting anything. Please try again.\n" << RESET;
            pauseAndClear();
            continue;
        } 
        else if (input == "0") {
            cout << BRIGHT_YELLOW << "\nUpdate canceled.\n" << RESET;
            pauseAndClear();
            return;
        }
        else if (input == "1") {
		    finding(1); 
		}
		else if (input == "2") {
		    finding(2);  
		}
		else if (input == "3") {
		    finding(3); 
		}
        else if (input == "4") {
            User users[MAX_USERS];
            int userCount = read_users(users);

            system("cls");
            cout << BRIGHT_WHITE << "\t=================================" << RESET << endl;
            cout << BG_BLUE << BRIGHT_WHITE << "\t\t--- ALL Users ---\n" << RESET;
            cout << BRIGHT_WHITE << "\t=================================" << RESET << endl;

            cout << BRIGHT_CYAN << left << setw(10) << "ID"
                 << setw(15) << "Name"
                 << setw(25) << "Email"
                 << setw(15) << "Role" << RESET << endl;
            cout << BRIGHT_WHITE << string(70, '-') << RESET << endl;

            for (int i = 0; i < userCount; i++) {
                cout << setw(10) << users[i].id
                     << setw(15) << users[i].name
                     << setw(25) << users[i].email
                     << setw(15) << users[i].role << endl;
            }

            cout << BLINK << "\nPress Enter to return to menu..." << RESET;
            cin.get();
            continue;
        }
        else {
            cout << RED << "\nInvalid choice. Please try again.\n" << RESET;
            pauseAndClear();
            continue;
        }
    }
}

