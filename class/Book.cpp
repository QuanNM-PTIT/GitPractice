#include <bits/stdc++.h>

using namespace std;

int getSmallestID();

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
    this -> id = getSmallestID();
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


int getSmallestID(){
    vector<int> bookIdList;
    ifstream inFile;
    inFile.open("../books.txt");
    string s;
    while (getline(inFile, s)){
        stringstream ss(s);
        string tmp;
        ss >> tmp;
        int id = stoi(tmp.substr(1, tmp.size()-2));
        bookIdList.push_back(id);
    }

    int present[bookIdList.size()] = {0};
    for (auto id : bookIdList)
        present[id] = 1;
    for (int i = 1; i <= bookIdList.size(); i++){
        if (!present[i]){
            return i;
        } 
    }
    return bookIdList.size()+1;
}

int main(){
    // Insert code here
    
    cout << "HelloBook\n";
    Book sach1 = Book("Thep da toi the day", "Nikolai A Ostrovsky", 1);
    cout << sach1.getBookID();
    return 0;
}