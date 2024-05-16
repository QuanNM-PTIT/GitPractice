#include <bits/stdc++.h>

using namespace std;

// Hàm lấy ra từng kiểu thông tin một trong file (ví dụ: trả về 1 vector<string> toàn ID)
vector<string> getInformationFromFile(const string& filename, int n) {
    vector<string> info;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
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

    Person getData(const string& filename, const string& targetID, int data) {
        ifstream file(filename);
        string line;
        int cnt = 0;

        while (getline(file, line)) {
            ++cnt;
        }

        file.close();

        vector<vector<string>> personData(data);

        for (int i = 0; i < data; ++i) {
            personData[i] = getInformationFromFile(filename, i);
        }

        int pos = -1;
        for (int i = 0; i < cnt; ++i) {
            if (personData[0][i] == targetID) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            cout << "Khong ton tai nguoi dung co ID la: " << targetID << '!' << endl;
        }
        else {
            return Person(personData[1][pos], personData[2][pos], personData[3][pos], personData[4][pos], personData[5][pos], personData[6][pos], personData[7][pos]);
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
    User() {}

    User(string email, string password){
        this->email = email;
        this->password = password;
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
        string filename = "test_user.txt";
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

    string getAuthor() const{
        return this -> author;
    }
    
    void setAuthor(const string& author) {
        this -> author = author;
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

    void deleteBook(const string& filename, int id) const {
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

    void updateBook(const string& filename, const string& newBookInfo, string newBookID) {
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
                string bookID = line.substr(startPos + 1, endPos - startPos - 1);

                // Nếu id của sách cần cập nhật == id hiện tại trong books.txt thì thay thế nó
                if (bookID == newBookID) {
                    outFile << '[' << bookID << "] " << newBookInfo << endl;
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

            cout << "Da cap nhat thong tin cuon sach co ID = " << newBookID << " thanh cong." << endl;
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần cập nhật
            remove("temp_books.txt");
            cout << "Khong tim thay cuon sach co ID = " << newBookID << " trong file." << endl;
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

    Book getData(const string& filename, const string& targetID, int data) {
        ifstream file(filename);
        string line;
        int cnt = 0;

        while (getline(file, line)) {
            ++cnt;
        }

        file.close();

        vector<vector<string>> bookData(data);

        for (int i = 0; i < data; ++i) {
            bookData[i] = getInformationFromFile(filename, i);
        }

        int pos = -1;
        for (int i = 0; i < cnt; ++i) {
            if (bookData[0][i] == targetID) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            cout << "Khong ton tai cuon sach co ID la: " << targetID << '!' << endl;
        }
        else {
            return Book(bookData[1][pos], bookData[2][pos], stoi(bookData[3][pos]));
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

bool isExistAlphaOrNum(string& s) {
    for (char c : s) {
        if (isalnum(c)) {
            return true;
        }
    }
    return false;
}

int cnt = 0;

vector<string> attributeOfPerson = {"ten", "email", "gioi tinh", "ngay sinh", "dia chi", "so dien thoai"};
vector<string> attributeOfBook = {"ten sach", "ten tac gia", "so luong"};

string input(string& data, vector<string>& attribute) {
    cout << "Nhap vao " << attribute[cnt] << " ban muon chinh sua, neu khong chinh sua gi thi nhap (Khong): ";
    scanf("\n");
    getline(cin, data);
    while (isExistAlphaOrNum(data) == false) {
        cout    << "Nhap sai du lieu cho, yeu cau phai co it nhat 1 ky tu!" << endl
                << "Nhap lai  " << attribute[cnt] << " ban muon chinh sua, neu khong chinh sua gi thi nhap (Khong): ";
        scanf("\n");
        getline(cin, data);
    }

    ++cnt;

    string tmp = data;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    if (tmp == "khong") {
        return "-1";
    }
    
    return data;
}

string editPersonalData(Person& p) {
    cnt = 0;
    string info = "";

    string name;
    name = input(name, attributeOfPerson);
    if (name == "-1") {
        info += '[' + p.getName() + "] ";
    }
    else {
        info += '[' + name + "] ";
    }

    string email;
    email = input(email, attributeOfPerson);
    if (email == "-1") {
        info += '[' + p.getEmail() + "] ";
    }
    else {
        info += '[' + email + "] ";
    }

    string sex;
    sex = input(sex, attributeOfPerson);
    if (sex == "-1") {
        info += '[' + p.getSex() + "] ";
    }
    else {
        info += '[' + sex + "] ";
    }

    string birthdate;
    birthdate = input(birthdate, attributeOfPerson);
    if (birthdate == "-1") {
        info += '[' + p.getBirthdate() + "] ";
    }
    else {
        info += '[' + birthdate + "] ";
    }

    string address;
    address = input(address, attributeOfPerson);
    if (address == "-1") {
        info += '[' + p.getAddress() + "] ";
    }
    else {
        info += '[' + address + "] ";
    }

    string phoneNumber;
    phoneNumber = input(phoneNumber, attributeOfPerson);
    if (phoneNumber == "-1") {
        info += '[' + p.getPhoneNumber() + "] ";
    }
    else {
        info += '[' + phoneNumber + "] ";
    }
    return info;
}

string editBookData(Book& b){
    cnt = 0;
    string info = "";

    string title;
    title = input(title, attributeOfBook);
    if (title == "-1") {
        info += '[' + b.getTitle() + "] ";
    }
    else {
        info += '[' + title + "] ";
    }

    string author;
    author = input(author, attributeOfBook);
    if (title == "-1") {
        info += '[' + b.getAuthor() + "] ";
    }
    else {
        info += '[' + author + "] ";
    }

    string quantity;
    quantity = input(quantity, attributeOfBook);
    if (title == "-1") {
        info += '[' + to_string(b.getQuantity()) + "] ";
    }
    else {
        info += '[' + quantity + "] ";
    }

    return info;
}

string changeRole(string& data) {
    cout << "Nhap vao role ban muon chinh sua, neu khong chinh sua gi thi nhap (Khong): ";
    scanf("\n");
    getline(cin, data);
    while (isExistAlphaOrNum(data) == false) {
        cout    << "Nhap sai du lieu cho, yeu cau phai co it nhat 1 ky tu!" << endl
                << "Nhap lai role ban muon chinh sua, neu khong chinh sua gi thi nhap (Khong): ";
        scanf("\n");
        getline(cin, data);
    }

    string tmp = data;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    if (tmp == "khong") {
        return "-1";
    }
    
    return data;
}

string str;

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

            // Try...catch để bắt lỗi nhập không đúng định dạng số cho query
            try {
                cin >> query;

                if (cin.fail() == true) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Sai dinh dang! Vui long nhap lai.\n");
                }

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
            catch (const exception& e) {
                cout << e.what() << endl;
            }
        }

        if (welcome == true) {
            cout    << endl << "Chuc mung ban da dang nhap thanh cong!" << endl
                    << "Welcome " << '<' << p.getRole() << '>' << endl;
            welcome = false;
            cout << endl;
        }

        cout << "Nhap vao tinh nang ban muon su dung: ";

        try {
            cin >> query;

            if (cin.fail() == true) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Sai dinh dang! Vui long nhap lai.\n");
            }

            cout << endl;

            switch (query) {
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
                        vector<string> idBook = getInformationFromFile("books.txt", 0);
                        string id;
                        cout << "Nhap vao id cuon sach ban muon sua: ";
                        cin >> id;

                        while (isValid(idBook, id) == true) {
                            cout    << "Khong ton tai cuon sach co id: " << id << endl
                                    << "Vui long nhap id cua cuon sach hop le !!!" << endl
                                    << "Nhap lai id cua cuon sach ban muon sua: ";
                            cin >> id;
                        }

                        Book tmp;
                        tmp = b.getData("books.txt", id, 4);

                        string info;
                        info = editBookData(tmp);
                        b.updateBook("books.txt", info, id);
                    }
                    cout << endl;
                    break;

                case 5:
                    if (p.getRole() == "User") {
                        cout << "Ban khong co quyen xoa sach!\n";
                    }
                    else {
                        int idDelBook;
                        cout << "Nhap vao ID cuon sach can xoa: ";
                        cin >> idDelBook;
                        b.deleteBook("books.txt", idDelBook);
                    }
                    break;

                case 6: // Tinh nang 6: Muon sach.
                    break;

                case 7: // Tinh nang 7: Tra sach.
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
                    break;

                case 13: // Tinh nang 13: Hien thi tat ca sach cua 1 nguoi dung da muon theo id (Admin).
                    break;

                case 14:
                    str = editPersonalData(p);
                    str += '[' + p.getRole() + ']';

                    p.updatePerson("people.txt", str, to_string(p.getID()));
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

                        Person tmp;
                        tmp = p.getData("people.txt", id, 8);

                        string info;
                        info = editPersonalData(tmp);
                        string newRole;
                        newRole = changeRole(newRole);
                        if (newRole == "-1") {
                            info += '[' + tmp.getRole() + ']';
                        }
                        else {
                            info += '[' + newRole + ']';
                        }

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
        catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}