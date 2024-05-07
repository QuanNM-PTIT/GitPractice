#include <bits/stdc++.h>
using namespace std;

class  Book {
private:
    int id;
    string title;
    string author;
    int quantity;
public:
    Book() {}

    Book(string title, string author, int quantity){
        this -> title = title;
        this -> author = author;
        this -> quantity = quantity;
    }

    int getID(){
        return this -> id;
    }

    void setID(int id){
        this -> id = id;
    }

    string getTitle(){
        return this -> title;
    }

    void setTitle(string title){
        this -> title = title;
    }

    int getQuantity(){
        return this -> quantity;
    }

    void setQuantity(int quantity){
        this -> quantity = quantity;
    }

    void addBook(const string& bookInf){
        ofstream outFile("test_add_book.txt", ios::app); 

        if(outFile.is_open()){
            outFile << bookInf << '\n';
            outFile.close();
            cout << "Thong tin cua cuon sach da duoc ghi thanh cong !\n";
        } else {
            cerr << "Mo file that bai !\n";
        }
    }
};

int main() {
    Book a;
    string bookInf;
    getline(cin, bookInf);
    a.addBook(bookInf);
    return 0;
}