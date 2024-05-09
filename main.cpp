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

    void updatePerson(const string& filename, const string& newPersonInfo, string newPersonID) {
        ifstream inFile(filename); 
        ofstream outFile("temp_person.txt"); 

        string line;
        bool found = false; // Kiểm tra xem ID có tồn tại không

        // Đọc từng dòng từ file gốc
        while (getline(inFile, line)) {
            size_t startPos = line.find("["); // Tìm vị trí của ký tự '['
            size_t endPos = line.find("]", startPos); // Tìm vị trí của ký tự ']' sau ký tự '['
            
            // Nếu như vẫn còn đọc được dữ liệu
            if (startPos != string::npos && endPos != string::npos) {
                string personID = line.substr(startPos + 1, endPos - startPos - 1);

                // Nếu id của sách cần cập nhật == id hiện tại trong books.txt thì thay thế nó
                if (personID == newPersonID) {
                    outFile << '[' << personID << "] " << newPersonInfo << endl;
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
            if (rename("temp_person.txt", filename.c_str()) != 0) {
                cerr << "Khong the đoi ten file tam thoi." << endl;
                return;
            }

            cout << "Da cap nhat thong tin cua nguoi dung co ID = " << newPersonID << " thanh cong." << endl;
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần cập nhật
            remove("temp_person.txt");
            cout << "Khong tim thay nguoi dung co ID = " << newPersonID << " trong file." << endl;
        }
    }
};

class BorrowInfo{
private:
	int id = 1;
	int personId;
	int bookId;
	int eBookId;
public:
    BorrowInfo() {}

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
                    cout << ">>> Thong tin da ton tai, khong phu hop !\n";
                    return false;
                }
            }
        }
        return true;
    }

    void addInfo(){
        // Kiểm tra dữ liệu trước khi thêm vào file
        if(this->isValid()){
            string file_name = "test_borrowInfos.txt";
            ofstream file(file_name, ios::app);
            file << endl;
            file << "[" << id << "] ";
            file << "[" << personId << "] ";
            file << "[" << bookId << "] ";
            file << "[" << eBookId << "]";
            file.close();
            cout << ">>> THEM THONG TIN THANH CONG !\n";
        }
        else{
            cout << ">>> THONG TIN DA TON TAI !\n";
        }
    }

    void deleteInfo(){
        // Kiểm tra thông tin đã tồn tại trong file chưa ?
        vector<string> lines;
        vector<string> personIds, bookIds, eBookIds;
        string filename = "test_borrowInfos.txt";
        fstream file(filename);
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
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
        int del_pos = -1;
        if(!personIds.empty()){
            for(int pos = 0; pos < personIds.size(); pos ++){
                if(this->personId == stoi(personIds[pos]) && this->bookId == stoi(bookIds[pos]) && this->eBookId == stoi(eBookIds[pos])){
                    del_pos = pos;
                    break;    
                }
            }
        }
        if(del_pos == -1){
            cout << "Thong tin tra sach khong hop le !\n";
        }
        else{
            // Đặt con trỏ về đầu tập tin
            file.seekg(0);
            // Bỏ qua dòng chứa thông tin muốn xóa
            for(int pos = 0; pos < lines.size(); pos ++){
                if(pos != del_pos){
                    file << lines[pos] << endl;
                }
            }
            cout << "Da xoa borrowInfo line " << del_pos << endl;
        }
        file.close();
    }

    void displayInfo(){
        vector<string> personIds, bookIds, eBookIds;
        string filename = "test_borrowInfos.txt";
        fstream file(filename);
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
        vector<string> books, eBooks;
        for(int pos = 0; pos < personIds.size(); pos ++){
            if(this->personId == stoi(personIds[pos])){
                if(bookIds[pos] != "-1") books.push_back(bookIds[pos]);
                if(eBookIds[pos] != "-1") eBooks.push_back(eBookIds[pos]);
            }
        }
        if(books.empty() && eBooks.empty()){
            cout << "Ban chua muon cuon sach nao !\n";
            return;
        }
        if(!books.empty()){
            cout << "Ban da muon books co ID la : ";
            for(auto bookID : books){
                cout << bookID << " ";
            }
        }
        if(!eBooks.empty()){
            cout << "\nBan da muon eBooks co ID la : ";
            for(auto eBookID : eBooks){
                cout << eBookID << " ";
            }
            cout << endl;
        }
    }

    void updateInfo(int new_personId, int new_bookId, int new_eBookId){
        // Validate dữ liệu trước khi cập nhật
        BorrowInfo valid_check(new_personId, new_bookId, new_eBookId);
        if(!valid_check.isValid()){
            return;
        }
        // Cập nhật dữ liệu
        this->personId = new_personId;
        this->bookId = new_bookId;
        this->eBookId = new_eBookId;

        // Thay đổi dòng chứa dữ liệu cần sửa
        string file_name = "test_borrowInfors.txt";
        fstream file(file_name);
        vector<string> lines;
        string line;
        while(getline(file, line)){
            lines.push_back(line);
        }
        // Thay đổi dữ liệu dựa theo personId
        vector<string> personIds = this->getInfo(1);
        for(int pos = 0; pos < personIds.size(); pos ++){
            if(this->id == stoi(personIds[pos])){
                lines[pos] = "[" + to_string(this->id) + "] [" + to_string(this->personId) + "] ";
                lines[pos] += "[" + to_string(new_bookId) + "] [" + to_string(new_eBookId) + "]";
            }
        }
        // Đặt con trỏ về đầu tập tin để ghi lại dữ liệu
        file.seekg(0);
        for(const string& l : lines){
            file << l << endl;
        }
        file.close();
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
    User() {}

    User(string email, string password){
        this->email = email;
        this->password = password;
        //Validate dữ liệu
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
        string filename = "test_users.txt";
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
        // Kiểm tra email trùng lặp
        vector<string> emails = this->getInfo(1);
        for(auto email : emails){
            if(this->email == email) return false;
        }
        // Kiểm tra password phù hợp ...
        
        return true;
    }

    void Register(){
        // Kiểm tra dữ liệu trước khi thêm vào file
        if(this->isValid()){
            string file_name = "test_users.txt";
            ofstream file(file_name, ios::app);
            file << endl;
            file << "[" << id << "] ";
            file << "[" << email << "] ";
            file << "[" << password << "] ";
            file.close();
            cout << ">>> DANG KY THANH CONG !\n";
        }
        else{
            cout << ">>> THONG TIN DA TON TAI\n";
        }
    }

    bool correctInfo(){
        // Kiểm tra thông tin đăng nhập
        vector<string> emails, passwords;
        string filename = "test_users.txt";
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while(ss >> token){
                tokens.push_back(token.substr(1, token.size() - 2));
            }
            emails.push_back(tokens[1]);
            passwords.push_back(tokens[2]);
        }   
        file.close();
        if(!emails.empty()){
            for(int pos = 0; pos < emails.size(); pos ++){
                if(this->email == emails[pos] && this->password == passwords[pos]){
                    return true;
                }
            }
        }
        return false;
    }

    Person login(){
        if(this->correctInfo()){
            // vector<string> emails = getInformationFromFile("people.txt", 2);
        }
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

// Hàm lấy ra từng kiểu thông tin một trong file (ví dụ: trả về 1 vector<string> toàn ID)
vector<string> getInformationFromFile(const string& filename, int n) {
    vector<string> info;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (ss >> token) {
            tokens.push_back(token.substr(1, token.size() - 2));
        }
        
        info.push_back(tokens[n]);
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
            outFile << endl << '[' << to_string(mex) << "] " <<  bookInf;
            outFile.close();
            cout << "Thong tin cua cuon sach da duoc ghi thanh cong!\n\n";
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

    void getOneBook(const string& filename, int id, int data) {
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

        int pos = -1;
        for (int i = 0; i < cnt; ++i) {
            if (stoi(bookInfor[0][i]) == id) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            cout << "Khong ton tai cuon sach co ID la: " << id << '!' << endl;
        }
        else {
            cout << "Thong tin cuon sach co ID la: " << id << endl;
            for (int i = 0; i < data; ++i) {
                cout << '[' << bookInfor[i][pos] << "] ";
            }
            cout << endl;
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
            << "|   1.  Dang nhap.                                                                              |\n"
            << "|   2.  Dang ky.                                                                                |\n"
            << "|   3.  Them sach (Admin).                                                                      |\n"
            << "|   4.  Sua thong tin sach (Admin).                                                             |\n"
            << "|   5.  Xoa sach (Admin).                                                                       |\n"
            << "|   6.  Muon sach.                                                                              |\n"
            << "|   7.  Tra sach.                                                                               |\n"
            << "|   8.  Lay thong tin cac quyen sach.                                                           |\n"
            << "|   9.  Lay thong tin 1 quyen sach.                                                             |\n"
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
    BorrowInfo bI;

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
                    << "Welcome " << '<' << p.getRole() << '>' << endl;
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
                    scanf("\n");
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
                if(p.getRole() == "User"){
                    int personId, bookId, eBookId;
                    cout << "Nhap personId, bookId, eBookId\n";
                    cin >> personId >> bookId >> eBookId;
                    BorrowInfo bI(personId, bookId, eBookId);
                    bI.addInfo();
                }
                break;

            case 7: // Tinh nang 7: Tra sach.
                if(p.getRole() == "User"){
                    int personId, bookId, eBookId;
                    cout << "Nhap personId, bookId, eBookId\n";
                    cin >> personId >> bookId >> eBookId;
                    BorrowInfo bI(personId, bookId, eBookId);
                    bI.deleteInfo();
                }
                break;

            case 8: 
                cout << "Day la thong tin cac quyen sach hien tai:" << endl;
                b.getBooks("books.txt", 4);
                cout << endl;
                break;

            case 9: 
                cout << "Nhap vao ID cuon sach ban muon biet thong tin: ";
                int id;
                cin >> id;
                b.getOneBook("books.txt", id, 4);
                cout << endl;
                break;

            case 10:
                cout << "Day la thong tin cac quyen sach EBooks hien tai:" << endl;
                eb.getBooks("ebooks.txt", 6);
                cout << endl;
                break;

            case 11: 
                cout << "Nhap vao ID cuon sach EBook ban muon biet thong tin: ";
                int idEBook;
                cin >> idEBook;
                eb.getOneBook("ebooks.txt", idEBook, 6);
                cout << endl;
                break;

            case 12: // Tinh nang 12: Hien thi cac quyen sach da muon cua ban than (User).
                if(p.getRole() == "User"){
                    int personId, bookId, eBookId;
                    cout << "Nhap personId, bookId, eBookId\n";
                    cin >> personId >> bookId >> eBookId;
                    BorrowInfo bI(personId, bookId, eBookId);
                    // Hien thi id cac quyen sach da muon cua User
                    bI.displayInfo();
                }
                break;

            case 13: // Tinh nang 13: Hien thi tat ca sach cua 1 nguoi dung da muon theo id (Admin).
                
                break;

            case 14: // Tinh nang 14: Chinh sua thong tin ca nhan (User).
                break;

            case 15:
                if (p.getRole() == "User") {
                    cout << "Ban khong co quyen chinh sua thong tin nguoi khac!" << endl;
                }
                else {
                    vector<string> idPerson = getInformationFromFile("people.txt", 0);
                    string id;
                    cout << "Nhap vao id cua nguoi dung ban muon sua: ";
                    cin >> id;
                    while (isValid(idPerson, id) == true) {
                        cout    << "Khong ton tai nguoi dung co id: " << id << endl
                                << "Vui long nhap id nguoi dung hop le !!!" << endl
                                << "Nhap lai id cua nguoi dung ban muon sua: ";
                        cin >> id;
                    }
                    cout << "Nhap vao thong tin nguoi can chinh sua: ";
                    string info;
                    scanf("\n");
                    getline(cin, info);
                    p.updatePerson("people.txt", info, id);
                }
                cout << endl;
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