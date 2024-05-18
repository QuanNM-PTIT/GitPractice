#include <bits/stdc++.h>

using namespace std;

#ifndef VALIDATE_H
#define VALIDATE_H

bool exsitedId(int id, string file, int idPosition = 1){
    ifstream inFile(file);
    vector<string> dataList;
    string tmp;
    while (getline(inFile, tmp)){
        dataList.push_back(tmp);
    }
    inFile.close();
    for (string item : dataList){
        int position = idPosition;
        stringstream ss(item);
        while (position > 0){
            ss >> tmp;
            position--;
        }
        if (id == stoi(tmp.substr(1, tmp.size()-2))){
            return true;
        }
    }
    return false;
}

#endif