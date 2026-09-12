#include <iostream>
#include <cstdlib> 
#include <ctime>

#include "menu.h"
#include "colour.h"

using namespace std;
void menu(){
	system("cls");
	cout << WHITE << "==================================================" << endl;
    cout << REVERSE << BOLD << "---Student Final Year Project Management System---" << RESET << endl;
    cout << WHITE << "==================================================" << endl;
    
    time_t now = time(0);
	tm *ltm = localtime(&now);
    char buffer[100];
	strftime(buffer, sizeof(buffer), "\t%H:%M | %d %B %Y | %A", ltm);
    cout << BLINK << CYAN << ITALIC << buffer << RESET << endl;
}
