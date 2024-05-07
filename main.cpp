#include <bits/stdc++.h>

using namespace std;

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
    Person() {}

    Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role) {
        this->name = name;
        this->email = email;
        this->sex = sex;
        this->birthdate = birthdate;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = role;
    }

    int getID() const {
        return id;
    }

    void setID(int id) {
        this->id = id;
    }

    string getName() const {
        return name;
    }

    void setName(const string& name) {
        this->name = name;
    }

    string getEmail() const {
        return email;
    }

    void setEmail(const string& email) {
        this->email = email;
    }

    string getSex() const {
        return sex;
    }

    void setSex(const string& sex) {
        this->sex = sex;
    }

    string getBirthdate() const {
        return birthdate;
    }

    void setBirthdate(const string& birthdate) {
        this->birthdate = birthdate;
    }

    string getAddress() const {
        return address;
    }

    void setAddress(const string& address) {
        this->address = address;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    void setPhoneNumber(const string& phoneNumber) {
        this->phoneNumber = phoneNumber;
    }

    string getRole() const {
        return role;
    }

    void setRole(const string& role) {
        this->role = role;
    }
};

vector<Person> people;

vector<string> getInformationFromFile(const string& filename, int n) {
    vector<string> info;
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
            line.erase(0, 1);
            tokens.push_back(line);
        }
        if (tokens.size() >= 3) {
            info.push_back(tokens[n]);
        }
    }
    file.close();
    return info;
}

bool isValid(const vector<string>& info, const string& email, int n) {
    for (int i = 0; i < n; ++i) {
        if (info[i] == email) {
            return false;
        }
    }
    return true;
}

class Book {
private:
    int id;
    string title;
    string author;
    int quantity;
public:
    Book() {}

    Book(const string& title, const string& author, int quantity) {
        this->title = title;
        this->author = author;
        this->quantity = quantity;
    }

    int getID() const {
        return id;
    }

    void setID(int id) {
        this->id = id;
    }

    string getTitle() const {
        return title;
    }

    void setTitle(const string& title) {
        this->title = title;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }

    void addBook(const string& bookInf) {
        ofstream outFile("test_add_book.txt", ios::app);
        if (outFile.is_open()) {
            outFile << bookInf << '\n';
            outFile.close();
            cout << "Thông tin của cuốn sách đã được ghi thành công!\n";
        } else {
            cerr << "Mở file thất bại!\n";
        }
    }
};

void initInformationForPeople() {
    vector<vector<string>> info(7);
    for (int i = 1; i <= 7; ++i) {
        info[i - 1] = getInformationFromFile("people.txt", i);
    }

    int id = 1;
    for (int j = 0; j < 10; ++j) {
        if (isValid(info[1], info[1][j], j)) {
            Person per(info[0][j], info[1][j], info[2][j], info[3][j], info[4][j], info[5][j], info[6][j]);
            per.setID(id++);
            people.push_back(per);
        }
    }
}

int main() {
    initInformationForPeople();
    return 0;
}