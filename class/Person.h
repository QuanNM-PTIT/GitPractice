#include <bits/stdc++.h>
#include "../function/getSmallestId.h"
#include "../data/fileName.h"

using namespace std;

#ifndef PERSON_H
#define PERSON_H

string getPersonRoleInLine(string data);

class Person {
    private:
        int id;
        string name;
        string email;
        string sex;
        string birthdate;
        string address;
        string phoneNumber;
        string role;
    public:
        Person();
        Person(int id, string name, string email, string sex, string birthdate, string address, string phoneNumber, string role);
        Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role);
        friend void addPerson(Person newPerson);
        friend void updatePeopleInfo(int personId);
        friend void updatePeopleInfoByAdmin();
        int getPersonId();
        string getPersonName();
        string getPersonEmail();
        string getPersonSex();
        string getPersonBirthdate();
        string getPersonAddress();
        string getPersonPhoneNumber();
        string getPersonRole();
};

Person::Person(){
    this -> id = -1;
    this -> name = "";
    this -> email = "";
    this -> sex = "";
    this -> birthdate = "";
    this -> address = "";
    this -> phoneNumber = "";
    this -> role = "";
}
Person::Person(int id, string name, string email, string sex, string birthdate, string address, string phoneNumber, string role){
    this -> id = id;
    this -> name = name;
    this -> email = email;
    this -> sex = sex;
    this -> birthdate = birthdate;
    this -> address = address;
    this -> phoneNumber = phoneNumber;
    this -> role = role;
}
Person::Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role){
    this -> id = getSmallestId(PeopleFile);
    this -> name = name;
    this -> email = email;
    this -> sex = sex;
    this -> birthdate = birthdate;
    this -> address = address;
    this -> phoneNumber = phoneNumber;
    this -> role = role;
}
void addPerson(Person newPerson){
    ofstream outFile(PeopleFile, ios::app);
    outFile << "[" << newPerson.getPersonId() << "] ";
    outFile << "[" << newPerson.getPersonName() << "] ";
    outFile << "[" << newPerson.getPersonEmail() << "] ";
    outFile << "[" << newPerson.getPersonSex() << "] ";
    outFile << "[" << newPerson.getPersonBirthdate() << "] ";
    outFile << "[" << newPerson.getPersonAddress() << "] ";
    outFile << "[" << newPerson.getPersonPhoneNumber() << "] ";
    outFile << "[" << newPerson.getPersonRole() << "]\n";
    outFile.close();
}
void updatePeopleInfo(int updatePersonId){
    system("cls");
    cout << "14. Chinh sua thong tin ca nhan.\n";
    cout << "Hay nhap thong tin moi!\n";
    string newName;
    string newEmail;
    string newSex;
    string newBirthdate;
    string newAddress;
    string newPhoneNumber;
    cout << "Nhap ten moi: ";
    cin.ignore();
    getline(cin, newName);
    cout << "Nhap Email moi: ";
    cin >> newEmail;
    cout << "Nhap Gioi tinh moi: ";
    cin >> newSex;
    cout << "Nhap Ngay sinh moi: ";
    cin >> newBirthdate;
    cout << "Nhap dia chi moi: ";
    cin.ignore();
    getline(cin, newAddress);
    cout << "Nhap So dien thoai moi: ";
    cin >> newPhoneNumber;
    cout << "Ban co chac chan muon sua thong tin? (1/0) ";
    int choose;
    cin >> choose;
    if (choose) {
        vector<string> peopleList;
        ifstream inFile(PeopleFile);
        string tmp;
        while (getline(inFile, tmp)){
            peopleList.push_back(tmp);
        }
        inFile.close();
        for (int i = 0; i < peopleList.size(); i++){
            int personId = getKeyId(peopleList[i]);
            if (personId == updatePersonId){
                peopleList[i] = "[" + to_string(updatePersonId) + "] ";
                peopleList[i] += "[" + newName + "] ";
                peopleList[i] += "[" + newEmail + "] ";
                peopleList[i] += "[" + newSex + "] ";
                peopleList[i] += "[" + newBirthdate + "] ";
                peopleList[i] += "[" + newAddress + "] ";
                peopleList[i] += "[" + newPhoneNumber + "] ";
                peopleList[i] += "[" + getPersonRoleInLine(peopleList[i]) + "] ";
                break;
            }
        }
        ofstream outFile(PeopleFile);
        for (string item : peopleList){
            outFile << item << "\n";
        }
        outFile.close();

    }  
    else {
        cout << "Ban da huy yeu cau sua thong tin!\n";
    }
    return;
}
void updatePeopleInfoByAdmin(){
    while (1) {
        system("cls");
        cout << "15. Chinh sua thong tin ca nhan cua Users.\n";
        cout << "Hay nhap User ID can sua thong tin: ";
        int updatePersonId;
        cin >> updatePersonId;
        if (!exsitedId(updatePersonId, PeopleFile)) {
            cout << "ID nguoi dung knong ton tai!\n";
            cout << "Ban co muon nhap lai? (1/0) ";
            int choose;
            cin >> choose;
            if (choose) {
                continue;
            }
            else {
                cout << "Ban da huy yeu cau sua thong tin nguoi dung!\n";
                break;           
            }
        }
        cout << "Hay nhap thong tin moi!\n";
        string newName;
        string newEmail;
        string newSex;
        string newBirthdate;
        string newAddress;
        string newPhoneNumber;
        string newRole;
        cout << "Nhap ten moi: ";
        cin.ignore();
        getline(cin, newName);
        cout << "Nhap Email moi: ";
        cin >> newEmail;
        cout << "Nhap Gioi tinh moi: ";
        cin >> newSex;
        cout << "Nhap Ngay sinh moi: ";
        cin >> newBirthdate;
        cout << "Nhap dia chi moi: ";
        cin.ignore();
        getline(cin, newAddress);
        cout << "Nhap So dien thoai moi: ";
        cin >> newPhoneNumber;
        cout << "Nhap vao tro moi: ";
        cin >> newRole;
        cout << "Ban co chac chan muon sua thong tin? (1/0) ";
        int choose;
        cin >> choose;
        if (choose) {
            vector<string> peopleList;
            ifstream inFile(PeopleFile);
            string tmp;
            while (getline(inFile, tmp)){
                peopleList.push_back(tmp);
            }
            inFile.close();
            for (int i = 0; i < peopleList.size(); i++){
                int personId = getKeyId(peopleList[i]);
                if (personId == updatePersonId){
                    peopleList[i] = "[" + to_string(updatePersonId) + "] ";
                    peopleList[i] += "[" + newName + "] ";
                    peopleList[i] += "[" + newEmail + "] ";
                    peopleList[i] += "[" + newSex + "] ";
                    peopleList[i] += "[" + newBirthdate + "] ";
                    peopleList[i] += "[" + newAddress + "] ";
                    peopleList[i] += "[" + newPhoneNumber + "] ";
                    peopleList[i] += "[" + newRole + "] ";
                    break;
                }
            }
            ofstream outFile(PeopleFile);
            for (string item : peopleList){
                outFile << item << "\n";
            }
            outFile.close();
            cout << "Chinh sua thong tin thanh cong!!\n";
        }  
        else {
            cout << "Ban da huy yeu cau sua thong tin!\n";
        }
        return;
    }
}

int Person::getPersonId(){
    return this -> id;
}
string Person::getPersonName(){
    return this -> name;
}
string Person::getPersonEmail(){
    return this -> email;
}
string Person::getPersonSex(){
    return this -> sex;
}
string Person::getPersonBirthdate(){
    return this -> birthdate;
}
string Person::getPersonAddress(){
    return this -> address;
}
string Person::getPersonPhoneNumber(){
    return this -> phoneNumber;
}
string Person::getPersonRole(){
    return this -> role;
}
string getPersonRoleInLine(string data){
    stringstream ss(data);
    string tmp;
    int t = 7;
    while (t--) {
        ss >> tmp;
    }
    return tmp.substr(1, tmp.size() -2);
}

#endif