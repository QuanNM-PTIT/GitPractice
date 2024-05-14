#include <bits/stdc++.h>

using namespace std;

#ifndef GETSMALLESTID_H
#define GETSMALLESTID_H

int getSmallestId(string fileName){
    vector<int> list;
    ifstream inFile(fileName);
    if (!inFile.good()) {
        cout << "Khong the mo tep tin." << endl;
        return -1;
    }
    string s;
    while (getline(inFile, s)){
        stringstream ss(s);
        string tmp;
        ss >> tmp;
        int id = stoi(tmp.substr(1, tmp.size()-2));
        list.push_back(id);
    }

    int present[list.size()] = {0};
    for (auto id : list){
        present[id] = 1;
    }
    for (int i = 1; i <= list.size(); i++){
        if (!present[i]){
            return i;
        } 
    }
    return list.size()+1;
}

#endif