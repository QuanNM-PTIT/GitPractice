#include <bits/stdc++.h>

using namespace std;

class Book {
    private:
        int id;
        string title;
        string author;
        int quantity;
    public:
        Book(int id, string title, string author, int quantity);
        void addBook();
        vector<Book> getBooks();
        void updateBook(int bookId);
        void deleteBook(int bookId);
        int getBookID();
};

Book::Book(int id, string title, string author, int quantity){
    this -> id = id;
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


int getSmallestID(vector<Book> bookList){
    int present[bookList.size()] = {0};
    for (auto book : bookList)
        present[book.getBookID()] = 1;
    for (int i = 0; i < bookList.size(); i++){
        if (!present[i]){
            return i;
        } 
    }
    return -1;
}

// int main(){
//     // Insert code here
    
//     cout << "Hello";
//     return 0;
// }