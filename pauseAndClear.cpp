#include "pauseAndClear.h"
#include "colour.h"

#include <iostream>
#include <cstdlib>  

using namespace std;

void pauseAndClear() {
    cout << BLINK  << "\nPress Enter to continue..." << RESET;
    cin.get(); 
    system("cls"); 
}
