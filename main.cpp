
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
            return lineCount + 1; // id là dòng ti?p theo sau khi dã d?m du?c s? dòng
        }
        return 1; // Tr? v? 1 n?u không m? du?c file
    }

    void addBook()
    {
        id = getNextAvailableId(); // Gán id là id bé nh?t chua xu?t hi?n
        cout << "Enter title: ";
        getline(cin, title);
        cout << "Enter author: ";
        getline(cin, author);
        cout << "Enter quantity: ";
        cin >> quantity;

        // Ki?m tra và ghi vào file
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

    void getBooks()
    {
        ifstream file("books.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file.\n";
        }
    }
    void updateBook(int idToUpdate)
    {
        string newTitle = "New Title";
        string newAuthor = "New Author";
        int newQuantity = 10;

        vector<string> lines;
        ifstream file("books.txt");
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
            string title, author;

            char bracket;
            ss >> bracket >> id >> bracket;
            getline(ss, title, ']');
            getline(ss, author, ']');
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
};

class EBook : public Book
{
protected:
    string fileFormat;
    int fileSize;

public:
    EBook() : Book(), fileFormat(""), fileSize(0) {}

    EBook(string title, string author, int quantity, string fileFormat, int fileSize)
        : Book(id, title, author, quantity), fileFormat(fileFormat), fileSize(fileSize) {}

    void addBook()
    {
        id = getNextAvailableId(); // Gán id là dòng ti?p theo trong file
        cout << "Enter title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author: ";
        getline(cin, author);
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter file format: ";
        cin.ignore();
        getline(cin, fileFormat);
        cout << "Enter file size: ";
        cin >> fileSize;

        // Ki?m tra và ghi vào file
        ofstream file("books.txt", ios::app);
        if (file.is_open())
        {
            file << "[" << id << "] "
                 << "[" << title << "] "
                 << "[" << author << "] "
                 << "[" << quantity << "] "
                 << "[" << fileFormat << "] "
                 << "[" << fileSize << "] " << endl;
            file.close();
            cout << "Ebook add done!\n";
        }
        else
        {
            cout << "Error!\n";
        }
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
    Person(int id, string name, string email, string sex, string birthdate, string address, string phoneNumber, string role)
        : id(id), name(name), email(email), sex(sex), birthdate(birthdate), address(address), phoneNumber(phoneNumber), role(role) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getSex() const { return sex; }
    string getBirthdate() const { return birthdate; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    string getRole() const { return role; }
};

// End Person

// Begin User
class User
{
private:
    int id;
    string email;
    string password;
    bool isLoggedIn;

public:
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
                size_t found = line.find(email);
                if (found != string::npos)
                {
                    file.close();
                    return false; // Email dã t?n t?i
                }
            }
            file.close();
        }
        return true; // Email h?p l?
    }

    // Ki?m tra m?t kh?u b?ng bi?u th?c,
    //  th? hi?n: Bi?u th?c này d?m b?o r?ng m?t kh?u ch?a ít nh?t m?t ch? s?, m?t ch? cái thu?ng, m?t ch? cái in hoa, m?t ký t? d?c bi?t và có ít nh?t 8 ký t?
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
            return lineCount + 1; // id là dòng ti?p theo sau khi dã d?m du?c s? dòng
        }
        return 1; // Tr? v? 1 n?u không m? du?c file
    }
};
// End User
class Users
{
private:
    vector<User> users;

    bool checkUser(const User &user)
    {
        for (const auto &u : users)
        {
            if (u.getEmail() == user.getEmail() && u.getPassword() == user.getPassword())
            {
                return true;
            }
        }
        return false;
    }

public:
    Users()
    {
        ifstream ifs("users.txt");
        if (ifs.is_open())
        {
            string line;
            while (getline(ifs, line))
            {
                stringstream ss(line);
                char s;
                int id;
                string email, password;
                ss >> s >> id >> s >> s;
                getline(ss, email, ']');
                ss >> s;
                getline(ss, password, ']');
                users.push_back(User(id, email, password));
            }
            ifs.close();
        }
    }

    Person login(User &login, const string &email, const string &password)
    {
        if (!checkUser(login))
        {
            cout << "Error !" << endl;
            return Person(0, "", "", "", "", "", "", "");
        }

        ifstream ifs("people.txt");
        if (!ifs.is_open())
        {
            cout << "Can not open file people.txt." << endl;
            return Person(0, "", "", "", "", "", "", "");
        }

        string line;
        while (getline(ifs, line))
        {
            stringstream ss(line);
            char s;
            int id;
            string emailPerson, name, sex, birthdate, address, phoneNumber, role;
            ss >> s >> id >> s;
            getline(ss, name, ']');
            ss >> s;
            getline(ss, emailPerson, ']');
            ss >> s;
            getline(ss, sex, ']');
            ss >> s;
            getline(ss, birthdate, ']');
            ss >> s;
            getline(ss, address, ']');
            ss >> s;
            getline(ss, phoneNumber, ']');
            ss >> s;
            getline(ss, role, ']');
            if (emailPerson == email)
            {
                ifs.close();
                cout << "Login successfully!" << endl;
                return Person(id, name, emailPerson, sex, birthdate, address, phoneNumber, role);
            }
        }
        ifs.close();
        cout << "Invalid!" << endl;
        return Person(0, "", "", "", "", "", "", "");
    }
    void logout()
    {

        cout << "Logout successful." << endl;
    }
};
// Begin BorrowInfo
class BorrowInfo
{
private:
    int id, personId, bookId, eBookId;

public:
    BorrowInfo(int, int, int);
    void addInfo();
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

void BorrowInfo::addInfo()
{
    ofstream fileout("borrowInfos.txt", ios::app);
    fileout << '[' << this->id << ']' << " " << '[' << this->personId << ']' << " " << '[' << this->bookId << "]"
            << " " << '[' << this->eBookId << ']' << endl;
    fileout.close();
}

void themthongtinmuonsach()
{
    int id, persionId, bookId, eBookId;
    cout << "Nhap id nguoi muon: ";
    cin >> persionId;
    cout << "Nhap id quyen sach duoc muon: ";
    cin >> bookId;
    cout << "Nhap id quyen sach dien tu duoc muon: ";
    cin >> eBookId;
    BorrowInfo x(persionId, bookId, eBookId);
    x.setId(x.getNextAvailableId());
    x.addInfo();
}

vector<int> extractNumbers(const string &input) // ham tra ve 1 vector id, id trong dau [] o file borrowInfo
{
    vector<int> numbers;
    stringstream ss(input);

    char ch;
    int number;

    // ??c t?ng k? t? t? chu?i
    while (ss >> ch)
    {
        if (ch == '[')
        {
            // N?u g?p k? t? '[', d?c s? trong d?u '[' ']'
            if (ss >> number)
            {
                numbers.push_back(number);
                // B? qua c?c k? t? c?n l?i cho d?n khi g?p k? t? ']'
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
                sort(v.begin(), v.end(), cmpBorrowInfo);
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

// Ket thuc khai bao cac ham thao tac
int main()
{
    Book book;
    book.addBook(); // Thêm m?t sách vào file books.txt
    // book.getBooks(); // Hi?n th? thông tin sách trong file books.txt

    EBook ebook;
    ebook.addBook(); // Thêm m?t Ebook vào file books.txt
    int idToUpdate;
    cout << "Enter ID want to update: ";
    cin >> idToUpdate;
    book.updateBook(idToUpdate); // C?p nh?t thông tin c?a sách

    // themthongtinmuonsach();
    // -- > done

    int id = User::getNextAvailableId();
    string email = "example@example.com";
    string password = "PTITd22@";
    User user(id, email, password);
    user.registerUser();
    cout << "Register Successfully" << endl;

    // capnhatthongtinmuonsach();
    // -- > done

    int id = User::getNextAvailableId();
    string email = "example@example.com";
    string password = "PTITd22@";
    User user(id, email, password);
    user.registerUser();
    cout << "Register Successfully" << endl;

    int idToUpdate;
    cout << "Enter ID want to update: ";
    cin >> idToUpdate;
    book.updateBook(idToUpdate); // C?p nh?t thông tin c?a sách

    // themthongtinmuonsach();
    // -- > done

    //  T?o m?t d?i tu?ng User
    User user1(1, "john.smith@gmail.com", "pass1234");
    User user2(2, "jane.doe@gmail.com", "abcD1234");
    User user3(3, "alice.johnson@gmail.com", "MyP@ssw0rd");
    User user4(4, "example@example.com", "PTITd22@");

    // Ki?m tra thông tin dang nh?p và tr? v? Person v?i email tuong ?ng.

    Users users;
    string email, password;
    cout << "Nhap email: ";
    cin >> email;
    cout << "Nhap mat khau: ";
    cin >> password;

    User loginUser(0, email, password);
    Person loggedInPerson = users.login(loginUser, email, password);

    if (loggedInPerson.getId() != 0)
    {
        cout << "Thong tin cua ban:" << endl;
        cout << "ID: " << loggedInPerson.getId() << endl;
        cout << "Ten: " << loggedInPerson.getName() << endl;
        cout << "Email: " << loggedInPerson.getEmail() << endl;
        cout << "Gioi tinh: " << loggedInPerson.getSex() << endl;
        cout << "Ngay sinh: " << loggedInPerson.getBirthdate() << endl;
        cout << "Dia chi: " << loggedInPerson.getAddress() << endl;
        cout << "So dien thoai: " << loggedInPerson.getPhoneNumber() << endl;
        cout << "Vai tro: " << loggedInPerson.getRole() << endl;
    }
    // Ðang xu?t
    users.logout();
    return 0;
}
