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
class Person{
	private:
		int id;
		string 	name, email, sex, birthdate, 
				address, phoneNumber, role;
		
	public:
		Person(string, string, string, string, string, string, string);
};

Person::Person(string name, string email, string sex, string birthday, string address, string phoneNumber, string role)
{
    this->name = name;
    this->email = email;
    this->sex = sex;
    this->birthdate = birthdate;
    this->address = address;
    this->phoneNumber = phoneNumber;
    this->role = role;
}

// End Person

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
    x.setId(x.getNextAvailableId());
    x.addInfo();
}

vector<int> extractNumbers(const string& input) //ham tra ve 1 vector id, id trong dau [] o file borrowInfo
{
    vector<int> numbers;
    stringstream ss(input);

    char ch;
    int number;

    // �?c t?ng k� t? t? chu?i
    while (ss >> ch) {
        if (ch == '[') {
            // N?u g?p k� t? '[', d?c s? trong d?u '[' ']'
            if (ss >> number) {
                numbers.push_back(number);
                // B? qua c�c k� t? c�n l?i cho d?n khi g?p k� t? ']'
                ss.ignore(numeric_limits<streamsize>::max(), ']');
            }
        }
    }

    return numbers;
}

void capnhatthongtinmuonsach()
{
	vector<BorrowInfo>v;
	ifstream filein("borrowInfos.txt");
	if(!filein.is_open())
	{
		cout << "Khong the mo tep borrowInfos.txt";
	}
	else
	{
		string tmp;
		while(getline(filein, tmp))
		{
			int id, perId, bookId, eBookId;
			vector<int>numbers = extractNumbers(tmp);
			id = numbers[0];
			perId = numbers[1];
			bookId = numbers[2];
			eBookId = numbers[3];
			BorrowInfo x(perId, bookId, eBookId);
			x.setId(id);
			cout << x.getId() << " " << x.getbookId() << endl;
		}
	}
	
	filein.close();
}

// Ket thuc khai bao cac ham thao tac
int main()
{
    Book book;
    // book.addBook(); // Thêm một sách vào file books.txt
    // // book.getBooks(); // Hiển thị thông tin sách trong file books.txt

    // EBook ebook;
    // ebook.addBook(); // Thêm một Ebook vào file books.txt
    //    int idToUpdate;
    //    cout << "Enter ID want to update: ";
    //    cin >> idToUpdate;
    //    book.updateBook(idToUpdate); // Cập nhật thông tin của sách

    //	themthongtinmuonsach(); --> done
    capnhatthongtinmuonsach();

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
