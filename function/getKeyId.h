#include <bits/stdc++.h>

using namespace std;

#ifndef GETKEYID_H
#define GETKEYID_H

int getKeyId(string dataLine){ // A single line in datafile has first element is key id
    stringstream ss(dataLine);
    string tmp;
    ss >> tmp;
    int id = stoi(tmp.substr(1, tmp.size()-2));
    return id;
}

#endif