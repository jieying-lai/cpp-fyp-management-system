#ifndef TITLE_MANAGE_H
#define TITLE_MANAGE_H

#include <string>
using namespace std;

const int MAX_TITLES = 100;

struct Title {
    string id;
    string name;
    string description;
    string field;
    string prerequisites;
    string supervisorId;
    string status;  
};

// Global variables
extern Title titles[MAX_TITLES];
extern int titleCount;

// Function declarations
void readTitles(Title titles[], int &titleCount);
void saveTitles(const Title titles[], int titleCount);

string generateNextId();
int findTitleIndex(const string& id);

#endif

