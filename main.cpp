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
            return lineCount + 1; // id là dòng tiếp theo sau khi đã đếm được số dòng
        }
        return 1; // Trả về 1 nếu không mở được file
    }

    void addBook()
    {
        id = getNextAvailableId(); // Gán id là id bé nhất chưa xuất hiện
        cout << "Enter title: ";
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
        id = getNextAvailableId(); // Gán id là dòng tiếp theo trong file
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

        // Kiểm tra và ghi vào file
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
class User
{
private:
    int id;
    string email;
    string password;

public:
    User(int _id, const string &_email, const string &_password) : id(_id), email(_email), password(_password) {}

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
                    return false; // Email đã tồn tại
                }
            }
            file.close();
        }
        return true; // Email hợp lệ
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

// End Person

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

// Bat dau khai bao cac ham thao tac

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
    x.addInfo();
}

vector<int> extractNumbers(const string &input) // ham tra ve 1 vector id, id trong dau [] o file borrowInfo
{
    vector<int> numbers;
    stringstream ss(input);

    char ch;
    int number;

    // �?c t?ng k� t? t? chu?i
    while (ss >> ch)
    {
        if (ch == '[')
        {
            // N?u g?p k� t? '[', d?c s? trong d?u '[' ']'
            if (ss >> number)
            {
                numbers.push_back(number);
                // B? qua c�c k� t? c�n l?i cho d?n khi g?p k� t? ']'
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
bool loggedIn = false;

void Login()
{
    string userName, password;
    cout << "Nhap Email: \n";
    cin >> userName;
    cout << "Nhap password: \n";
    cin >> password;
    ifstream filein("users.txt");
    if (!filein.is_open())
    {
        cout << "Khong the mo tep users.txt\n";
    }
    else
    {
        string tmp;
        while (getline(filein, tmp))
        {
            if (tmp.find(userName) != string::npos && tmp.find(password) != string::npos)
            {
                cout << "Dang nhap thanh cong\n";
                loggedIn = true; // Đánh dấu đã đăng nhập thành công
                filein.close();  // Đóng file users.txt trước khi tiếp tục
                ifstream peopleFile("people.txt");
                if (!peopleFile.is_open())
                {
                    cout << "Khong the mo tep people.txt\n";
                }
                else
                {
                    string name;
                    while (getline(peopleFile, tmp))
                    {
                        if (tmp.find(userName) != string::npos)
                        {
                            // Tìm thấy email trong file people.txt
                            // Sử dụng stringstream để lấy tên từ dòng chứa email
                            stringstream ss(tmp);
                            string bracket;
                            ss >> bracket;          // Bỏ qua ký tự '['
                            getline(ss, name, ']'); // Lấy tên đến khi gặp ký tự ']'

                            name = name.substr(2); // Bỏ đi dấu [ ở đầu tên
                            cout << "Welcome " << name << "!\n";
                            break; // Kết thúc vòng lặp sau khi tìm thấy tên
                        }
                    }
                    peopleFile.close();
                }
                return;
            }
        }
        cout << "Dang nhap that bai\n";
    }
    filein.close();
}

// Ket thuc khai bao cac ham thao tac

// Start bien toan cuc
char option;
bool active;

// End bien toan cuc
int main()
{
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
            Login();
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
                cout << "bam \"q\" de dang suat\n";
                cout << "bam \"r\" de thoat chuong trinh\n";
                cout << endl;
                cin >> option;
                if (option == 'r')
                    return 0; // Thoát chương trình
                if (option == 'q')
                { // Đăng xuất
                    loggedIn = false;
                    break;
                }
                // Thực thi các chức năng khác
            }
        }
    }

    //    Book book;
    // book.addBook(); // Thêm một sách vào file books.txt
    // // book.getBooks(); // Hiển thị thông tin sách trong file books.txt

    // EBook ebook;
    // ebook.addBook(); // Thêm một Ebook vào file books.txt
    //    int idToUpdate;
    //    cout << "Enter ID want to update: ";
    //    cin >> idToUpdate;
    //    book.updateBook(idToUpdate); // Cập nhật thông tin của sách

    //	themthongtinmuonsach(); --> done
    //    capnhatthongtinmuonsach();--> done

    //    int id = User::getNextAvailableId();
    //    string email = "example@example.com";
    //    string password = "PTITd22@";
    //    User user(id, email, password);
    //    user.registerUser();
    //    cout << "Register Successfully" << endl;

    return 0;
    //    int idToUpdate;
    //    cout << "Enter ID want to update: ";
    //    cin >> idToUpdate;
    //    book.updateBook(idToUpdate); // Cập nhật thông tin của sách

    //	themthongtinmuonsach(); --> done
}