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
};
