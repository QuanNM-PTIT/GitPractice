#include <bits/stdc++.h>
#include "../function/getSmallestId.h"
#include "../function/getKeyId.h"
#include "../function/validate.h"
#include "../data/fileName.h"

#ifndef BOOK_H
#define BOOK_H

using namespace std;

int cmp(string book1, string book2);

class Book {
    private:
        int id;
        string title;
        string author;
        int quantity;
    public:
        Book(string title, string author, int quantity)
            : title(title), author(author), quantity(quantity) {}
        friend void addBook();
        friend vector<Book> getBooks();
        friend void updateBook();
        friend void deleteBook();
        friend void displayBook();

        int getBookId();
        string getBookTitle();
        string getBookAuthor();
        int getBookQuantity();
};

void addBook(){
    system("cls");
    cout << "3. Them sach.\n";
    cout << "Hay nhap thong tin sach can them!\n";
    string title;
    string author;
    int quantity;
    cout << "Nhap Ten sach: ";
    cin.ignore();
    getline(cin, title);
    cout << "Nhap Ten tac gia: ";
    cin.ignore();
    getline(cin, author);
    cout << "Nhap So luong sach: ";
    cin >> quantity;
    Book newBook = Book(title, author, quantity);

    ofstream outFile(BooksFile, ios::app);
    outFile << "[" << newBook.getBookId() << "] ";
    outFile << "[" << newBook.getBookTitle() << "] ";
    outFile << "[" << newBook.getBookAuthor() << "] ";
    outFile << "[" << newBook.getBookQuantity() << "]\n";
    outFile.close();
    return;
}
vector<Book> getBooks(){
    
}
void updateBook(){
    while (1) {
        system("cls");
        cout << "4. Sua thong tin sach.\n";
        cout << "Nhap ID sach can sua thong tin: ";
        int updateId;
        cin >> updateId;
        if (exsitedId(updateId, BooksFile)) {
            string newTitle;
            string newAuthor;
            int newQuantity;
            cout << "Nhap thong tin moi!\n";
            cout << "Nhap Ten sach: ";
            cin.ignore();
            getline(cin, newTitle);
            cout << "Nhap Ten tac gia: ";
            cin.ignore();
            getline(cin, newAuthor);
            cout << "Nhap So luong sach: ";
            cin >> newQuantity;
            
            vector<string> bookList;
            ifstream inFile(BooksFile);
            string tmp;
            while (getline(inFile, tmp)){
                bookList.push_back(tmp);
            }
            inFile.close();
            for (int i = 0; i < bookList.size(); i++){
                int bookId = getKeyId(bookList[i]);
                if (bookId == updateId){
                    bookList[i] = "[" + to_string(updateId) + "] ";
                    bookList[i] += "[" + newTitle + "] ";
                    bookList[i] += "[" + newAuthor + "] ";
                    bookList[i] += "[" + to_string(newQuantity) + "]";
                    break;
                }
            }
            ofstream outFile(BooksFile);
            for (int i = 0; i < bookList.size(); i++){
                outFile << bookList[i] << "\n";
            }
            outFile.close();
            cout << "Chinh sua sach thanh cong!!\n";
            return;
        }
        else {
            cout << "ID sach khong ton tai!\n";
            cout << "Ban co muon nhap lai ID sach? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                cout << "Ban da huy yeu cau sua thong tin sach!\n";
                break;
            }
        }
    }
    return;
}
void deleteBook(){
    while (1) {
        system("cls");
        cout << "5. Xoa sach.\n";
        cout << "Nhap ID sach can xoa: ";
        int deleteId;
        cin >> deleteId;
        if (exsitedId(deleteId, BooksFile)) {
            cout << "Ban co chac muon xoa quyen sach nay? (1/0) ";
            int choose;
            cin >> choose;
            if (choose) {
                vector<string> bookList;
                ifstream inFile(BooksFile);
                string tmp;
                while (getline(inFile, tmp)){
                    bookList.push_back(tmp);
                }
                inFile.close();
                ofstream outFile(BooksFile);
                for (int i = 0; i < bookList.size(); i++){
                    int bookId = getKeyId(bookList[i]);
                    if (bookId != deleteId){
                        outFile << bookList[i] << "\n";
                    }
                }
                outFile.close();
                cout << "Xoa sach thanh cong!!\n";
            }
            else {
                cout << "Ban da huy yeu cau xoa sach!!\n";
            }
            return;
        }
        else {
            cout << "ID sach khong ton tai!\n";
            cout << "Ban co muon nhap lai ID sach? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                cout << "Ban da huy yeu cau xoa sach!!\n";
                break;
            }
        }
    }
    return;
}
void displayBook(){
    system("cls");
    cout << "8. Lay thong tin cac quyen sach.\n";
    vector<string> bookList;
    ifstream inFile(BooksFile);
    string tmp;
    while (getline(inFile, tmp)){
        bookList.push_back(tmp);
    }
    inFile.close();
    sort(bookList.begin(), bookList.end(), cmp);
    cout << "Danh sach cac dau sach hien co:\n";
    for (auto book : bookList) {
        cout << book << "\n";
    }
    return;
}
void getOneBook(){
    while (1) {
        system("cls");
        cout << "9. Lay thong tin 1 quyen sach.\n";
        cout << "Nhap ID sach can tim: ";
        int bookId;
        cin >> bookId;
        if (exsitedId(bookId, BooksFile)) {
            vector<string> bookList;
            ifstream inFile(BooksFile);
            string tmp;
            while (getline(inFile, tmp)){
                bookList.push_back(tmp);
            }
            inFile.close();
            string bookInfo = "";
            for (auto book : bookList) {
                if (bookId == getKeyId(book)) {
                    bookInfo = book;
                    break;
                }
            }
            cout << "Thong tin sach tim duoc:\n";
            cout << bookInfo << "\n";
            break;
        }
        else {
            cout << "ID sach khong ton tai!\n";
            cout << "Ban co muon nhap lai ID sach? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                cout << "Ban da huy yeu cau tim sach!!\n";
                break;
            }
        }
    }
    return;
}

int Book::getBookId(){
    return this -> id;
}
string Book::getBookTitle(){
    return this -> title;
}
string Book::getBookAuthor(){
    return this -> author;
}
int Book::getBookQuantity(){
    return this -> quantity;
}
int cmp(string book1, string book2){
    return getKeyId(book1) < getKeyId(book2);
}

#endif