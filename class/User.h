#include <bits/stdc++.h>
#include "./Person.h"
#include "../function/getSmallestId.h"

using namespace std;

#ifndef USER_H
#define USER_H

bool exsitedEmail(string email, string fileName);
bool exsitedPassword(string password, string fileName);
Person getPeronInfo(string email);
vector<string> splitData(string data);

class User{
    private:
        int id;
        string email;
        string password;
    public:
        User(string email, string password);
        friend void addUser(User newUser);
        friend void registerUser();
        friend Person loginUser();
        friend Person logoutUser(Person currentUser);
        int getUserId();
        string getUserEmail();
        string getUserPassword();

};

User::User(string email, string password){
    this -> id = getSmallestId(UserFile);
    this -> email = email;
    this -> password = password;
}
void addUser(User newUser){
    ofstream outFile(UserFile, ios::app);
    outFile << "[" << newUser.getUserId() << "] ";
    outFile << "[" << newUser.getUserEmail() << "] ";
    outFile << "[" << newUser.getUserPassword() << "]\n";
    outFile.close();
}
void registerUser(){
    string name;
    string password;
    string email;
    string sex;
    string birthdate;
    string address;
    string phoneNumber;
    string role;
    while (1) {
        system("cls");
        cout << "2. Dang ki.\n";
        cout << "Hay nhap thong tin sach can them!\n";
        cout << "Nhap Ten: ";
        cin.ignore();
        getline(cin, name);
        cout << "Nhap Email: ";
        cin >> email;
        cout << "Nhap Password: ";
        cin >> password;
        cout << "Nhap Gioi tinh: ";
        cin >> sex;
        cout << "Nhap Ngay sinh: ";
        cin >> birthdate;
        cout << "Nhap Dia chi: ";
        cin.ignore();
        getline(cin, address);
        cout << "Nhap So dien thoai: ";
        cin >> phoneNumber;
        role = "User";

        if (!exsitedEmail(email, UserFile)) {
            User newUser = User(email, password);
            addUser(newUser);
            Person newPerson = Person(name, email, sex, birthdate, address, phoneNumber, role);
            addPerson(newPerson);
            cout << "Dang ki thanh cong!!\n";
            cout << "Nhan Enter de tro ve MENU!!\n";
            cin.ignore();
            cin.get();
            break;
        }
        else {
            cout << "Email da ton tai!!!\n";
            cout << "Ban co muon nhap lai?? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                break;
            }
        }
    }
    system("cls");
    return;
}
Person loginUser(){
    string email;
    string password;
    while (1) {
        system("cls");
        cout << "1. Dang nhap.\n";
        cout << "Nhap Email: ";
        cin >> email;
        cout << "Nhap Password: ";
        cin >> password;
        if (exsitedEmail(email, UserFile) && exsitedPassword(password, UserFile)) {
            Person newPerson = getPeronInfo(email);
            cout << "Dang nhap thanh cong!!\n";
            cout << "Chao mung " << newPerson.getPersonName() << " !!!\n";
            cout << "Nhan Enter de tro ve MENU!!\n";
            cin.ignore();
            cin.get();
            system("cls");
            return newPerson;
        }
        else {
            cout << "Email hoac Mat khau khong dung!!!\n";
            cout << "Ban co muon nhap lai?? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                break;
            }
        }
    }
    return Person();
}
Person logoutUser(Person currentUser){
    system("cls");
    cout << "16. Dang xuat.\n";
    cout << "Ban co muon dang xuat?? (1/0) ";
    int choose;
    cin >> choose;
    if (choose) {
        cout << "Ban da dang xuat!\n";
        cout << "Nhan Enter de tro ve MENU!!\n";
        cin.ignore();
        cin.get();
        system("cls");
        return Person();
    }
    system("cls");
    return currentUser;
}

int User::getUserId(){
    return this -> id;
}
string User::getUserEmail(){
    return this -> email;
}
string User::getUserPassword(){
    return this -> password;
}
bool exsitedEmail(string email, string fileName){
    ifstream inFile(fileName);
    vector<string> dataList;
    string tmp;
    while (getline(inFile, tmp)){
        dataList.push_back(tmp);
    }
    inFile.close();
    for (string item : dataList){
        stringstream ss(item);
        ss >> tmp;
        ss >> tmp;
        if (email == tmp.substr(1, tmp.size()-2)){
            return true;
        }
    }
    return false;
}
bool exsitedPassword(string password, string fileName){
    ifstream inFile(fileName);
    vector<string> dataList;
    string tmp;
    while (getline(inFile, tmp)){
        dataList.push_back(tmp);
    }
    inFile.close();
    for (string item : dataList){
        stringstream ss(item);
        ss >> tmp;
        ss >> tmp;
        ss >> tmp;
        if (password == tmp.substr(1, tmp.size()-2)){
            return true;
        }
    }
    return false;
}
Person getPeronInfo(string personEmail){
    ifstream inFile(PeopleFile);
    vector<string> dataList;
    string tmp;
    while (getline(inFile, tmp)){
        dataList.push_back(tmp);
    }
    inFile.close();
    string info = "!";
    vector<string> wordList;
    for (string item : dataList){
        wordList = splitData(item);
        if (personEmail == wordList[2]){
            info = item;
            break;
        }
    }
    wordList.clear();
    wordList = splitData(info);
    int id = stoi(wordList[0]);
    string name = wordList[1];
    string email = wordList[2];
    string sex = wordList[3];
    string birthdate = wordList[4];
    string address = wordList[5];
    string phoneNumber = wordList[6];
    string role = wordList[7];
    wordList.clear();
    return Person(id, name, email, sex, birthdate, address, phoneNumber, role);
}
vector<string> splitData(string data){
    vector<string> list;
    string tmp = "";
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == '[') {
            continue;
        }
        if (data[i] == ']') {
            list.push_back(tmp);
            tmp = "";
            i++;
            continue;
        }
        tmp += data[i];
    }
    return list;
}

#endif