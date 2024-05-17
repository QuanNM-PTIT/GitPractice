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


#endif