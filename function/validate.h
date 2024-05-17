#include <bits/stdc++.h>

using namespace std;

#ifndef VALIDATE_H
#define VALIDATE_H

bool exsitedId(int id, string file){
    ifstream inFile(file);
    vector<string> dataList;
    string tmp;
    while (getline(inFile, tmp)){
        dataList.push_back(tmp);
    }
    inFile.close();
    for (string item : dataList){
        stringstream ss(item);
        ss >> tmp;
        if (id == stoi(tmp.substr(1, tmp.size()-2))){
            return true;
        }
    }
    return false;
}

#endif