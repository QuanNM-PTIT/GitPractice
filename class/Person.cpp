#include <bits/stdc++.h>

using namespace std;

int getSmallestId();

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
        Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role);
        int getPersonId();
};

Person::Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role){
    this -> id = getSmallestId();
    this -> name = name;
    this -> email = email;
    this -> sex = sex;
    this -> birthdate = birthdate;
    this -> address = address;
    this -> phoneNumber = phoneNumber;
    this -> role = role;
}
int Person::getPersonId(){
    return this -> id;
}



// int main()
// {
//     // Insert code here
//     cout << "Hello world\n";
//     Person hieu = Person("Hieu", "HieuMD.B22KH039", "male", "23/01/2004", "Hanoi", "0813267626", "User");
//     cout << hieu.getPersonId();
//     return 0;
// }

int getSmallestId(){
    vector<int> peopleIdList;
    ifstream inFile;
    inFile.open("../people.txt");
    string s;
    while (getline(inFile, s)){
        stringstream ss(s);
        string tmp;
        ss >> tmp;
        int id = stoi(tmp.substr(1, tmp.size()-2));
        peopleIdList.push_back(id);
    }

    int present[peopleIdList.size()] = {0};
    for (auto id : peopleIdList)
        present[id] = 1;
    for (int i = 1; i <= peopleIdList.size(); i++){
        if (!present[i]){
            return i;
        } 
    }
    return peopleIdList.size()+1;
}