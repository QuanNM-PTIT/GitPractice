#include <bits/stdc++.h>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;

void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

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

bool isExistAlphaOrNum(string& s) {
    for (char c : s) {
        if (isalnum(c)) {
            return true;
        }
    }
    return false;
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

    Person(int id, string name, string email, string sex, string birthdate, string address, string phoneNumber, string role) {
        this->id = id;
        this->name = name;
        this->email = email;
        this->sex = sex;
        this->birthdate = birthdate;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = role;
    }

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
                setColor(5, 0);
                cerr << "Unable to delete the original file." << endl;
                setColor(7, 0);
                return;
            }

            // Đổi tên file tạm thời thành file gốc
            if (rename("temp_person.txt", filename.c_str()) != 0) {
                setColor(5, 0);
                cerr << "Cannot rename the file temporarily." << endl;
                setColor(7, 0);
                return;
            }

            setColor(5, 0);
            cout << "Successfully updated the information of the user with ID: " << newPersonID << "." << endl;
            setColor(7, 0);
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần cập nhật
            remove("temp_person.txt");
            setColor(5, 0);
            cout << "Cannot find the user with ID: " << newPersonID << " in the file." << endl;
            setColor(7, 0);
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
            setColor(5, 0);
            cout << "There is no user with ID: " << targetID << '!' << endl;
            setColor(7, 0);
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
        string filename = "borrowInfos.txt";
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
                    setColor(5, 0);
                    cout << ">>> Information already exists, not suitable!\n";
                    setColor(7, 0);
                    return false;
                }
            }
        }
        return true;
    }

    void addInfo(){
        // Kiểm tra dữ liệu trước khi thêm vào file
        if(this->isValid()){
            setColor(5, 0);
            cout << ">>> Successfully added information!\n";
            setColor(7, 0);
            string file_name = "borrowInfos.txt";
            ofstream file(file_name, ios::app);
            file << endl;
            file << "[" << id << "] ";
            file << "[" << personId << "] ";
            file << "[" << bookId << "] ";
            file << "[" << eBookId << "]";
            file.close();
        }
        else{
            setColor(5, 0);
            cout << ">>> Information already exists\n";
            setColor(7, 0);
        }
    }

    void deleteInfo(){
        // Kiểm tra thông tin đã tồn tại trong file chưa ?
        vector<string> lines;
        vector<string> personIds, bookIds, eBookIds;
        string filename = "borrowInfos.txt";
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
            setColor(5, 0);
            cout << "Invalid return book information!\n";
            setColor(7, 0);
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
            setColor(5, 0);
            cout << "Deleted borrowInfo line " << del_pos << endl;
            setColor(7, 0);
        }
        file.close();
    }

    void displayInfo(const int personID){
        vector<string> personIds, bookIds, eBookIds;
        string filename = "borrowInfos.txt";
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
            if(personID == stoi(personIds[pos])){
                if(bookIds[pos] != "-1") books.push_back(bookIds[pos]);
                if(eBookIds[pos] != "-1") eBooks.push_back(eBookIds[pos]);
            }
        }
        if(books.empty() && eBooks.empty()){
            setColor(5, 0);
            cout << "You haven't borrowed any book!\n";
            setColor(7, 0);
            return;
        }
        if(!books.empty()){
            setColor(5, 0);
            cout << "You have borrowed books with ID: ";
            setColor(7, 0);
            for(auto bookID : books){
                cout << bookID << " ";
            }
        }
        if(!eBooks.empty()){
            setColor(5, 0);
            cout << "\nYou have borrowed eBooks with ID: ";
            setColor(7, 0);
            for(auto eBookID : eBooks){
                cout << eBookID << " ";
            }
            cout << endl;
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

        // Thay đổi dòng chứa dữ liệu cần sửa
        string file_name = "borrowInfos.txt";
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

    // Hàm tạo ID mới cho người dùng
    int getNewUserID(const string& filename) {
        ifstream file(filename);
        vector<string> dataID = getInformationFromFile(filename, 0);

        set<long long> dataIDInt;
        for (string s : dataID) {
            dataIDInt.insert(stoi(s));
        } 

        int mex = 0;
        for (auto it = dataIDInt.begin(); it != dataIDInt.end(); ++it) {\
            if (*it > mex + 1) {
                break;
            }
            mex = *it;
        }
        
        file.close();
        return ++mex;
    }

    bool emailExists(const string& email) {
        vector<string> emails = getInformationFromFile("users.txt", 1);
        for (const string& e : emails) {
            if (e == email) {
                return true;
            }
        }
        return false;
    }

    bool validatePassword(const string& email, const string& password) {
        vector<string> emails = getInformationFromFile("users.txt", 1);
        vector<string> passwords = getInformationFromFile("users.txt", 2);
        for (size_t i = 0; i < emails.size(); ++i) {
            if (emails[i] == email && passwords[i] == password) {
                return true;
            }
        }
        return false;
    }

    void Register(Person& p){
        string fullName, email, gender, birthdate, address, phoneNumber, password;
    
        // Nhập thông tin từ người dùng
        setColor(5, 0);
        cout << "Enter full name: ";
        setColor(7, 0);
        scanf("\n");
        getline(cin, fullName);

        while (isExistAlphaOrNum(fullName) == false) {
            setColor(5, 0);
            cout << "Wrong format, please enter correct format, no special characters!" << endl;
            setColor(7, 0);
            scanf("\n");
            getline(cin, fullName);
        }
        
        setColor(5, 0);
        cout << "Enter email: ";
        setColor(7, 0);
        cin >> email;

        // Kiểm tra email đã tồn tại chưa
        while (emailExists(email)) {
            setColor(5, 0);
            cout << "Email already exists. Please choose another email." << endl;
            setColor(7, 0);
            cin >> email;
        }

        setColor(5, 0);
        cout << "Enter gender: ";
        setColor(7, 0);
        cin >> gender;

        while (isExistAlphaOrNum(gender) == false) {
            setColor(5, 0);
            cout << "Wrong format, please enter correct format, no special characters!" << endl;
            setColor(7, 0);
            scanf("\n");
            cin >> gender;
        }
        
        setColor(5, 0);
        cout << "Enter birthdate: ";
        setColor(7, 0);
        cin >> birthdate;

        while (isExistAlphaOrNum(birthdate) == false) {
            setColor(5, 0);
            cout << "Wrong format, please enter correct format, no special characters!" << endl;
            setColor(7, 0);
            scanf("\n");
            cin >> birthdate;
        }

        setColor(5, 0);
        cout << "Enter address: ";
        setColor(7, 0);
        cin.ignore();
        getline(cin, address);

        while (isExistAlphaOrNum(address) == false) {
            setColor(5, 0);
            cout << "Wrong format, please enter correct format, no special characters!" << endl;
            setColor(7, 0);
            scanf("\n");
            cin >> address;
        }

        setColor(5, 0);
        cout << "Enter phone number: ";
        setColor(7, 0);
        cin >> phoneNumber;

        while (isExistAlphaOrNum(phoneNumber) == false) {
            setColor(5, 0);
            cout << "Wrong format, please enter correct format, no special characters!" << endl;
            setColor(7, 0);
            scanf("\n");
            cin >> phoneNumber;
        }

        // Tạo ID mới cho người dùng
        int personID = getNewUserID("people.txt");

        // Ghi thông tin người dùng vào file people.txt
        ofstream personFile("people.txt", ios_base::app);
        if (personFile.is_open()) {
            personFile << endl << "[" + to_string(personID) + "] [" + fullName + "] [" + email + "] [" + gender + "] [" + birthdate + "] [" + address + "] [" + phoneNumber + "] [User]";;
            personFile.close();
        } 
        else {
            setColor(5, 0);
            cerr << "Unable to open file people.txt" << endl;
            setColor(7, 0);
        }
        
        // Nhập mật khẩu
        setColor(5, 0);
        cout << "Create password: ";
        setColor(7, 0);
        cin >> password;

        while (password == "" or password.size() < 8) {
            setColor(5, 0);
            cout << "Your password is too weak, please enter a password longer than 8 characters!" << endl;
            cout << "Create password: ";
            setColor(7, 0);
            cin >> password;
        }

        // Ghi email và mật khẩu vào file user.txt
        int userID = getNewUserID("users.txt");
        ofstream userFile("users.txt", ios_base::app);
        if (userFile.is_open()) {
            userFile << endl << "[" + to_string(userID) + "] [" + email + "] [" + password + "]";
            userFile.close();
            setColor(5, 0);
            cout << "Registration successful!" << endl;
            setColor(7, 0);
        } 
        else {
            setColor(5, 0);
            cerr << "Unable to open file users.txt" << endl;
            setColor(7, 0);
        }

        p.setID(personID);
        p.setName(fullName);
        p.setEmail(email);
        p.setSex(gender);
        p.setBirthdate(birthdate);
        p.setAddress(address);
        p.setPhoneNumber(phoneNumber);
        p.setRole("User");
    }
    
    bool login(Person& p){
        string email, password;

        while (true) {
            setColor(5, 0);
            cout << "Enter email: ";
            setColor(7, 0);
            cin >> email;

            if (!emailExists(email)) {
                setColor(5, 0);
                cout << "Email does not exist. Please try again." << endl;
                setColor(7, 0);
            } 
            else {
                break;
            }
        }

        while (true) {
            setColor(5, 0);
            cout << "Enter password: ";
            setColor(7, 0);
            cin >> password;

            if (!validatePassword(email, password)) {
                setColor(5, 0);
                cout << "Invalid password. Please try again." << endl;
                setColor(7, 0);
            } 
            else {
                break;
            }
        }

        ifstream file("people.txt");
        string line;
        while (getline(file, line)) {
            size_t pos = 0;
            string token;
            vector<string> tokens;

            while ((pos = line.find("] [")) != string::npos) {
                token = line.substr(1, pos - 1);
                tokens.push_back(token);
                line.erase(0, pos + 2);
            }

            if (!line.empty()) {
                line.pop_back();
                line.erase(0, 1);
                tokens.push_back(line);
            }

            if (tokens.size() >= 7 && tokens[2] == email) { 
                file.close();
                p.setName(tokens[1]);
                p.setEmail(tokens[2]);
                p.setSex(tokens[3]);
                p.setBirthdate(tokens[4]);
                p.setAddress(tokens[5]);
                p.setPhoneNumber(tokens[6]);
                p.setRole(tokens[7]);
            }
        }
        file.close();
        return true;
    }  

    void logout(Person& p){
        setColor(5, 0);
        cout << "Logging out..." << endl;
        setColor(7, 0);

        p.setName("");
        p.setEmail("");
        p.setSex("");
        p.setBirthdate("");
        p.setAddress("");
        p.setPhoneNumber("");
        p.setRole("");
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
            setColor(5, 0);
            cout << "The information of the book has been successfully written!\n";
            setColor(7, 0);
        }
    }

    void getBooks(const string& filename, int data) const {
        ifstream file(filename);
        string line;
        vector<string> lines;

         while (getline(file, line)){
            lines.push_back(line);
        }

        file.close();

        for (const string &line : lines){
            cout << line << endl;
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
                setColor(5, 0);
                cerr << "Unable to delete the original file." << endl;
                setColor(7, 0);
                return;
            }

            // Đổi tên file tạm thời thành file gốc
            if (rename("temp_books.txt", filename.c_str()) != 0) {
                setColor(5, 0);
                cerr << "Cannot rename the file temporarily." << endl;
                setColor(7, 0);
                return;
            }

            setColor(5, 0);
            cout << "Successfully deleted the information of the book with ID: " << id << "." << endl;
            setColor(7, 0);
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần xoá
            remove("temp_books.txt");
            setColor(5, 0);
            cout << "Cannot find the book with ID: " << id << " in the file." << endl;
            setColor(7, 0);
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
                setColor(5, 0);
                cerr << "Unable to delete the original file." << endl;
                setColor(7, 0);
                return;
            }

            // Đổi tên file tạm thời thành file gốc
            if (rename("temp_books.txt", filename.c_str()) != 0) {
                setColor(5, 0);
                cerr << "Cannot rename the file temporarily." << endl;
                setColor(7, 0);
                return;
            }

            setColor(5, 0);
            cout << "Successfully updated the information of the book with ID = " << newBookID << "." << endl;
            setColor(7, 0);
        } 
        else {
            // Xoá file tạm thời nếu không tìm thấy cuốn sách cần cập nhật
            remove("temp_books.txt");
            setColor(5, 0);
            cout << "Cannot find Book with ID: " << newBookID << " in file." << endl;
            setColor(7, 0);
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
            setColor(5, 0);
            cout << "There is no book with the ID: " << id << '!' << endl;
            setColor(7, 0);
        }
        else {
            setColor(5, 0);
            cout << "The information of the book with ID " << id << " is:" << endl;
            setColor(7, 0);
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
            setColor(5, 0);
            cout << "There is no book with the ID: " << targetID << '!' << endl;
            setColor(7, 0);
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

int cnt = 0;
vector<string> attributeOfPerson = {"name", "email", "gender", "date of birth", "address", "phone number"};
vector<string> attributeOfBook = {"book name", "author name", "quantity"};

string input(string& data, vector<string>& attribute) {
    setColor(5, 0);
    cout << "Enter the " << attribute[cnt] << " you want to edit, if you don't want to edit anything, enter (None): ";
    setColor(7, 0);
    scanf("\n");
    getline(cin, data);
    while (isExistAlphaOrNum(data) == false) {
        setColor(5, 0);
        cout    << "Invalid input, it must contain at least 1 character!" << endl
                << "Re-enter the " << attribute[cnt] << " you want to edit, if you don't want to edit anything, enter (None): ";
        setColor(7, 0);
        scanf("\n");
        getline(cin, data);
    }

    ++cnt;

    string tmp = data;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    if (tmp == "none") {
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
    setColor(5, 0);
    cout << "Enter the role you want to edit, if you don't want to edit anything, enter (None): ";
    setColor(7, 0);
    scanf("\n");
    getline(cin, data);
    while (isExistAlphaOrNum(data) == false) {
        setColor(5, 0);
        cout    << "Invalid input, it must contain at least 1 character!" << endl
                << "Re-enter the role you want to edit, if you don't want to edit anything, enter (None): ";
        scanf("\n");
        setColor(7, 0);
        getline(cin, data);
    }

    string tmp = data;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    if (tmp == "none") {
        return "-1";
    }
    
    return data;
}

// In ra danh sách tính năng với màu hồng
void menu() {
    setColor(11, 0); // Màu xanh cyan cho chữ, nền đen
    cout    << "-------------------------------------------------------------------------------------------------\n"
            << "|                       ___Please choose one of the following features___                       |\n" 
            << "|   1.  Login.                                                                                  |\n"
            << "|   2.  Register.                                                                               |\n"
            << "|   3.  Add book (Admin).                                                                       |\n"
            << "|   4.  Edit book information (Admin).                                                          |\n"
            << "|   5.  Delete book (Admin).                                                                    |\n"
            << "|   6.  Borrow book.                                                                            |\n"
            << "|   7.  Return book.                                                                            |\n"
            << "|   8.  Get information of all books.                                                           |\n"
            << "|   9.  Get information of a book.                                                              |\n"
            << "|   10. Get information of all eBooks available.                                                |\n"
            << "|   11. Get information of an eBook with id.                                                    |\n"
            << "|   12. Display all borrowed books of yourself (User).                                          |\n"
            << "|   13. Display all borrowed books of a user by user id (Admin).                                |\n"
            << "|   14. Edit personal information.                                                              |\n"
            << "|   15. Edit personal information of another user (Admin).                                      |\n"
            << "|   16. Logout.                                                                                 |\n"
            << "|   17. Exit program.                                                                           |\n"
            << "-------------------------------------------------------------------------------------------------\n";
    setColor(7, 0); // Đặt lại màu mặc định (màu trắng chữ, nền đen)
}

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseAndClear() {
    setColor(5, 0);
    cout << "Press (Enter) to go back to the Menu..." << endl;
    setColor(7, 0);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
    cin.get(); // Wait for the user to press Enter
    clearScreen();
}

int main() {
    clearScreen();
    menu();

    string str;
    int query = 0;
    bool welcome = false;

    Person p;
    User u;
    Book b;
    EBook eb;
    BorrowInfo bI;

    while (true) {
        while (!welcome) {
            setColor(5, 0);
            cout << "Login/Register to use features!!!\n";
            setColor(7, 0);

            try {
                cin >> query;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    setColor(12, 0);
                    throw runtime_error("Invalid format! Please try again.\n");
                    setColor(7, 0);
                }

                switch(query) {
                    case 1: 
                        u.login(p);
                        welcome = true;
                        break;

                    case 2: 
                        u.Register(p);
                        welcome = true;
                        break;
                    
                    case 17:
                        return 0;
                        break;
                }
            }
            catch (const exception& e) {
                setColor(12, 0);
                cout << e.what() << endl;
                setColor(7, 0);
            }

            if (welcome) {
                setColor(5, 0);
                cout << "\nCongratulations, you have successfully logged in!" << endl
                    << "Welcome " << '<';
                setColor(7, 0); 
                cout << p.getName();
                setColor(5, 0); 
                cout << '>' << endl;
                setColor(7, 0);
                pauseAndClear();
                menu();
            }
        }

        setColor(5, 0);
        cout << "Enter the feature you want to use: ";
        setColor(7, 0);

        try {
            cin >> query;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                setColor(12, 0);
                throw runtime_error("Invalid format! Please try again.\n");
                setColor(7, 0);
            }

            switch (query) {
                case 3: 
                    if (p.getRole() == "Admin") {
                        setColor(5, 0);
                        cout << "Enter book information: ";
                        setColor(7, 0);
                        string bookInfo;
                        cin.ignore();
                        getline(cin, bookInfo);
                        b.addBook("books.txt", bookInfo);
                    } 
                    else {
                        setColor(5, 0);
                        cout << "You do not have permission to add book information!!!\n";
                        setColor(7, 0);
                    }
                    break;

                case 4:
                    if (p.getRole() == "User") {
                        setColor(5, 0);
                        cout << "You do not have permission to edit book information!" << endl;
                        setColor(7, 0);
                    } 
                    else {
                        vector<string> idBook = getInformationFromFile("books.txt", 0);
                        string id;
                        setColor(5, 0);
                        cout << "Enter the id of the book you want to edit: ";
                        setColor(7, 0);
                        cin >> id;

                        while (!isValid(idBook, id)) {
                            setColor(5, 0);
                            cout << "The book with id: " << id << " does not exist" << endl
                                 << "Please enter a valid book id!!!" << endl
                                 << "Re-enter the id of the book you want to edit: ";
                            setColor(7, 0);
                            cin >> id;
                        }

                        Book tmp = b.getData("books.txt", id, 4);
                        string info = editBookData(tmp);
                        b.updateBook("books.txt", info, id);
                    }
                    break;

                case 5:
                    if (p.getRole() == "User") {
                        setColor(5, 0);
                        cout << "You do not have permission to delete books!\n";
                        setColor(7, 0);
                    }
                    else {
                        int idDelBook;
                        setColor(5, 0);
                        cout << "Enter the ID of the book to be deleted: ";
                        setColor(7, 0);
                        cin >> idDelBook;
                        b.deleteBook("books.txt", idDelBook);
                    }
                    break;

                case 6: 
                    if (p.getRole() == "User") {
                        int personId, bookId, eBookId;
                        setColor(5, 0);
                        cout << "Enter personId, bookId, eBookId\n";
                        setColor(7, 0);
                        cin >> personId >> bookId >> eBookId;
                        BorrowInfo bI(personId, bookId, eBookId);
                        bI.addInfo();
                    } 
                    else {
                        setColor(5, 0);
                        cout << "You do not have permission to add book information!\n"; 
                        setColor(7, 0);
                    }
                    break;

                case 7: 
                    if (p.getRole() == "User") {
                        int personId, bookId, eBookId;
                        setColor(5, 0);
                        cout << "Enter personId, bookId, eBookId\n";
                        setColor(7, 0);
                        cin >> personId >> bookId >> eBookId;
                        BorrowInfo bI(personId, bookId, eBookId);
                        bI.deleteInfo();
                    } 
                    else {
                        setColor(5, 0);
                        cout << "You do not have permission to delete books!\n";
                        setColor(7, 0);
                    }
                    break;

                case 8: 
                    setColor(5, 0);
                    cout << "Here is the information of the current books:" << endl;
                    setColor(7, 0);
                    b.getBooks("books.txt", 4);
                    break;

                case 9: 
                    setColor(5, 0);
                    cout << "Enter the ID of the book you want information about: ";
                    setColor(7, 0);
                    int id;
                    cin >> id;
                    b.getOneBook("books.txt", id, 4);
                    break;

                case 10:
                    setColor(5, 0);
                    cout << "Here is the information of the current EBooks:" << endl;
                    setColor(7, 0);
                    eb.getBooks("ebooks.txt", 6);
                    break;

                case 11: 
                    setColor(5, 0);
                    cout << "Enter the ID of the EBook you want information about: ";
                    setColor(7, 0);
                    int idEBook;
                    cin >> idEBook;
                    eb.getOneBook("ebooks.txt", idEBook, 6);
                    break;

                case 12: 
                    bI.displayInfo(p.getID());
                    break;

                case 13: 
                    if (p.getRole() == "User") {
                        setColor(5, 0);
                        cout << "You do not have permission to use this feature!!!" << endl;
                        setColor(7, 0);
                    } 
                    else {
                        int id;
                        setColor(5, 0);
                        cout << "Enter the ID of the user you want to see their borrowed books: ";
                        setColor(7, 0);
                        cin >> id;
                        bI.displayInfo(id);
                    }
                    break;

                case 14:
                    str = editPersonalData(p);
                    str += '[' + p.getRole() + ']';
                    p.updatePerson("people.txt", str, to_string(p.getID()));
                    break;

                case 15:
                    if (p.getRole() == "User") {
                        setColor(5, 0);
                        cout << "You do not have permission to edit other users' information!" << endl;
                        setColor(7, 0);
                    } 
                    else {
                        vector<string> idPerson = getInformationFromFile("people.txt", 0);
                        string id;
                        setColor(5, 0);
                        cout << "Enter the id of the user you want to edit: ";
                        setColor(7, 0);
                        cin >> id;

                        while (!isValid(idPerson, id)) {
                            setColor(5, 0);
                            cout << "The user with id: " << id << " does not exist" << endl
                                 << "Please enter a valid user id!!!" << endl
                                 << "Re-enter the id of the user you want to edit: ";
                            setColor(7, 0);
                            cin >> id;
                        }

                        Person tmp = p.getData("people.txt", id, 8);
                        string info = editPersonalData(tmp);
                        string newRole = changeRole(newRole);

                        if (newRole == "-1") {
                            info += '[' + tmp.getRole() + ']';
                        } 
                        else {
                            info += '[' + newRole + ']';
                        }

                        p.updatePerson("people.txt", info, id);
                    }
                    break;

                case 16: 
                    u.logout(p);
                    welcome = false;
                    break;

                case 17:
                    return 0;
                    break;
            }

            if (query < 3 or query > 17) {
                setColor(12, 0);
                cout << "This feature does not exist !!!" << endl;
                setColor(7, 0);
            }

            pauseAndClear();
            menu();
        }
        catch (const exception& e) {
            setColor(12, 0);
            cout << e.what() << endl;
            setColor(7, 0);
        }
    }
    return 0;
}