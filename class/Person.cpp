#include <bits/stdc++.h>
#include "../function/getSmallestId.cpp"

using namespace std;

const string BorrowInfosFile = "../data/borrowInfos.txt";
const string PeopleFile = "../data/people.txt";
const string BooksFile = "../data/books.txt";
const string EBooksFile = "../data/ebooks.txt";

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
    this -> id = getSmallestId(PeopleFile);
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
