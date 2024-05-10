#include <bits/stdc++.h>
#include "../function/getSmallestId.cpp"

using namespace std;

const string BorrowInfosFile = "../data/borrowInfos.txt";
const string PeopleFile = "../data/people.txt";
const string BooksFile = "../data/books.txt";
const string EBooksFile = "../data/ebooks.txt";

class Book {
    private:
        int id;
        string title;
        string author;
        int quantity;
    public:
        Book(string title, string author, int quantity);
        void addBook();
        vector<Book> getBooks();
        void updateBook(int bookId);
        void deleteBook(int bookId);
        int getBookID();
};

Book::Book(string title, string author, int quantity){
    this -> id = getSmallestId(BooksFile);
    this -> title = title;
    this -> author = author;
    this -> quantity = quantity;
}
void Book::addBook(){

}
vector<Book> Book::getBooks(){

}
void Book::updateBook(int bookId){

}
void Book::deleteBook(int bookId){

}
int Book::getBookID(){
    return this -> id;
}

// int main(){
//     // Insert code here
    
//     cout << "HelloBook\n";
//     Book sach1 = Book("Thep da toi the day", "Nikolai A Ostrovsky", 1);
//     cout << sach1.getBookID();
//     return 0;
// }