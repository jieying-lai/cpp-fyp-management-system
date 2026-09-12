#include "register_user.h"

#include <iostream>
#include <string>
#include <fstream>  //for if stream, ofstream, fstream
#include <cctype> // for toupper

#include "menu.h"
#include "pauseAndClear.h"
#include "colour.h"
#include "getMaskedPassword.h"

using namespace std;

void register_user(){

	
	system("cls"); 
	//menu page///////////////////////////////////////////////////////////////////
	menu();
	cout << "\n==================================================" << endl;
    cout << "            " << REVERSE << "--- Register New User ---\n" << RESET;
    cout << "==================================================" << endl;
    cout << BRIGHT_YELLOW << "(or 'C' to cancel)\n" << RESET ;
    
    string input; 
    string user[5];
    //create account - id//////////////////////////////////////////////////////////
    
    while (true) {
	    cout << "\nEnter Unique ID: ";
	    getline(cin, input);
	
	    if (input == "C" || input == "c") {
	        pauseAndClear(); 
	        return;
	    }
	
	    if (input.empty()) {
	        cout << RED << "ID cannot be empty. Registration failed.\n" << RESET;
	        continue;
	    }

	    bool numeric = true;
	    for (int i = 0; i < input.length(); i++) {
	        if (!isdigit(input[i])) {
	            numeric = false;
	            break;
	        }
	    }
	    if (!numeric) {
	        cout << RED << "ID must be numeric. Registration failed.\n" << RESET;
	        continue; 
	    }

	    ifstream users("users.txt");
	    string line;
	    bool exists = false;
	    while (getline(users, line)) {
	        string userId;
	        for (int i = 0; i < line.size(); i++) {
	            if (line[i] == ',') break;
	            userId += line[i];
	        }
	        if (userId == input) {
	            exists = true;
	            break;
	        }
	    }
	    users.close();
	
	    if (exists) {
	        cout << RED << "ID already exists. Registration failed.\n" << RESET;
	        continue; 
	    }

	    user[0] = input;
	    break;
	}

	// enter name////////////////////////////////////////////////////////////////////
	
	while (true){
	    cout << "\nEnter Name: ";
	    getline(cin, input);
		if (input == "C" || input == "c") {
			pauseAndClear(); 
			return; 
		}
			
	    if (input.empty()) {
		    cout << RED << "Name cannot be empty. Please try again.\n" << RESET;
		    continue;
		}
	    
	    else{
	    	for (char &c : input){
	    		c=toupper(c);
			}
	    	user[1] = input;
	    	break;
		}
	} 
	
	
	//enter email /////////////////////////////////////////////////////////
	while (true){
	    cout << "\nEnter Email: ";
	    getline(cin, input);
	
	    if (input == "C" || input == "c") {
	        pauseAndClear();
	        return; 
	    }
	
	    if (input.empty()) {
	        cout << RED << "Email cannot be empty. Please try again.\n" << RESET;
	        continue;
	    }

	    if (input.find('@') == string::npos || input.find('.') == string::npos) {
	        cout << RED << "Invalid email format. Must contain '@' and '.'\n" << RESET;
	        continue;
	    }

	    ifstream users("users.txt");
	    string line;
	    bool duplicate = false;
	    while (getline(users, line)){
	        string userEmail;
	        int column = 0;
	        for (int i = 0; i < line.size(); i++){
	            if (line[i] == ','){
	                column++;
	                continue;
	            }
	            if (column == 2){
	                userEmail += line[i];
	            }
	        }
	        if (userEmail == input) {
	            duplicate = true;
	            break;
	        }
	    }
	    users.close();
	
	    if (duplicate) {
	        cout << RED << "Email already exists. Please try again.\n" << RESET;
	        continue;
	    }
	    
		for (char &c : input){
	    		c=tolower(c);
			}
			
	    user[2] = input;
	    break;
	}
	
	//enter password /////////////////////////////////////////////////////////
	while (true) {
	    cout << "\nEnter Password (at least 8 characters): ";
	    
	    input = getMaskedPassword();
		if (input == "C" || input == "c") { 
			pauseAndClear(); 
			return; 
			}
			
	    if (input.empty()) {
	        cout << RED << "Password cannot be empty. Please try again.\n" << RESET;
	        continue;
	    }
		
		if (input.length() < 8){
			cout << RED << "Password cannot less than 8 characters.Please try again.\n"<< RESET;
			continue;
		}

	    cout << "Confirm Password: ";
	    string confirmPassword = getMaskedPassword();
	
	    if (input == confirmPassword) {
	    	user[3] = input;
	        break;
	    } 
	    else {
	        cout << RED << "Passwords do not match. Please re-enter your password.\n" << RESET;
	    }   
	}
	
	//enter role////////////////////////////////////////////////////////////////////////////
	while (true){
		cout << "\nSelect Role:\n";
	    cout << "[1] Lecturer\n";
	    cout << "[2] Student\n";
	    cout << "Enter your choice (1 or 2): ";
	    getline(cin, input);
	    
		if (input == "C" || input == "c") { 
			pauseAndClear(); 
			return; 
			}
			
	    if (input.empty()) {
	        cout << RED << "Input cannot be empty. Please try again.\n" << RESET;
	        continue;
	    }
		
		if (input == "1"){
			user[4] = "Lecturer";
			break;
		}
		
		else if (input == "2"){
			user[4] = "Student";
			break;
		}
		
		else{
			cout << RED << "Invalid input. Please try again." << RESET ;
			continue;
		}
	} 

	//save user info/////////////////////////////////////////////////////////////////
	ofstream file("users.txt", ios::app);
	file << user[0] << "," << user[1] << "," << user[2] << "," << user[3] << "," << user[4] << "\n";
	file.close();
	cout << BRIGHT_CYAN << "\n *****User registered successfully!*****\n" << RESET;
	pauseAndClear(); 
}
