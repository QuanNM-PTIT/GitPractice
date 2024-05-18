#include <bits/stdc++.h>

using namespace std;
class Book
{
protected:
    int id;
    string title;
    string author;
    int quantity;

public:
    Book() : id(0), title(""), author(""), quantity(0) {}

    Book(int id, string title, string author, int quantity) : id(id), title(title), author(author), quantity(quantity) {}

    int getId()
    {
        return id;
    }
    int getQuantity()
    {
        return quantity;
    }
    string getTitle()
    {
        return title;
    }
    string getAuthor()
    {
        return author;
    }

    int getNextAvailableId()
    {
        ifstream file("books.txt");
        if (file.is_open())
        {
            int lineCount = 0;
            string line;
            while (getline(file, line))
            {
                lineCount++;
            }
            file.close();
            return lineCount + 1; // id là dòng tiếp theo sau khi đã đếm được số dòng
        }
        return 1; // Trả về 1 nếu không mở được file
    }

    void addBook()
    {
        id = getNextAvailableId(); // Gán id là id bé nhất chưa xuất hiện
        cout << "Enter title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author: ";
        getline(cin, author);
        cout << "Enter quantity: ";
        cin >> quantity;

        // Kiểm tra và ghi vào file
        ofstream file("books.txt", ios::app);
        if (file.is_open())
        {
            file << "[" << id << "] "
                 << "[" << title << "] "
                 << "[" << author << "] "
                 << "[" << quantity << "] " << endl;
            file.close();
            cout << "Add Done\n";
        }
        else
        {
            cout << "Error!\n";
        }
    }

    vector<Book> getBooks()
    {
        vector<Book> ans;
        ifstream file("books.txt");
        if (file.is_open())
        {
            string line;
            while (std::getline(file, line))
            {
                stringstream ss(line);
                int Id, Quantity;
                string Author, Title;
                char c;

                ss >> c >> Id >> c >> c;
                std::getline(ss, Title, ']');
                ss >> c;
                std::getline(ss, Author, ']');
                ss >> c >> Quantity; // Sửa lại để đọc Quantity trực tiếp

                Book book(Id, Author, Title, Quantity);
                ans.push_back(book);
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file.\n";
        }
        return ans;
    }
    void updateBook(int idToUpdate)
    {
        string newTitle;
        string newAuthor;
        int newQuantity;

        cout << "Enter new title: ";
        cin.ignore();
        getline(cin, newTitle);
        cout << "Enter new author: ";
        getline(cin, newAuthor);
        cout << "Enter new quantity: ";
        cin >> newQuantity;

        vector<string> lines;
        ifstream file("books.txt");
        if (!file.is_open())
        {
            cerr << "Error" << endl;
            return;
        }

        string line;
        while (std::getline(file, line))
        {
            stringstream ss(line);
            int id, quantity;
            string title, author;

            char bracket;
            ss >> bracket >> id >> bracket;
            std::getline(ss, title, ']');
            std::getline(ss, author, ']');
            ss >> bracket >> quantity >> bracket;

            if (id == idToUpdate)
            {
                stringstream updatedLine;
                updatedLine << "[" << id << "] [" << newTitle << "] [" << newAuthor << "] [" << newQuantity << "]";
                lines.push_back(updatedLine.str());
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile("books.txt");
        if (!outFile.is_open())
        {
            cerr << "Error!" << endl;
            return;
        }

        for (const auto &line : lines)
        {
            outFile << line << endl;
        }
        outFile.close();

        cout << "Book with ID " << idToUpdate << " Updated done!" << endl;
    }

    void MinusQuantityBook(int idToUpdate, string title, string author, int newQuantity)
    {
        // string newTitle;
        // string newAuthor;
        // int newQuantity;

        // cout << "Enter new title: ";
        // cin.ignore();
        // getline(cin, newTitle);
        // cout << "Enter new author: ";
        // getline(cin, newAuthor);
        // cout << "Enter new quantity: ";
        // cin >> newQuantity;

        vector<string> lines;
        ifstream file("books.txt");
        if (!file.is_open())
        {
            cerr << "Error" << endl;
            return;
        }

        string line;
        while (std::getline(file, line))
        {
            stringstream ss(line);
            int id, quantity;
            string title, author;

            char bracket;
            ss >> bracket >> id >> bracket >> bracket;
            std::getline(ss, title, ']');
            ss >> bracket;
            std::getline(ss, author, ']');
            ss >> bracket >> quantity >> bracket;

            if (id == idToUpdate)
            {
                stringstream updatedLine;
                updatedLine << "[" << id << "] [" << title << "] [" << author << "] [" << newQuantity << "]";
                lines.push_back(updatedLine.str());
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile("books.txt");
        if (!outFile.is_open())
        {
            cerr << "Error!" << endl;
            return;
        }

        for (const auto &line : lines)
        {
            outFile << line << endl;
        }
        outFile.close();

        // cout << "Book with ID " << idToUpdate << " Updated done!" << endl;
    }

    void deleteBook(int idToDelete)
    {
        vector<string> lines;
        ifstream file("books.txt");
        if (!file.is_open())
        {
            cerr << "Error!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            int id, quantity;
            string title, author;

            char bracket;
            ss >> bracket >> id >> bracket;
            getline(ss, title, ']');
            getline(ss, author, ']');
            ss >> bracket >> quantity >> bracket;

            if (id == idToDelete)
            {
                found = true;
                cout << "Book with ID " << id << " Deleted done!" << endl;
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        if (!found)
        {
            cerr << "Error: Book with ID " << idToDelete << " not found." << endl;
            return;
        }

        ofstream outFile("books.txt");
        if (!outFile.is_open())
        {
            cerr << "Error!" << endl;
            return;
        }

        for (const auto &line : lines)
        {
            outFile << line << endl;
        }
        outFile.close();
    }
};

class EBook : public Book
{
protected:
    string fileFormat;
    int fileSize;

public:
    EBook() : Book(), fileFormat(""), fileSize(0) {}

    EBook(int id, string title, string author, int quantity, string fileFormat, int fileSize)
        : Book(id, title, author, quantity), fileFormat(fileFormat), fileSize(fileSize) {}

    string getFileFormat()
    {
        return fileFormat;
    }

    int getFileSize()
    {
        return fileSize;
    }
    // Phương thức thêm thông tin cuốn sách vào file ebooks.txt
    void addBookToFile()
    {
        ofstream file("ebooks.txt", ios::app);
        if (file.is_open())
        {
            file << "[" << id << "] "
                 << "[" << title << "] "
                 << "[" << author << "] "
                 << "[" << quantity << "] "
                 << "[" << fileFormat << "] "
                 << "[" << fileSize << "]" << endl;
            file.close();
            cout << "EBook added done" << endl;
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    void updateEbooktoFile(int idToUpdate)
    {
        string newTitle;
        string newAuthor;
        int newQuantity;
        string newFileFormat;
        int newFileSize;

        cout << "Enter new title: ";
        cin.ignore();
        getline(cin, newTitle);
        cout << "Enter new author: ";
        getline(cin, newAuthor);
        cout << "Enter new quantity: ";
        cin >> newQuantity;
        cout << "Enter new file format: ";
        cin.ignore();
        getline(cin, newFileFormat);
        cout << "Enter new file size: ";
        cin >> newFileSize;

        vector<string> lines;
        ifstream file("ebooks.txt");
        if (!file.is_open())
        {
            cerr << "Error" << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            int id, quantity;
            string title, author, fileFormat;
            int fileSize;

            char bracket;
            ss >> bracket >> id >> bracket;
            getline(ss, title, ']');
            getline(ss, author, ']');
            ss >> bracket >> quantity >> bracket;
            getline(ss, fileFormat, ']');
            ss >> bracket >> fileSize >> bracket;

            if (id == idToUpdate)
            {
                stringstream updatedLine;
                updatedLine << "[" << id << "] [" << newTitle << "] [" << newAuthor << "] [" << newQuantity << "] [" << newFileFormat << "] [" << newFileSize << "]";
                lines.push_back(updatedLine.str());
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile("ebooks.txt");
        if (!outFile.is_open())
        {
            cerr << "Error!" << endl;
            return;
        }

        for (const auto &line : lines)
        {
            outFile << line << endl;
        }
        outFile.close();

        cout << "EBook with ID " << idToUpdate << " Updated done!" << endl;
    }

    void MinusQuantityEBook(int idToUpdate, string title, string author, int newQuantity, string fileFormat, int fileSize)
    {
        // string newTitle;
        // string newAuthor;
        // int newQuantity;
        // string newFileFormat;
        // int newFileSize;

        // cout << "Enter new title: ";
        // cin.ignore();
        // getline(cin, newTitle);
        // cout << "Enter new author: ";
        // getline(cin, newAuthor);
        // cout << "Enter new quantity: ";
        // cin >> newQuantity;
        // cout << "Enter new file format: ";
        // cin.ignore();
        // getline(cin, newFileFormat);
        // cout << "Enter new file size: ";
        // cin >> newFileSize;

        vector<string> lines;
        ifstream file("ebooks.txt");
        if (!file.is_open())
        {
            cerr << "Error" << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            int id1, quantity1;
            string title1, author1, fileFormat1;
            int fileSize1;

            char bracket;
            ss >> bracket >> id1 >> bracket >> bracket;
            getline(ss, title1, ']');
            ss >> bracket;
            getline(ss, author1, ']');
            ss >> bracket >> quantity1 >> bracket >> bracket;
            getline(ss, fileFormat1, ']');
            ss >> bracket >> fileSize1 >> bracket;

            if (id1 == idToUpdate)
            {
                stringstream updatedLine;
                updatedLine << "[" << idToUpdate << "] [" << title << "] [" << author << "] [" << newQuantity << "] [" << fileFormat << "] [" << fileSize << "]";
                lines.push_back(updatedLine.str());
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile("ebooks.txt");
        if (!outFile.is_open())
        {
            cerr << "Error!" << endl;
            return;
        }

        for (const auto &line : lines)
        {
            outFile << line << endl;
        }
        outFile.close();

        // cout << "EBook with ID " << idToUpdate << " Updated done!" << endl;
    }
};
// Begin Person

class Person
{
private:
    int id;
    string name, email, sex, birthdate,
        address, phoneNumber, role;

public:
    Person(string, string, string, string, string, string, string);
    int getNextAvailableId();
    bool addPerson();
    void setId(int);
    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getSex() const { return sex; }
    string getBirthdate() const { return birthdate; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    string getRole() const { return role; }
};

Person::Person(string name, string email, string sex, string birthday, string address, string phoneNumber, string role)
{
    this->name = name;
    this->email = email;
    this->sex = sex;
    this->birthdate = birthday;
    this->address = address;
    this->phoneNumber = phoneNumber;
    this->role = role;
    this->id = getNextAvailableId();
}

void Person::setId(int x)
{
    this->id = x;
    return;
}

int Person::getNextAvailableId()
{
    ifstream file("people.txt");
    if (file.is_open())
    {
        int lineCount = 0;
        string line;
        while (getline(file, line))
        {
            lineCount++;
        }
        file.close();
        return lineCount + 1; // id là dòng tiếp theo sau khi đã đếm được số dòng
    }
    return 1; // Trả về 1 nếu không mở được file
}

bool Person::addPerson()
{
    ofstream fileout("people.txt", ios::app);
    if (fileout.is_open())
    {
        fileout << '[' << this->id << ']' << " " << '[' << this->name << ']' << " " << '[' << this->email << ']'
                << " " << '[' << this->sex << ']' << " " << '[' << this->birthdate << ']' << " " << '[' << this->address << ']'
                << " " << '[' << this->phoneNumber << ']' << " " << '[' << this->role << ']' << endl;
        fileout.close();
        return true;
    }
    else
    {
        return false;
    }
    fileout.close();
}

class User
{
private:
    int id;
    string email;
    string password;

public:
    bool isLoggedIn;

    User(int _id, const string &_email, const string &_password) : id(_id), email(_email), password(_password), isLoggedIn(false) {}
    string getEmail() const { return email; }
    string getPassword() const { return password; }

    // check email trùng
    bool validateEmail()
    {
        ifstream file("users.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line.find(email) != string::npos)
                {
                    file.close();
                    return false; // email đã tồn tại
                }
            }
            file.close();
        }
        return true; // email hợp lệ
    }

    // Kiểm tra mật khẩu bằng biểu thức,
    //  thể hiện: Biểu thức này đảm bảo rằng mật khẩu chứa ít nhất một chữ số, một chữ cái thường, một chữ cái in hoa, một ký tự đặc biệt và có ít nhất 8 ký tự
    bool validatePassword()
    {
        regex pattern("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&*()_+\\-={}\\[\\]|;:'\"<>,.?/~]).{8,}$");
        return regex_match(password, pattern);
    }

    bool registerUser()
    {
        if (!validateEmail())
        {
            cout << "Error: Email already exists." << endl;
            return false;
        }

        ofstream fileout("users.txt", ios::app);
        if (fileout.is_open())
        {
            fileout << '[' << id << ']' << " [" << email << "] [" << password << "]" << endl;
            fileout.close();
            return true;
        }
        else
        {
            cout << "Error: Unable to open file." << endl;
            return false;
        }
    }

    static int getNextAvailableId()
    {
        ifstream file("users.txt");
        if (file.is_open())
        {
            int lineCount = 0;
            string line;
            while (getline(file, line))
            {
                lineCount++;
            }
            file.close();
            return lineCount + 1; // id là dòng tiếp theo sau khi đã đếm được số dòng
        }
        return 1; // Trả về 1 nếu không mở được file
    }
};
vector<User> dsUsers;
vector<Person> dsPeople;

Person getPerson(const string &emailToFind)
{
    ifstream filein("people.txt");
    if (filein.is_open())
    {
        string line;
        int id;
        string name, email, sex, birthdate, address, phoneNumber, role;
        char bracket;
        while (getline(filein, line))
        {
            stringstream ss(line);
            ss >> bracket >> id >> bracket >> bracket;
            getline(ss, name, ']');
            ss >> bracket;
            getline(ss, email, ']');
            ss >> bracket;
            getline(ss, sex, ']');
            ss >> bracket;
            getline(ss, birthdate, ']');
            ss >> bracket;
            getline(ss, address, ']');
            ss >> bracket;
            getline(ss, phoneNumber, ']');
            ss >> bracket;
            getline(ss, role, ']');
            if (email == emailToFind)
            {
                Person cur(name, email, sex, birthdate, address, phoneNumber, role);
                cur.setId(id);
                filein.close();
                return cur;
            }
        }
        filein.close();
    }
    return Person("", "", "", "", "", "", "");
}

// Begin BorrowInfo
class BorrowInfo
{
private:
    int id, personId, bookId, eBookId;

public:
    BorrowInfo(int, int, int);
    bool addInfo();
    int getNextAvailableId();
    void setId(int);
    void setpersonId(int);
    void setbookId(int);
    void seteBookId(int);
    int getId();
    int getpersonId();
    int getbookId();
    int geteBookId();
};

BorrowInfo::BorrowInfo(int personId, int bookId, int eBookId)
{
    this->personId = personId;
    this->bookId = bookId;
    this->eBookId = eBookId;
}

bool BorrowInfo::addInfo()
{
    ofstream fileout("borrowInfos.txt", ios::app);
    if (fileout.is_open())
    {
        id = getNextAvailableId();
        fileout << '[' << this->id << ']' << " " << '[' << this->personId << ']' << " " << '[' << this->bookId << "]"
                << " " << '[' << this->eBookId << ']' << endl;
        fileout.close();
        return true;
        fileout.close();
    }
    else
        return false;
}

int BorrowInfo::getNextAvailableId()
{
    ifstream file("borrowInfos.txt");
    if (file.is_open())
    {
        int lineCount = 0;
        string line;
        while (getline(file, line))
        {
            lineCount++;
        }
        file.close();
        return lineCount + 1; // id là dòng tiếp theo sau khi đã đếm được số dòng
    }
    return 1; // Trả về 1 nếu không mở được file
}

void BorrowInfo::setId(int id)
{
    this->id = id;
}

void BorrowInfo::setpersonId(int id)
{
    this->id = id;
}

void BorrowInfo::setbookId(int id)
{
    this->id = id;
}

void BorrowInfo::seteBookId(int id)
{
    this->id = id;
}

int BorrowInfo::getId()
{
    return this->id;
}

int BorrowInfo::getpersonId()
{
    return this->personId;
}

int BorrowInfo::getbookId()
{
    return this->bookId;
}

int BorrowInfo::geteBookId()
{
    return this->eBookId;
}

// End BorrowInfo

// Biến toàn cục
vector<int> borrowedBooks;
vector<int> borrowedEBook;
bool loggedIn = false;
Person curPer("", "", "", "", "", "", "");

// Bat dau khai bao cac ham thao tac

void themthongtinmuonsach(int perID)
{
    int bookId, eBookId;
    cout << "Nhap id quyen sach duoc muon: ";
    cin >> bookId;
    cout << "Nhap id quyen sach dien tu duoc muon: ";
    cin >> eBookId;
    BorrowInfo x(perID, bookId, eBookId);
    x.addInfo();

    ifstream filein("books.txt");
    if (filein.is_open())
    {
        string line;
        while (getline(filein, line))
        {
            stringstream ss(line);
            char bracket;
            int id, quantity;
            string author, title;
            ss >> bracket >> id >> bracket >> bracket;
            getline(ss, title, ']');
            ss >> bracket;
            getline(ss, author, ']');
            ss >> bracket;
            ss >> quantity;

            if (id == bookId)
            {
                Book x;
                x.MinusQuantityBook(id, title, author, quantity - 1);
            }
        }
    }
    filein.close();

    ifstream filein2("ebooks.txt");
    if (filein2.is_open())
    {
        string line;
        while (getline(filein2, line))
        {
            stringstream ss(line);
            int id, quantity;
            string title, author, fileFormat;
            int fileSize;
            char bracket;
            ss >> bracket >> id >> bracket >> bracket;
            getline(ss, title, ']');
            ss >> bracket;
            getline(ss, author, ']');
            ss >> bracket >> quantity >> bracket >> bracket;
            getline(ss, fileFormat, ']');
            ss >> bracket >> fileSize >> bracket;
            if (id == eBookId)
            {
                EBook x;
                x.MinusQuantityEBook(id, title, author, quantity - 1, fileFormat, fileSize);
            }
        }
    }
    filein2.close();

    borrowedBooks.push_back(bookId);
    borrowedEBook.push_back(eBookId);
    // chưa trừ số lượng sách trong eBook
}

void ShowAllBorrowedBookEbook()
{
    cout << "Danh sach cac quyen sach da muon la: \n";
    for (int id : borrowedBooks)
    {
        //        cout << getNameBookById(id) << endl;
    }
    cout << "Danh sach cac quyen sach dien tu da muon la: \n";
    for (int id : borrowedEBook)
    {
        //        cout << getNameEBookById(id) << endl;
    }
}

vector<int> extractNumbers(const string &input) // ham tra ve 1 vector id, id trong dau [] o file borrowInfo
{
    vector<int> numbers;
    stringstream ss(input);

    char ch;
    int number;

    // Đọc từng kí tự chuỗi
    while (ss >> ch)
    {
        if (ch == '[')
        {
            // Nếu gặp kí tự '[', đọc số trong dấu '[' ']'
            if (ss >> number)
            {
                numbers.push_back(number);
                // Bỏ qua các kí tự còn lai cho đến khi gặp kí tự ']'
                ss.ignore(numeric_limits<streamsize>::max(), ']');
            }
        }
    }

    return numbers;
}

bool cmpBorrowInfo(BorrowInfo a, BorrowInfo b)
{
    return a.getId() < b.getId();
}

bool cmpBooks(Book a, Book b)
{
    return a.getId() < b.getId();
}

bool cmpEBooks(EBook a, EBook b)
{
    return a.getId() < b.getId();
}

void capnhatthongtinmuonsach()
{
    vector<BorrowInfo> v;
    ifstream filein("borrowInfos.txt");
    if (!filein.is_open())
    {
        cout << "Khong the mo tep borrowInfos.txt";
    }
    else
    {
        string tmp;
        while (getline(filein, tmp))
        {
            int id, perId, bookId, eBookId;
            vector<int> numbers = extractNumbers(tmp);
            id = numbers[0];
            perId = numbers[1];
            bookId = numbers[2];
            eBookId = numbers[3];
            BorrowInfo x(perId, bookId, eBookId);
            x.setId(id);
            v.push_back(x);
        }
        int id, perId, bookId, eBookId;
        cout << "Nhap id muon sach muon sua thong tin: ";
        cin >> id;
        cout << "Nhap personId muon sua: ";
        cin >> perId;
        cout << "Nhap bookId muon sua: ";
        cin >> bookId;
        cout << "Nhap eBookId muon sua: ";
        cin >> eBookId;
        int ok = 0;
        for (auto it = v.begin(); it != v.end(); it++)
        {
            if (it->getId() == id)
            {
                v.erase(it);
                ok = 1;
                break;
            }
        }
        if (ok == 0)
        {
            cout << "Khong tim thay id muon sach muon sua thong tin\n";
        }
        else
        {
            ofstream fileout("borrowInfos.txt", ios::trunc);
            if (fileout.is_open())
            {
                BorrowInfo x(perId, bookId, eBookId);
                x.setId(id);
                v.push_back(x);
                std::sort(v.begin(), v.end(), cmpBorrowInfo);
                for (BorrowInfo i : v)
                {
                    fileout << "[" << i.getId() << "] " << "[" << i.getpersonId() << "] " << "[" << i.getbookId() << "] " << "[" << i.geteBookId() << "]" << endl;
                }
                cout << "Da sua thanh cong\n";
            }
            else
                cout << "Khong the mo tep borrowInfos.txt\n";
            fileout.close();
        }
    }

    filein.close();
}
// Hàm LoadUsers chịu trách nhiệm đọc dữ liệu người dùng từ tệp user.txt và tải nó vào vectơ dsUsers.
void loadUsers()
{
    ifstream file("users.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            char bracket;
            int id;
            string email, password;

            ss >> bracket >> id >> bracket >> bracket;
            getline(ss, email, ']');
            ss >> bracket;
            getline(ss, password, ']');

            dsUsers.emplace_back(id, email, password);
        }
        file.close();
    }
}
// Hàm LoadPeople chịu trách nhiệm đọc dữ liệu người từ tệp people.txt và tải nó vào vectơ dsPeople.
void loadPeople()
{
    ifstream file("people.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            char bracket;
            int id;
            string name, email, sex, birthdate, address, phoneNumber, role;

            ss >> bracket >> id >> bracket >> bracket;
            getline(ss, name, ']');
            ss >> bracket;
            getline(ss, email, ']');
            ss >> bracket;
            getline(ss, sex, ']');
            ss >> bracket;
            getline(ss, birthdate, ']');
            ss >> bracket;
            getline(ss, address, ']');
            ss >> bracket;
            getline(ss, phoneNumber, ']');
            ss >> bracket;
            getline(ss, role, ']');

            Person p(name, email, sex, birthdate, address, phoneNumber, role);
            p.setId(id);
            dsPeople.push_back(p);
        }
        file.close();
    }
}

Person login(bool &check)
{
    string email, password;
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> password;

    for (auto &s : dsUsers)
    {
        if (email == s.getEmail())
        {
            if (password == s.getPassword())
            {
                check = true;
                Person p = getPerson(email);
                if (p.getEmail() != "")
                {
                    cout << "Dang nhap thanh cong !\n";
                    cout << "Welcome " << p.getName() << " !\n";
                    return p;
                }
            }
        }
    }
    check = false;
    cout << "Sai thong tin dang nhap !\n";
    return Person("", "", "", "", "", "", "");
}

void Signup()
{
    string userName, password;
    cout << "Nhap userName: \n";
    cin >> userName;
    cout << "Nhap password: \n";
    cin >> password;
    User x(0, userName, password);
    int id = x.getNextAvailableId();
    User a(id, userName, password);
    bool check = a.registerUser();
    if (check)
    {
        string name, email, sex, birthday, address, phoneNumber, role;
        cout << "Dang ky tai khoan truy cap thanh cong, vui long nhap thong tin ca nhan\n";
        cout << "Nhap Ho va ten: \n";
        scanf("\n");
        getline(cin, name);
        cout << "Nhap email: \n";
        cin >> email;
        cout << "Nhap gioi tinh: \n";
        cin >> sex;
        cout << "Nhap ngay thang nam sinh: \n";
        cin >> birthday;
        cout << "Nhap dia chi noi o: \n";
        scanf("\n");
        getline(cin, address);
        cout << "Nhap so dien thoai: \n";
        cin >> phoneNumber;
        role = "User";
        Person a(name, email, sex, birthday, address, phoneNumber, role);
        bool check = a.addPerson();
        if (check)
        {
            cout << "Them thong tin thanh cong\n";
        }
        else
            cout << "Khong the mo tep people.txt de them thong tin\n";
    }
    return;
}

Person getPerson(string emailCheck)
{
    ifstream filein("people.txt");
    if (filein.is_open())
    {
        string line;
        int id;
        string name, email, sex, birthdate,
            address, phoneNumber, role;
        char bracket;
        while (getline(filein, line))
        {
            stringstream ss(line);
            ss >> bracket >> id >> bracket >> bracket;
            getline(ss, name, ']');
            ss >> bracket;
            getline(ss, email, ']');
            ss >> bracket;
            getline(ss, sex, ']');
            ss >> bracket;
            getline(ss, birthdate, ']');
            ss >> bracket;
            getline(ss, address, ']');
            ss >> bracket;
            getline(ss, phoneNumber, ']');
            ss >> bracket;
            getline(ss, role, ']');
            if (email == emailCheck)
            {
                Person cur(name, email, sex, birthdate, address, phoneNumber, role);
                cur.setId(id);
                return cur;
            }
        }
    }

    filein.close();
}

string GetRoleByEmail(const string &email)
{
    ifstream peopleFile("people.txt");
    if (!peopleFile.is_open())
    {
        cout << "Khong the mo tep people.txt\n";
        return ""; // Trả về chuỗi rỗng nếu không mở được file
    }

    string tmp;
    while (getline(peopleFile, tmp))
    {
        if (tmp.find(email) != string::npos)
        {
            // Tìm thấy email trong file people.txt
            stringstream ss(tmp);
            string role;
            ss >> tmp >> tmp;
            // Đọc Role
            ss >> role;
            // Xóa kí tự [ ở đầu và ] ở cuối
            role = role.substr(1, role.size() - 2);
            peopleFile.close();
            return role;
        }
    }

    cout << "Khong tim thay thong tin nguoi dung.\n";
    peopleFile.close();
    return ""; // Trả về chuỗi rỗng nếu không tìm được email
}

void showBooks()
{
    Book book;
    vector<Book> ans = book.getBooks();
    std::sort(ans.begin(), ans.end(), cmpBooks);
    for (Book tmpBook : ans)
    {
        cout << "ID: " << tmpBook.getId() << " - " << "Title: " << tmpBook.getTitle() << " - " << "Author: " << tmpBook.getAuthor() << " - " << "Quantity: " << tmpBook.getQuantity() << endl;
    }
    return;
}

void showEBooks()
{
    vector<EBook> ans;
    ifstream filein("ebooks.txt");
    if (filein.is_open())
    {
        string line;
        while (getline(filein, line))
        {
            stringstream ss(line);
            char c;
            int id, quantity, fileSize;
            string title, author, fileFormat;
            ss >> c >> id >> c >> c;
            getline(ss, title, ']');
            ss >> c;
            getline(ss, author, ']');
            ss >> c;
            ss >> quantity >> c >> c;
            getline(ss, fileFormat, ']');
            ss >> c;
            ss >> fileSize;
            EBook ebook(id, title, author, quantity, fileFormat, fileSize);
            ans.push_back(ebook);
        }
        std::sort(ans.begin(), ans.end(), cmpEBooks);
        for (EBook eb : ans)
        {
            cout << "ID: " << eb.getId() << " - " << "Title: " << eb.getTitle() << " - " << "Author: " << eb.getAuthor() << " - " << "Quantity: " << eb.getQuantity() << " - " << "FileFormat: " << eb.getFileFormat() << " - " << "FileSize: "
                 << eb.getFileSize() << endl;
        }
        filein.close();
    }
    else
    {
        cout << "Khong the mo tep ebooks.txt\n";
    }
    return;
}
// Ket thuc khai bao cac ham thao tac

int main()
{
    loadUsers();
    loadPeople();

    char option;
    while (true)
    {
        cout << "dang nhap - bam \"a\"\n";
        cout << "dang ki - bam \"b\"\n";
        cout << "thoat chuong trinh - bam \"r\"\n";
        cin >> option;
        if (option == 'r')
            return 0;
        if (option == 'b')
        {
            Signup();
        }
        if (option == 'a')
        {
            bool check;
            Person curPer = login(check);
            if (check)
            {
                cout << "Vai tro cua ban la: " << curPer.getRole() << endl;
                bool loggedIn = true;
                while (loggedIn)
                {

                    cout << "CHON CAC CHUC NANG:\n";
                    cout << "bam \"c\" de them sach - quyen cua admin\n";
                    cout << "bam \"d\" de sua thong tin sach - quyen cua admin\n";
                    cout << "bam \"e\" de xoa sach - quyen cua admin\n";
                    cout << "bam \"f\" de muon sach\n";
                    cout << "bam \"g\" de tra sach\n";
                    cout << "bam \"h\" de hien thi tat ca sach\n";
                    cout << "bam \"i\" de lay thong tin cuon sach trong Books\n";
                    cout << "bam \"j\" de hien thi tat ca sach trong Ebooks\n";
                    cout << "bam \"k\" de lay thong tin cuon sach trong Ebooks\n";
                    cout << "bam \"m\" de hien thi tat ca sach ban da muon\n";
                    cout << "bam \"n\" de hien thi tat ca sach cua mot nguoi - quyen cua admin\n";
                    cout << "bam \"o\" de chinh sua thong tin ca nhan cua ban\n";
                    cout << "bam \"p\" de chinh sua thong tin ca nhan cua mot nguoi - quyen cua admin\n";
                    cout << "bam \"q\" de dang xuat\n";
                    cout << "bam \"r\" de thoat chuong trinh\n";
                    cout << endl;

                    cin >> option;
                    if (option == 'r')
                        return 0; // Thoát chương trình

                    if (option == 'c')
                    {
                        if (curPer.getRole() == "Admin")
                        {
                            Book book;
                            book.addBook();
                        }
                        else
                        {
                            cout << "Ban khong co quyen thuc hien chuc nang nay!\n";
                        }
                    }
                    if (option == 'e')
                    {
                        if (curPer.getRole() == "Admin")
                        {
                            int idToDelete;
                            cout << "Enter ID want to delete: ";
                            cin >> idToDelete;
                            Book book;
                            // Xác nhận trước khi xóa
                            cout << "Are you sure you want to delete this book? (Y/N): ";
                            char confirm;
                            cin >> confirm;
                            if (confirm == 'Y' || confirm == 'y')
                            {
                                book.deleteBook(idToDelete);
                                cout << "Book deleted successfully!" << endl;
                            }
                            else
                            {
                                cout << "Deletion canceled." << endl;
                            }
                        }
                        else
                        {
                            cout << "Ban khong co quyen thuc hien chuc nang nay!\n";
                        }
                    }
                    if (option == 'd')
                    {
                        // UpdateBook
                        if (curPer.getRole() == "Admin")
                        {
                            int idToUpdate;
                            cout << "Enter ID want to update: ";
                            cin >> idToUpdate;
                            Book book;
                            book.updateBook(idToUpdate);
                        }
                        else
                        {
                            cout << "Ban khong co quyen thuc hien chuc nang nay!\n";
                        }
                        // updateEbook
                        // if (curPer.getRole() == "Admin")
                        // {
                        //     int idToUpdate;
                        //     cout << "Enter ID want to update: ";
                        //     cin >> idToUpdate;
                        //     Book book;
                        //     book.updateBook(idToUpdate);
                        // }
                        // else
                        // {
                        //     cout << "Ban khong co quyen thuc hien chuc nang nay!\n";
                        // }

                        // if (curPer.getRole() == "Admin")
                        // {
                        //     int idToUpdate;
                        //     cout << "Enter ID want to update: ";
                        //     cin >> idToUpdate;
                        //     EBook ebook;
                        //     ebook.updateEbooktoFile(idToUpdate);
                        // }
                        // else
                        // {
                        //     cout << "Ban khong co quyen thuc hien chuc nang nay!\n";
                        // }
                    }
                    if (option == 'i')
                    {
                        // hien thi thong tin sach theo id nguoi dung nhap
                        int id;
                        cout << "Nhap id cuon sach ban muon xem thong tin: ";
                        cin >> id;
                        Book book;
                        vector<Book> ans = book.getBooks();
                        for (Book tmpBook : ans)
                        {
                            if (tmpBook.getId() == id)
                            {
                                cout << "ID: " << tmpBook.getId() << " - " << "Title: " << tmpBook.getTitle() << " - " << "Author: " << tmpBook.getAuthor() << " - " << "Quantity: " << tmpBook.getQuantity() << endl;
                            }
                        }
                    }
                    if (option == 'k')
                    {

                        // hien thi thong tin ebook theo id
                        int id;
                        cout << "Nhap id cuon sach dien tu ban muon xem thong tin: ";
                        cin >> id;
                        vector<EBook> ans;
                        ifstream filein("ebooks.txt");
                        if (filein.is_open())
                        {
                            string line;
                            while (getline(filein, line))
                            {
                                stringstream ss(line);
                                char c;
                                int id, quantity, fileSize;
                                string title, author, fileFormat;
                                ss >> c >> id >> c >> c;
                                getline(ss, title, ']');
                                ss >> c;
                                getline(ss, author, ']');
                                ss >> c;
                                ss >> quantity >> c >> c;
                                getline(ss, fileFormat, ']');
                                ss >> c;
                                ss >> fileSize;
                                EBook ebook(id, title, author, quantity, fileFormat, fileSize);
                                ans.push_back(ebook);
                            }
                            for (EBook eb : ans)
                            {
                                if (eb.getId() == id)
                                {
                                    cout << "ID: " << eb.getId() << " - " << "Title: " << eb.getTitle() << " - " << "Author: " << eb.getAuthor() << " - " << "Quantity: " << eb.getQuantity() << " - " << "FileFormat: " << eb.getFileFormat() << " - " << "FileSize: "
                                         << eb.getFileSize() << endl;
                                }
                            }
                            filein.close();
                        }
                        else
                        {
                            cout << "Khong the mo tep ebooks.txt\n";
                        }
                    }
                    if (option == 'h')
                    {
                        showBooks();
                    }
                    if (option == 'j')
                    {
                        showEBooks();
                    }
                    if (option == 'f')
                    {
                        themthongtinmuonsach(curPer.getId());
                        // themthongtinmuonsach();
                    }
                    if (option == 'g')
                    {
                        capnhatthongtinmuonsach();
                    }
                    if (option == 'm')
                    {
                        // hien thi tat ca sach ban da muon
                        vector<BorrowInfo> v;
                        ifstream filein("borrowInfos.txt");
                        if (!filein.is_open())
                        {
                            cout << "Khong the mo tep borrowInfos.txt";
                        }
                        else
                        {
                            string tmp;
                            while (getline(filein, tmp))
                            {
                                int id, perId, bookId, eBookId;
                                vector<int> numbers = extractNumbers(tmp);
                                id = numbers[0];
                                perId = numbers[1];
                                bookId = numbers[2];
                                eBookId = numbers[3];
                                BorrowInfo x(perId, bookId, eBookId);
                                x.setId(id);
                                v.push_back(x);
                            }
                            std::sort(v.begin(), v.end(), cmpBorrowInfo);
                            for (BorrowInfo i : v)
                            {
                                if (i.getpersonId() == curPer.getId())
                                {
                                    cout << "ID: " << i.getId() << " - " << "PersonId: " << i.getpersonId() << " - " << "BookId: " << i.getbookId() << " - " << "EBookId: " << i.geteBookId() << endl;
                                }
                            }
                            filein.close();
                        }
                        
                    }
                    if (option == 'n')
                    {
                        if (curPer.getRole() == "Admin")
                        {
                            int id;
                            cout << "Nhap id nguoi muon xem thong tin: ";
                            cin >> id;
                            vector<BorrowInfo> v;
                            ifstream filein("borrowInfos.txt");
                            if (!filein.is_open())
                            {
                                cout << "Khong the mo tep borrowInfos.txt";
                            }
                            else
                            {
                                string tmp;
                                while (getline(filein, tmp))
                                {
                                    int id, perId, bookId, eBookId;
                                    vector<int> numbers = extractNumbers(tmp);
                                    id = numbers[0];
                                    perId = numbers[1];
                                    bookId = numbers[2];
                                    eBookId = numbers[3];
                                    BorrowInfo x(perId, bookId, eBookId);
                                    x.setId(id);
                                    v.push_back(x);
                                }
                                std::sort(v.begin(), v.end(), cmpBorrowInfo);
                                for (BorrowInfo i : v)
                                {
                                    if (i.getpersonId() == id)
                                    {
                                        cout << "ID: " << i.getId() << " - " << "PersonId: " << i.getpersonId() << " - " << "BookId: " << i.getbookId() << " - " << "EBookId: " << i.geteBookId() << endl;
                                    }
                                }
                                filein.close();
                            }
                        }
                        else
                        {
                            cout << "Ban khong co quyen thuc hien chuc nang nay!\n";
                        }
                    }
                    if (option == 'o')
                    {
                        // chinh sua thong tin ca nhan cua ban
                        int id;
                        cout << "Nhap id cua ban: ";
                        cin >> id;
                        string name, email,sex, birthdate, address, phoneNumber, role;
                        cout << "Nhap ten moi: ";
                        cin >> name;
                        cout << "Nhap email moi: ";
                        cin >> email;
                        cout << "Nhap gioi tinh moi: ";
                        cin>>sex;
                        cout << "Nhap ngay thang nam sinh moi: ";
                        cin>>birthdate;
                        cout << "Nhap dia chi moi: ";
                        cin >> address;
                        cout << "Nhap so dien thoai moi: ";
                        cin >> phoneNumber;
                        Person x(name, email,sex,birthdate, address, phoneNumber, role);
                        x.setId(id);
                        x.addPerson();
                    }
                    if (option == 'p')
                    {
                        // chinh sua thong tin ca nhan cua mot nguoi
                        if (curPer.getRole() == "Admin")
                        {
                            int id;
                            cout << "Nhap id nguoi muon chinh sua: ";
                            cin >> id;
                            string name, email;
                            cout << "Nhap ten moi: ";
                            cin >> name;
                            cout << "Nhap email moi: ";
                            cin >> email;
                            Person x(name, email, "Nam", "01/01/2000", "Ha Noi", "0123456789", "User");
                            x.setId(id);
                            x.addPerson();
                        }
                        else
                        {
                            cout << "Ban khong co quyen thuc hien chuc nang nay!\n";
                        }
                    }
                    if (option == 'q')
                    {
                        loggedIn = false;
                    }

                    // Thực hiện các chức năng khác tương tự
                }
                borrowedBooks.clear();
                borrowedEBook.clear();
            }
            else
            {
                cout << "Dang nhap that bai\n";
            }
        }
    }
    return 0;
}
