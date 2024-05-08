#include <bits/stdc++.h>

using namespace std;

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
};

class User{
private:
	int id;
	string email;
	string password;
public:
    User(string email, string password){
        this->email = email;
        this->password = password;
    }
    void register(){

    }
    Person login(){

    }
    void logout(){

    }
};

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

<<<<<<< HEAD
void init_Id(const string& file_name) {
    vector<string> id_list = getInformationFromFile(file_name, 0);
    map<string, int> mp;
    for(auto id : id_list){
        mp[id] = 1;
    }
    int id = 1;
    while(mp[id]){
        id ++;
    }
}

=======
>>>>>>> 772a3615b886f8299a90ada9c7be317c060ba085
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

void menu() {
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
            << "13. Hiển thị tất cả các quyển sách của 1 người dùng đã mượn với id người dùng (Admin).\n"
            << "14. Chỉnh sửa thông tin cá nhân.\n"
            << "15. Chỉnh sửa thông tin cá nhân của người khác (Admin).\n"
            << "16. Đăng xuất.\n"
            << "17. Thoát chương trình\n";
}

int main() {
<<<<<<< HEAD
    
=======
    menu();

    int query;
    cin >> query;
    bool isLogin = false;
    while (true) {
        while (isLogin == false) {
            cout << "Đăng nhập/Đăng ký để sử dụng tính năng!!!\n";
            cin >> query;
            // Tinh nang 1: Dang nhap.
            if (query == 1) {
                
            }
            // Tinh nang 2: Dang ky.
            else if (query == 2) {

            }
        }
        // Tinh nang 3: Them sach (Admin).
        if (query == 3) {

        }
        // Tinh nang 4: Sua thong tin sach (Admin).
        else if (query == 4) {

        }
        // Tinh nang 5: Xoa sach (Admin).
        else if (query == 5) {

        }
        // Tinh nang 6: Muon sach.
        else if (query == 6) {

        }
        // Tinh nang 7: Tra sach.
        else if (query == 7) {

        }
        // Tinh nang 8: Lay thong tin cac quyen sach.
        else if (query == 8) {

        }
        // Tinh nang 9: Lay thong tin 1 quyen sach.
        else if (query == 9) {

        }
        // Tinh nang 10: Lay thong tin cac quyen sach eBook.
        else if (query == 10) {

        }
        // Tinh nang 11: Lay thong tin 1 eBook theo id.
        else if (query == 11) {

        }
        // Tinh nang 12: Hien thi cac quyen sach da muon cua ban than (User).
        else if (query == 12) {

        }
        // Tinh nang 13: Hien thi tat ca sach cua 1 nguoi dung da muon theo id (Admin).
        else if (query == 13) {

        }
        // Tinh nang 14: Chinh sua thong tin ca nhan (User).
        else if (query == 14) {

        }
        // Tinh nang 15: Chinh sua thong tin nguoi khac (Admin).
        else if (query == 15) {

        }
        // Tinh nang 16: Dang xuat.
        else if (query == 16) {
            
        }
        // Tinh nang 17: Thoat chuong trinh.
        else if (query == 17) {
            return 0;
        }
    }
>>>>>>> 772a3615b886f8299a90ada9c7be317c060ba085
    return 0;
}