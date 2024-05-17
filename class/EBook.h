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
        EBook::EBook(string title, string author, int quantity, string fileFormat, int fileSize);
};

EBook::EBook(string title, string author, int quantity, string fileFormat, int fileSize){
    Book(title, author, quantity);
    this -> fileFormat = fileFormat;
    this -> fileSize = fileSize;
}


#endif