#include <bits/stdc++.h>
#include "../function/getSmallestId.h"
#include "../data/fileName.h"

using namespace std;

#ifndef PERSON_H
#define PERSON_H

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
    this -> name = "Hieu";
    this -> email = "";
    this -> sex = "";
    this -> birthdate = "";
    this -> address = "";
    this -> phoneNumber = "";
    this -> role = "Admin";
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

#endif