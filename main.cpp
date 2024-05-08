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

    void clearInfo() {
        id = -1;
        name = "";
        email = "";
        sex = "";
        birthdate = "";
        address = "";
        phoneNumber = "";
        role = "";
    }
};

class User{
private:
	int id;
	string email;
	string password;

public:
    User() {}

    User(string email, string password){
        this->email = email;
        this->password = password;
    }

    void Register(){

    }

    Person login(){
        return Person("HDL", "hdl@gmail.com", "Male", "25/01/2005", "Ha Noi", "000", "Admin");
    }

    void logout(){

    }

    int getId(){
        return id;
    }

    void setId(int id){
        this->id = id;
    }

    string getEmail(){
        return email;
    }

    void setEmail(string email){
        this->email = email;
    }

    string getPassword(){
        return password;
    }

    void setPassword(string password){
        this->password = password;
    }
};

class BorrowInfo{
private:
	int id = 1;
	int personId;
	int bookId;
	int eBookId;
public:
    BorrowInfo(int personId, int bookId, int eBookId){
        this->personId = personId;
        this->bookId = bookId;
        this->eBookId = eBookId;
        // Cập nhật Id ...
        // Validate các thông tin đầu vào ...
    }

    void addInfo(){
        // Validate dữ liệu ...
        string file_name = "users.txt";
        ofstream file("file_name");
        file << endl;
        file << "[" << this->id << "] ";
        file << "[" << this->personId << "] ";
        file << "[" << this->bookId << "] ";
        file << "[" << this->eBookId << "]";
        file.close();
    }

    void updateInfo(){
        // Validate dữ liệu ...

    }

    int getId(){
        return id;
    }

    void setId(int id){
        this->id = id;
    }

    int getPersonId(){
        return personId;
    }

    void setPersonId(int personId){
        this->personId = personId;
    }

    int getBookId(){
        return bookId;
    }

    void setBookId(int bookId){
        this->bookId = bookId;
    }

    int getEbookId(){
        return eBookId;
    }

    void setEbookId(int eBookId){
        this->eBookId = eBookId;
    }
};

// Hàm lấy ra từng kiểu thông tin một trong file (ví dụ: trả về 1 vector<string> toàn ID)
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

class Book {
protected:
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

    // Khởi tạo contructor gồm đầy đủ thông tin
    Book(const int& id, const string& title, const string& author, const int& quantity)
        : id(id), title(title), author(author), quantity(quantity) {}

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

    void addBook(const string& filename, const string& bookInf) {
        ofstream outFile(filename, ios::app);
        vector<string> dataID = getInformationFromFile(filename, 0);

        set<long long> dataIDInt;
        for (string s : dataID) {
            dataIDInt.insert(stoi(s));
        } 

        int mex = 0;
        for (auto it = dataIDInt.begin(); it != dataIDInt.end(); ++it) {
            if (*it > mex + 1) {
                mex = mex + 1;
                break;
            }
            mex = *it;
        }
        ++mex;

        if (outFile.is_open()) {
            outFile << endl << '[' << to_string(mex) << "] " <<  bookInf << endl;
            outFile.close();
            cout << "Thong tin cua cuon sach da duoc ghi thanh cong!\n";
        }
    }

    void getBooks(const string& filename, int data) const {
        ifstream file(filename);
        string line;
        int cnt = 0;

        while (getline(file, line)) {
            ++cnt;
        }

        file.close();

        vector<vector<string>> bookInfor(data);

        for (int i = 0; i < data; ++i) {
            bookInfor[i] = getInformationFromFile(filename, i);
        }

        for (int i = 0; i < cnt; ++i) {
            for (int j = 0; j < data; ++j) {
                cout << "[" << bookInfor[j][i] << "] ";
            }
            cout << endl;
        }
    }

    void deleteBook(const string& filename) const {
        ifstream inFile(filename); 
        ofstream outFile("temp_books.txt"); 

        string line;
        bool found = false; // Kiểm tra xem ID có tồn tại không

        // Đọc từng dòng từ file gốc
        while (getline(inFile, line)) {
            size_t startPos = line.find("["); // Tìm vị trí của ký tự '['
            size_t endPos = line.find("]", startPos); // Tìm vị trí của ký tự ']' sau ký tự '['
            
            if (startPos != string::npos && endPos != string::npos) {
                string bookId = line.substr(startPos + 1, endPos - startPos - 1);

                if (bookId == to_string(this->id)) {
                    found = true; // Đánh dấu là đã tìm thấy cuốn sách cần xoá
                    continue; // Bỏ qua việc ghi dòng này vào file tạm thời
                }
            }

            // Ghi lại dòng vào file tạm thời
            outFile << line << endl;
        }

        inFile.close();
        outFile.close();

        if (found) {
            // Xoá file gốc
            if (remove(filename.c_str()) != 0) {
                cerr << "Khong the xoa file goc." << endl;
                return;
            }

            // Đổi tên file tạm thời thành file gốc
            if (rename("temp_books.txt", filename.c_str()) != 0) {
                cerr << "Khong the đoi ten file tam thoi." << endl;
                return;
            }

            cout << "Da xoa thong tin cua cuon sach có ID = " << id << " thanh cong." << endl;
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần xoá
            remove("temp_books.txt");
            cout << "Khong tim thay cuon sach co ID = " << id << " trong file." << endl;
        }
    }

    void updateBook(const string& filename, const string& newBookInfo) {
        // Tìm id từ thông tin mới của sách
        size_t startPos = newBookInfo.find("[");
        size_t endPos = newBookInfo.find("]", startPos);
        if (startPos == string::npos || endPos == string::npos) {
            cerr << "Khong the cap nhat thong tin sach vi khong tim thay ID." << endl;
            return;
        }

        string newBookId = newBookInfo.substr(startPos + 1, endPos - startPos - 1);

        ifstream inFile(filename); 
        ofstream outFile("temp_books.txt"); 

        string line;
        bool found = false; // Kiểm tra xem ID có tồn tại không

        // Đọc từng dòng từ file gốc
        while (getline(inFile, line)) {
            size_t startPos = line.find("["); // Tìm vị trí của ký tự '['
            size_t endPos = line.find("]", startPos); // Tìm vị trí của ký tự ']' sau ký tự '['
            
            // Nếu như vẫn còn đọc được dữ liệu
            if (startPos != string::npos && endPos != string::npos) {
                string bookId = line.substr(startPos + 1, endPos - startPos - 1);

                // Nếu id của sách cần cập nhật == id hiện tại trong books.txt thì thay thế nó
                if (bookId == newBookId) {
                    outFile << newBookInfo << endl;
                    found = true; // Đánh dấu là đã tìm thấy và cập nhật thông tin của cuốn sách
                } 
                // Nếu là các dữ liệu khác thì đẩy thẳng vào file
                else {
                    outFile << line << endl;
                }
            } 
            // Đẩy nốt dữ kiện cuối vào file
            else {
                outFile << line << endl;
            }
        }

        inFile.close();
        outFile.close();

        if (found) {
            // Xoá file gốc
            if (remove(filename.c_str()) != 0) {
                cerr << "Khong the xoa file goc." << endl;
                return;
            }

            // Đổi tên file tạm thời thành file gốc
            if (rename("temp_books.txt", filename.c_str()) != 0) {
                cerr << "Khong the đoi ten file tam thoi." << endl;
                return;
            }

            cout << "Da cap nhat thong tin cua cuon sach có ID = " << newBookId << " thanh cong." << endl;
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần cập nhật
            remove("temp_books.txt");
            cout << "Khong tim thay cuon sach co ID = " << newBookId << " trong file." << endl;
        }
    }
};

class EBook : public Book {
private: 
    string fileFormat;
    int fileSize;

public:
    EBook() {}

    EBook(const string& title, const string& author, int quantity, const string& fileFormat, int fileSize)
        : Book(title, author, quantity), fileFormat(fileFormat), fileSize(fileSize) {}

    string getFileFormat() {
        return this->fileFormat;
    }

    void setFileFormat(string ff) {
        this->fileFormat == ff;
    }

    int getFileSize() {
        return this->fileSize;
    }

    void setFileSize(int fs) {
        this->fileSize = fs;
    } 
};

// Kiểm tra thông tin needCheck đã tồn tại trong file hay chưa
template <class val>
bool isValid(const vector<val>& info, const val needCheck) {
    for (auto i : info) {
        if (i == needCheck) {
            return false;
        }
    }
    return true;
}

// In ra danh sách tính năng
void menu() {
    cout    << "-------------------------------------------------------------------------------------------------\n"
            << "|                      ___Vui long chon mot trong cac tinh nang sau day___                      |\n" 
            << "|   1. Dang nhap.                                                                               |\n"
            << "|   2. Dang ky.                                                                                 |\n"
            << "|   3. Them sach (Admin).                                                                       |\n"
            << "|   4. Sua thong tin sach (Admin).                                                              |\n"
            << "|   5. Xoa sach (Admin).                                                                        |\n"
            << "|   6. Muon sach.                                                                               |\n"
            << "|   7. Tra sach.                                                                                |\n"
            << "|   8. Lay thong tin cac quyen sach.                                                            |\n"
            << "|   9. Lay thong tin 1 quyen sach.                                                              |\n"
            << "|   10. Lay thong tin tat ca cac quyen sach eBook hien co.                                      |\n"
            << "|   11. Lay thong tin 1 eBook co id nam trong file eBooks.txt.                                  |\n"
            << "|   12. Hien thi tat ca cac quyen sach da muon cua ban than (User).                             |\n"
            << "|   13. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon voi id nguoi dung (Admin).      |\n"
            << "|   14. Chinh sua thong tin ca nhan.                                                            |\n"
            << "|   15. Chinh sua thong tin ca nhan cua nguoi khac (Admin).                                     |\n"
            << "|   16. Dang xuat.                                                                              |\n"
            << "|   17. Xoa man hinh console.                                                                   |\n"
            << "|   18. Thoat chuong trinh.                                                                     |\n"
            << "-------------------------------------------------------------------------------------------------\n";
}

bool isLogin(Person& p) {
    return p.getID() > 0 and p.getName() != "" and p.getEmail() != "" and p.getSex() != "" and p.getBirthdate() != "" and p.getAddress() != "" and p.getPhoneNumber() != "" and p.getRole() != "";
}

void clearScreen() {
    system("cls");
}

int main() {
    menu();

    int query = 0;
    bool welcome = false;

    Person p;
    User u;
    Book b;
    EBook eb;

    while (query != 18) {
        while (isLogin(p) == false) {
            cout << "Dang nhap/Dang ky de su dung tinh nang!!!\n";
            cin >> query;
            switch(query){
                case 1: 
                    p = u.login();
                    p.setID(1);
                    welcome = true;
                    break;
                case 2: // Tinh nang 2: Dang ky.
                    break;
            }
        }
        if (welcome == true) {
            cout    << endl << "Chuc mung ban da dang nhap thanh cong!" << endl
                    << "Welcome " << '<' << p.getName() << '>' << endl;
            welcome = false;
            cout << endl;
        }

        cout << "Nhap vao tinh nang ban muon su dung: ";
        cin >> query;
        cout << endl;

        switch(query){
            case 3: 
                if (p.getRole() == "Admin") {
                    cout << "Nhap cac thong tin cua sach: ";
                    string bookInfo;
                    getline(cin, bookInfo);
                    b.addBook("books.txt", bookInfo);
                }
                else {
                    cout << "Ban khong co quyen them thong tin sach !!!\n";
                }
                break;
            case 4:
                if (p.getRole() == "User") {
                    cout << "Ban khong co quyen chinh sua thong tin sach!" << endl;
                }
                else {
                    cout << "Nhap vao thong tin sach can chinh sua:" << endl;
                    string info;
                    scanf("\n");
                    getline(cin, info);
                    b.updateBook("books.txt", info);
                }
                break;
            case 5: // Tinh nang 5: Xoa sach (Admin).
                break;
            case 6: // Tinh nang 6: Muon sach.
                break;
            case 7: // Tinh nang 7: Tra sach.
                break;
            case 8: // Tinh nang 8: Lay thong tin cac quyen sach.
                break;
            case 9: // Tinh nang 9: Lay thong tin 1 quyen sach.
                break;
            case 10:
                cout << "Day la thong tin cac quyen sach EBooks hien tai:" << endl;
                eb.getBooks("ebooks.txt", 6);
                cout << endl;
                break;
            case 11: // Tinh nang 11: Lay thong tin 1 eBook theo id.
                break;
            case 12: // Tinh nang 12: Hien thi cac quyen sach da muon cua ban than (User).
                break;
            case 13: // Tinh nang 13: Hien thi tat ca sach cua 1 nguoi dung da muon theo id (Admin).
                break;
            case 14: // Tinh nang 14: Chinh sua thong tin ca nhan (User).
                break;
            case 15: // Tinh nang 15: Chinh sua thong tin nguoi khac (Admin).
                break;
            case 16: 
                u.logout();
                p.clearInfo();
                break;
            case 17:
                clearScreen();
                menu();
                break;
        }
    }
    return 0;
}