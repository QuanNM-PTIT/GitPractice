#include <bits/stdc++.h>
using namespace std;

class Person {
private:
    int id = 1;
    string name;
    string email;
    string sex;
    string birthdate;
    string address;
    string phoneNumber;
    string role;

    vector<string> getEmailsFromFile(string filename) {
        vector<string> emails;
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = line.find("] [")) != string::npos) {
                string token = line.substr(1, pos - 1);
                tokens.push_back(token);
                line.erase(0, pos + 2);
            }
            if (!line.empty()) {
                line.pop_back(); 
                tokens.push_back(line);
            }
            if (tokens.size() >= 3) {
                emails.push_back(tokens[2]);
            }
        }
        file.close();
        return emails;
    }
public:
    Person() {}

    bool isValidEmail(string email) {
        vector<string> emails = getEmailsFromFile("people.txt");
        for (const auto& existingEmail : emails) {
            if (existingEmail == email) {
                return false;
            }
        }
        return true;
    }

    int getID() {
        return this->id;
    }

    void setID(int id) {
        this->id = id;
    }

    string getName() {
        return this->name;
    }

    void setName(string name) {
        this->name = name;
    }

    string getEmail() {
        return this->email;
    }

    void setEmail(string email) {
        this->email = email;
    }

    string getSex() {
        return this->sex;
    }

    void setSex(string sex) {
        this->sex = sex;
    }

    string getBirthdate() {
        return this->birthdate;
    }

    void setBirthdate(string birthdate) {
        this->birthdate = birthdate;
    }

    string getAddress() {
        return this->address;
    }

    void setAddress(string address) {
        this->address = address;
    }

    string getPhoneNumber() {
        return this->phoneNumber;
    }

    void setPhoneNumber(string phoneNumber) {
        this->phoneNumber = phoneNumber;
    }

    string getRole() {
        return this->role;
    }

    void setRole(string role) {
        this->role = role;
    }
};

class  Book {
private:
    int id;
    string title;
    string author;
    int quantity;
public:
    Book() {}

    Book(string title, string author, int quantity){
        this -> title = title;
        this -> author = author;
        this -> quantity = quantity;
    }

    int getID(){
        return this -> id;
    }

    void setID(int id){
        this -> id = id;
    }

    string getTitle(){
        return this -> title;
    }

    void setTitle(string title){
        this -> title = title;
    }

    int getQuantity(){
        return this -> quantity;
    }

    void setQuantity(int quantity){
        this -> quantity = quantity;
    }

    void addBook(const string& bookInf){
        ofstream outFile("test_add_book.txt", ios::app); 

        if(outFile.is_open()){
            outFile << bookInf << '\n';
            outFile.close();
            cout << "Thong tin cua cuon sach da duoc ghi thanh cong !\n";
        } else {
            cerr << "Mo file that bai !\n";
        }
    }
};

int main() {
    Person p;
    Book a;
    string bookInf;
    getline(cin, bookInf);
    a.addBook(bookInf);
    return 0;
}