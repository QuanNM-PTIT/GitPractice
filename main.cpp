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
        // Validate dữ liệu đầu vào ...

        this->personId = personId;
        this->bookId = bookId;
        this->eBookId = eBookId;
        // Cập nhật Id
        vector<string> ID_list = this->getInfo(0);
        map<int, int> mp;
        for(string ID : ID_list){
            mp[stoi(ID)] = 1;
        }
        while(mp[id]){
            ++ id;
        }
    }

    vector<string> getInfo(int n){
        vector<string> info;
        string filename = "test_borrowInfos.txt";
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while(ss >> token){
                tokens.push_back(token.substr(1, token.size() - 2));
            }
            info.push_back(tokens[n]);
        }   
        file.close();
        return info;
    }
    
    bool isValid(){
        // Kiểm tra thông tin đã tồn tại trong file chưa ?
        vector<string> personIds, bookIds, eBookIds;
        string filename = "test_borrowInfos.txt";
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while(ss >> token){
                tokens.push_back(token.substr(1, token.size() - 2));
            }
            personIds.push_back(tokens[1]);
            bookIds.push_back(tokens[2]);
            eBookIds.push_back(tokens[3]);
        }   
        file.close();
        if(!personIds.empty()){
            for(int pos = 0; pos < personIds.size(); pos ++){
                if(this->personId == stoi(personIds[pos]) && this->bookId == stoi(bookIds[pos]) && this->eBookId == stoi(eBookIds[pos])){
                    return false;
                }
            }
        }
        return true;
    }

    void addInfo(){
        // Kiểm tra dữ liệu trước khi thêm vào file
        if(this->isValid()){
            cout << ">>> Them thong tin thanh cong !\n";
            string file_name = "test_borrowInfos.txt";
            ofstream file(file_name, ios::app);
            file << endl;
            file << "[" << id << "] ";
            file << "[" << personId << "] ";
            file << "[" << bookId << "] ";
            file << "[" << eBookId << "]";
            file.close();
        }
        else{
            cout << ">>> Thong tin da ton tai\n";
        }
    }

    void updateInfo(int new_personId, int new_bookId, int new_eBookId){
        // Validate dữ liệu trước khi cập nhật
        BorrowInfo valid_var(new_personId, new_bookId, new_eBookId);
        if(!valid_var.isValid()){
            return;
        }
        // Cập nhật dữ liệu
        this->personId = new_personId;
        this->bookId = new_bookId;
        this->eBookId = new_eBookId;

        // Thay đổi trong file
        string file_name = "test_borrowInfors.txt";
        fstream file(file_name);
        vector<string> lines;
        string line;
        while(getline(file, line)){
            lines.push_back(line);
        }
        // Thay đổi dữ liệu dựa theo personId
        vector<string> ID_list = this->getInfo(0);
        for(auto iter = ID_list.begin(); iter != ID_list.end(); iter ++){
            if(this->id == stoi(*iter)){
                int line_pos = iter - ID_list.begin();
                lines[line_pos] = "[" + to_string(this->id) + "] [" + to_string(new_personId) + "] ";
                lines[line_pos] += "[" + to_string(new_bookId) + "] [" + to_string(new_eBookId) + "]";
            }
        }
        // Đặt con trỏ về đầu tập tin để ghi lại dữ liệu
        file.seekg(0);
        for(const string& l : lines){
            file << l << endl;
        }
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