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

int main() {
    Person person;
    string emailToCheck = "emily.davis@gmail.com";
    if (person.isValidEmail(emailToCheck)) {
        cout << "Email chua ton tai trong file!" << endl;
    } 
    else {
        cout << "Email ton tai trong file!" << endl;
    }
    return 0;
}