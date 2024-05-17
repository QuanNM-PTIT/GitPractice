#include <bits/stdc++.h>
#include "./Book.h"
#include "../function/getSmallestId.h"

using namespace std;

#ifndef EBOOK_H
#define EBOOK_H

class EBook : private Book{
    private:
        string fileFormat;
        int fileSize;
    public:
        EBook(string title, string author, int quantity, double fileSize)
            : Book(title, author, quantity), fileSize(fileSize) {}
        friend void displayEBook();
        friend void getOneEBook();
};

void displayEBook(){
    system("cls");
    cout << "10. Lay thong tin tat ca cac eBook hien co.\n";
    vector<string> bookList;
    ifstream inFile(EBooksFile);
    string tmp;
    while (getline(inFile, tmp)){
        bookList.push_back(tmp);
    }
    inFile.close();
    sort(bookList.begin(), bookList.end(), cmp);
    cout << "Danh sach cac dau sach dien tu hien co:\n";
    for (auto book : bookList) {
        cout << book << "\n";
    }
    return;
}
void getOneEBook(){
    while (1) {
        system("cls");
        cout << "11. Lay thong tin 1 EBook.\n";
        cout << "Nhap ID EBook can tim: ";
        int eBookId;
        cin >> eBookId;
        if (exsitedId(eBookId, EBooksFile)) {
            vector<string> bookList;
            ifstream inFile(EBooksFile);
            string tmp;
            while (getline(inFile, tmp)){
                bookList.push_back(tmp);
            }
            inFile.close();
            string bookInfo = "";
            for (auto book : bookList) {
                if (eBookId == getKeyId(book)) {
                    bookInfo = book;
                    break;
                }
            }
            cout << "Thong tin EBook tim duoc:\n";
            cout << bookInfo << "\n";
            break;
        }
        else {
            cout << "ID EBook khong ton tai!\n";
            cout << "Ban co muon nhap lai ID EBook? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                cout << "Ban da huy yeu cau tim EBook!!\n";
                break;
            }
        }
    }
    return;
}


#endif