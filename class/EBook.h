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
        EBook();
};

EBook::EBook(){
    Book("", "", 0);
    this -> fileFormat = "";
    this -> fileSize = 0;
}

#endif