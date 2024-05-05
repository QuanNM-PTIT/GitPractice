#include <bits/stdc++.h>

using namespace std;

class Person{
    private:
    int id ; 
    string name , email , sex , birthdate, address, phoneNumber, role;
    public:
    Person( string name , string email , string sex ,string birthdate,string address,string phoneNumber,string role ){
        this->name = name ;
        this->email = email;
        this->sex = sex ;
        this-> birthdate = birthdate; 
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = role;
        ifstream in;
        in.open("people.txt");
        string tmp ;
        int cnt = 0 ; 
        while( getline( in , tmp ) )cnt ++ ; // dem so luong person
        in.close();
        this->id = cnt + 1 ; 
    }
    void addInfo(){
        ofstream out("people.txt", ios::app); 
        out << '[' << this->id << ']' << " " << '[' << this->name << ']' << " " << '[' << this->email << "]" << " " << '[' << this->sex << ']' << " " << '[' << this->birthdate << ']' << " " << '[' << this->address << ']' << " " << '[' << this->phoneNumber << ']' << " " << '[' << this->role << ']' << endl;
        out.close();
    }
    int getId(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    string getEmail(){
        return this->email;
    }
    string getSex(){
        return this->sex;
    }
    string getBirthdate(){
        return this->birthdate;
    }
    string getAddress(){
        return this->address;
    }
    string getPhoneNumber(){
        return this->phoneNumber;
    }
    string getRole(){
        return this->role;
    }
};

class BorrowInfo{
    private:
    int id , personId, bookId, eBookId;
    public:
    BorrowInfo( int personId, int bookId, int eBookId ){
        this->personId = personId ; 
        this->bookId = bookId ;
        this->eBookId = eBookId;
        ifstream in;
        in.open("borrowInfos.txt");
        string tmp ;
        int cnt = 0 ; 
        while( getline( in , tmp ) )cnt ++ ; // dem so luong borrowInfos
        in.close();
        this->id = cnt + 1 ;
    }
    void addInfo(){
        ofstream out("borrowInfos.txt", ios::app) ; 
        out << '[' << this->id << ']' << " " << '[' << this->personId << ']' << " " << '[' << this->bookId << "]" << " " << '[' << this->eBookId << ']' << endl;
        out.close();
    }
    int getId(){
        return this->id;
    }
    int getPersonId(){
        return this->personId;
    }
    int getBookId(){
        return this->bookId;
    }
    int getEbookId(){
        return this->eBookId;
    }
};

int main()
{
    // Insert code here
    return 0;
}