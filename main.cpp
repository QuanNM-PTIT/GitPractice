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

bool isValid(const vector<string>& info, const string& needCheck, int n) {
    for (int i = 0; i < n; ++i) {
        if (info[i] == needCheck) {
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
        return this->id;
    }

    void setID(int id) {
        this->id = id;
    }

    string getTitle() const {
        return this->title;
    }

    void setTitle(const string& title) {
        this->title = title;
    }

    int getQuantity() const {
        return this->quantity;
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
        } 
        else {
            cerr << "Mở file thất bại!\n";
        }
    }
};

int main() {
    cout    << "Vui lòng chọn một trong các tính năng sau đây\n" 
            << "1. Đăng nhập.\n"
            << "2. Đăng ký.\n"
            << "3. Thêm sách (Admin).\n"
            << "4. Sửa thông tin sách (Admin).\n"
            << "5. Xóa sách (Admin).\n"
            << "6. Mượn sách.\n"
            << "7. Trả sách.\n"
            << "8. Lấy thông tin các quyển sách.\n"
            << "9. Lấy thông tin 1 quyển sách.\n"
            << "10. Lấy thông tin tất cả các quyển sách eBook hiện có.\n"
            << "11. Lấy thông tin 1 eBook có id nằm trong file eBooks.txt.\n"
            << "12. Hiển thị tất cả các quyển sách đã mượn của bản thân (User).\n"
            << "13. Hiển thị tất cả các quyển sách của 1 người dùng đã mượn với id người dùng.\n"
            << "14. Chỉnh sửa thông tin cá nhân.\n"
            << "15. Chỉnh sửa thông tin cá nhân của người khác (Admin).\n"
            << "16. Đăng xuất.\n"
            << "17. Thoát chương trình\n";

    int query;
    cin >> query;
    while (true) {
        
    }
    return 0;
}