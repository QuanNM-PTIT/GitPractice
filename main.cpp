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
    void Register(){

    }
    Person login(){

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

    void addBook(const string& bookInf) {
        ofstream outFile("books.txt", ios::app);
        if (outFile.is_open()) {
            outFile << bookInf << '\n';
            outFile.close();
            cout << "Thông tin của cuốn sách đã được ghi thành công!\n";
        }
    }

    void getBooks() {
        ifstream file("books.txt");
        string line;
        int cnt = 0;

        while (getline(file, line)) {
            ++cnt;
        }

        file.close();

        vector<vector<string>> bookInfor(4);

        for (int i = 0; i < 4; ++i) {
            bookInfor[i] = getInformationFromFile("books.txt", i);
        }

        for (int i = 0; i < cnt; ++i) {
            for (int j = 0; j < 4; ++j) {
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

                if (bookId == to_string(id)) {
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
                cerr << "Không thể xoá file gốc." << endl;
                return;
            }

            // Đổi tên file tạm thời thành file gốc
            if (rename("temp_books.txt", filename.c_str()) != 0) {
                cerr << "Không thể đổi tên file tạm thời." << endl;
                return;
            }

            cout << "Đã xoá thông tin của cuốn sách có ID = " << id << " thành công." << endl;
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần xoá
            remove("temp_books.txt");
            cout << "Không tìm thấy cuốn sách có ID = " << id << " trong file." << endl;
        }
    }
};

// Kiểm tra thông tin needCheck đã tồn tại trong file hay chưa
bool isValid(const vector<string>& info, const string& needCheck, int n) {
    for (int i = 0; i < n; ++i) {
        if (info[i] == needCheck) {
            return false;
        }
    }
    return true;
}

// In ra danh sách tính năng
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
    menu();

    int query;
    cin >> query;
    bool isLogin = false;

    while (true) {
        while (isLogin == false) {
            cout << "Đăng nhập/Đăng ký để sử dụng tính năng!!!\n";
            cin >> query;
            switch(query){
                case 1: // Tinh nang 1: Dang nhap.
                    break;
                case 2: // Tinh nang 2: Dang ky.
                    break;
            }
        }
        switch(query){
            case 3: // Tinh nang 3: Them sach (Admin).
                break;
            case 4: // Tinh nang 4: Sua thong tin sach (Admin).
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
            case 10: // Tinh nang 10: Lay thong tin cac quyen sach eBook.
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
            case 16: // Tinh nang 16: Dang xuat.
                break;
            case 17: // Tinh nang 17: Thoat chuong trinh.
                return 0;
        }
    }
    return 0;
}