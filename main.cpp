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
    Book() {}

    Book(int _id, string _title, string _author, int _quantity)
    {
        id = _id;
        title = _title;
        author = _author;
        quantity = _quantity;
    }

    void addBook()
    {
        ofstream file("books.txt", ios::app);
        file << id << " " << title << " " << author << " " << quantity << endl;
        file.close();
    }

    static vector<Book> getBooks()
    {
        vector<Book> books;
        ifstream file("books.txt");
        int id, quantity;
        string title, author;
        while (file >> id >> title >> author >> quantity)
        {
            books.push_back(Book(id, title, author, quantity));
        }
        file.close();
        return books;
    }

    static void updateBook(int _id, string _title, string _author, int _quantity)
    {
        vector<Book> books = getBooks();
        for (auto &book : books)
        {
            if (book.id == _id)
            {
                book.title = _title;
                book.author = _author;
                book.quantity = _quantity;
                break;
            }
        }
        ofstream file("books.txt");
        for (const auto &book : books)
        {
            file << book.id << " " << book.title << " " << book.author << " " << book.quantity << endl;
        }
        file.close();
    }

    static void deleteBook(int _id)
    {
        vector<Book> books = getBooks();
        for (auto it = books.begin(); it != books.end(); ++it)
        {
            if (it->id == _id)
            {
                books.erase(it);
                break;
            }
        }
        ofstream file("books.txt");
        for (const auto &book : books)
        {
            file << book.id << " " << book.title << " " << book.author << " " << book.quantity << endl;
        }
        file.close();
    }
};

class EBook : public Book
{
private:
    string fileFormat;
    int fileSize;

public:
    EBook() {}

    EBook(int _id, string _title, string _author, int _quantity, string _fileFormat, int _fileSize)
        : Book(_id, _title, _author, _quantity), fileFormat(_fileFormat), fileSize(_fileSize) {}

    void addBook()
    {
        ofstream file("ebooks.txt", ios::app);
        file << id << " " << title << " " << author << " " << quantity << " " << fileFormat << " " << fileSize << endl;
        file.close();
    }

    static vector<EBook> getEBooks()
    {
        vector<EBook> ebooks;
        ifstream file("ebooks.txt");
        int id, quantity, fileSize;
        string title, author, fileFormat;
        while (file >> id >> title >> author >> quantity >> fileFormat >> fileSize)
        {
            ebooks.push_back(EBook(id, title, author, quantity, fileFormat, fileSize));
        }
        file.close();
        return ebooks;
    }
};

class User
{
protected:
    int id;
    string email;
    string password;

public:
    User() {}

    User(int _id, string _email, string _password) : id(_id), email(_email), password(_password) {}

    void registerUser()
    {

        ofstream file("users.txt", ios::app);
        file << id << " " << email << " " << password << endl;
        file.close();
    }

    static vector<User> getUsers()
    {
        vector<User> users;
        ifstream file("users.txt");
        int id;
        string email, password;
        while (file >> id >> email >> password)
        {
            users.push_back(User(id, email, password));
        }
        file.close();
        return users;
    }

    static Person login(const string &_email, const string &_password)
    {
        vector<User> users = getUsers();
        for (const auto &user : users)
        {
            if (user.email == _email && user.password == _password)
            {
                // Fetch corresponding person details from another source or database
                // Here, just a placeholder person is returned
                return Person(user.id, , user.email, , , , , );
            }
        }
        return Person();
    }

    static void logout()
    {
    }
    class Person
{
private:
    int id;
    string name;
    string email;
    string sex;
    string birthdate;
    string address;
    string phone;
    string role;

public:
    Person() {}
    Person(string name, string email, string sex, string birthdate, string address, string phone, string role)
    {
        this->name = name;
        this->email = email;
        this->sex = sex;
        this->birthdate = birthdate;
        this->address = address;
        this->phone = phone;
        this->role = role;
    }
    void setId(int id)
    {
        this->id = id;
    }
    int getId()
    {
        return id;
    }
    void setName(string name)
    {
        this->name = name;
    }
    string getName()
    {
        return name;
    }

    void setEmail(string email)
    {
        this->email = email;
    }
    string getEmail()
    {
        return email;
    }
    void setSex(string sex)
    {
        this->sex = sex;
    }
    string getSex()
    {
        return sex;
    }
    void setBirthdate(string birtdate)
    {
        this->birthdate = birthdate;
    }
    string getBirthdate()
    {
        return birthdate;
    }
    void setAddress(string address)
    {
        this->address = address;
    }
    string getAddress()
    {
        return address;
    }
    void setPhone(string phone)
    {
        this->phone = phone;
    }
    string getPhone()
    {
        return phone;
    }
    void setRole(string role)
    {
        this->role = role;
    }
    string getRole()
    {
        return role;
    }
    void addInfo(const string &data) {
        // this function is not needed in this context
    }
   bool isValidId(const std::string& id) {
    // Thực hiện kiểm tra tính hợp lệ của ID tại đây
    // Ví dụ:
    // Kiểm tra xem ID có phải là một chuỗi hợp lệ không
    // Sử dụng regex hoặc các tiêu chí khác để kiểm tra tính hợp lệ của ID
    // Trả về true nếu ID hợp lệ, ngược lại trả về false
    return true;
}

// Hàm cập nhật thông tin vào file borrowInfos.txt
 static vector<Person> getPerson() {
        vector<Person> persons;
        fstream fs("people.txt", ios::in);
        string line;

        while (getline(fs, line)) {
            Person x;
            istringstream iss(line);
            string segment;
            vector<string> segments;

            while (getline(iss, segment, ']')) {
                size_t startPos = segment.find('[');
                if (startPos != string::npos) {
                    segments.push_back(segment.substr(startPos + 1));
                }
            }

            if (segments.size() >= 8) {  // Kiểm tra đủ các phần tử
                x.id = stoi(segments[0]);
                x.name = segments[1];
                x.email = segments[2];
                x.sex = segments[3];
                x.birthdate = segments[4];
                x.address = segments[5];
                x.phone = segments[6];
                x.role = segments[7];
                persons.push_back(x);
            }
        }
        fs.close();
        return persons;
    }

    static void updatePerson(int _id, const string &_name, const string &_email, const string &_sex, const string &_birthday, const string &_address, const string &_phone) {
        vector<Person> persons = getPerson();
        bool found = false;

        for (auto &person : persons) {
            if (person.id == _id) {
                found = true;
                person.name = _name;
                person.email = _email;
                person.sex = _sex;
                person.birthdate = _birthday;
                person.address = _address;
                person.phone = _phone;
                // Không thay đổi role
                break;
            }
        }

        if (!found) {
            cout << "Không có id người dùng" << endl;
            return;
        }

        fstream fs("people.txt", ios::out | ios::trunc);
        if (!fs.is_open()) {
            cout << "Không thể mở file để ghi dữ liệu." << endl;
            return;
        }

        for (const auto &person : persons) {
            fs << "[" << person.id << "] [" << person.name << "] [" << person.email << "] [" << person.sex << "] [" << person.birthdate << "] [" << person.address << "] [" << person.phone << "] [" << person.role << "]" << endl;
        }
        fs.close();
    }
};

class BorrowInfo
{
private:
    int id = 1;
    int personId;
    int bookId;
    int eBookId;

public:
    BorrowInfo() {}
    BorrowInfo(int personId, int bookId, int eBookId)
        : personId(personId), bookId(bookId), eBookId(eBookId)
    {
        id = getNextId(); // Tự động nhận id bé nhất chưa xuất hiện trong file
    }

    std::string toString() const
    {
        return std::to_string(id) + " " + std::to_string(personId) + " " + std::to_string(bookId) + " " + std::to_string(eBookId);
    }

    bool validateInput(const std::set<std::string> &existingInfo) const
    {
        return (id >= 0 && personId >= 0 && bookId >= 0 && eBookId >= 0 && existingInfo.find(toString()) == existingInfo.end());
    }

    // Hàm tìm id bé nhất chưa xuất hiện trong file borrowInfos.txt
    int getNextId() const
    {
        std::ifstream inFile("borrowInfos.txt");
        if (!inFile)
        {
            return 1; // Nếu file không tồn tại, trả về id đầu tiên
        }

        std::set<int> existingIds;
        int maxId = 0;
        std::string line;
        while (std::getline(inFile, line))
        {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ' ');
            int currentId = std::stoi(token);
            existingIds.insert(currentId);
            maxId = std::max(maxId, currentId);
        }
        inFile.close();

        // Tìm id bé nhất chưa xuất hiện
        for (int i = 1; i <= maxId + 1; ++i)
        {
            if (existingIds.find(i) == existingIds.end())
            {
                return i;
            }
        }

        // Trường hợp tất cả các id từ 1 đến maxId đều đã xuất hiện
        return maxId + 1;
    }
    void setPersonId(int personId)
    {
        this->personId = personId;
    }
    int getPersonId()
    {
        return personId;
    }
    void setBookId(int bookId)
    {
        this->bookId = bookId;
    }
    int getBookId()
    {
        return bookId;
    }
    void setEBook(int eBookId)
    {
        this->eBookId = eBookId;
    }
    int getEBook()
    {
        return eBookId;
    }
    void addInfo()
    {
        // Thêm thông tin vào file borrowInfos.txt
        std::ofstream file("borowInfos.txt", std::ios_base::app);
        file << "[" << id << "] [" << personId << "] [" << bookId << "] [" << eBookId << "]\n";
        file.close();
    }

    BorrowInfo(int id, int personId, int bookId, int eBookId)
        : id(id), personId(personId), bookId(bookId), eBookId(eBookId) {}

    // std::string toString() const
    // {
    //     return std::to_string(id) + " " + std::to_string(personId) + " " + std::to_string(bookId) + " " + std::to_string(eBookId);
    // }

    // bool validateInput(const std::set<string> &existingInfo) const
    // {
    //     return (id >= 0 && personId >= 0 && bookId >= 0 && eBookId >= 0 && existingInfo.find(toString()) == existingInfo.end());
    // }
};

std::set<std::string> readExistingInfo(const std::string &filename)
{
    std::ifstream inFile(filename);
    std::set<std::string> existingInfo;
    if (inFile)
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            existingInfo.insert(line);
        }
        inFile.close();
    }
    return existingInfo;
}

void updateBorrowInfos(const std::vector<BorrowInfo> &infos)
{
    std::ofstream outFile("borrowInfos.txt", std::ios::app);
    if (!outFile)
    {
        std::cerr << "Không thể mở file để ghi." << std::endl;
        return;
    }

    std::set<std::string> existingInfo = readExistingInfo("borrowInfos.txt");

    for (const auto &info : infos)
    {
        if (info.validateInput(existingInfo))
        {
            outFile << info.toString() << std::endl;
            existingInfo.insert(info.toString());
        }
        else
        {
            std::cerr << "Dữ liệu không hợp lệ hoặc đã tồn tại. Bỏ qua bản ghi." << std::endl;
        }
    }
    outFile.close();
    std::cout << "Thông tin đã được cập nhật vào file." << std::endl;
}
int main()
{
    
}
