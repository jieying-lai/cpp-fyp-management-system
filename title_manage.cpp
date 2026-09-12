#include "title_manage.h"
#include "colour.h"
#include "pauseAndClear.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

// Global variables
Title titles[MAX_TITLES];
int titleCount = 0;

void readTitles(Title titles[], int &titleCount) {
    ifstream file("titles.txt");
    titleCount = 0;

    if (!file) { 
        ofstream newFile("titles.txt");
        newFile.close();
        return;
    }

    string line;
    while (getline(file, line) && titleCount < MAX_TITLES) {
        stringstream ss(line);
        Title t;
        getline(ss, t.id, ',');
        getline(ss, t.name, ',');
        getline(ss, t.description, ',');
        getline(ss, t.field, ',');
        getline(ss, t.prerequisites, ',');
        getline(ss, t.supervisorId, ',');
        getline(ss, t.status);

        t.status.erase(remove(t.status.begin(), t.status.end(), '\r'), t.status.end());

        if (!t.id.empty())
            titles[titleCount++] = t;
    }
    file.close();

    sort(titles, titles + titleCount, [](const Title &a, const Title &b) {
        return a.id < b.id;
    });
}

void saveTitles(const Title titles[], int titleCount) {
    ofstream file("titles.txt", ios::trunc);
    for (int i = 0; i < titleCount; i++) {
        file << titles[i].id << ","
             << titles[i].name << ","
             << titles[i].description << ","
             << titles[i].field << ","
             << titles[i].prerequisites << ","
             << titles[i].supervisorId << ","
             << titles[i].status << "\n";
    }
}


string generateNextId() {
    int maxId = 0;
    for (int i = 0; i < titleCount; i++) {
        if (!titles[i].id.empty() && titles[i].id[0] == 'T') {
            string numPart = titles[i].id.substr(1);
            if (all_of(numPart.begin(), numPart.end(), ::isdigit)) {
                int num = stoi(numPart);
                if (num > maxId) maxId = num;
            }
        }
    }

    int nextId = maxId + 1;
    stringstream ss;
    ss << 'T' << setw(3) << setfill('0') << nextId;
    return ss.str();
}

int findTitleIndex(const string &id) {
    string query = id;
    transform(query.begin(), query.end(), query.begin(), ::toupper);

    for (int i = 0; i < titleCount; i++) {
        string target = titles[i].id;
        transform(target.begin(), target.end(), target.begin(), ::toupper);
        if (target == query)
            return i;
    }
    return -1;
}

