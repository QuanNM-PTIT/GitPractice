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
    //     void updateBook(int id)
    //     {

    //     }
    //     void deleteBook(int id)
    //     {

    //     }
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

int main()
{
    Book book;
    book.addBook(); // Thêm một sách vào file books.txt
    // book.getBooks(); // Hiển thị thông tin sách trong file books.txt

    EBook ebook;
    ebook.addBook(); // Thêm một sách điện tử vào file books.txt

    return 0;
}
