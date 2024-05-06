#include <bits/stdc++.h>
#include "./Book.cpp"

using namespace std;

class EBook : private Book{
    private:
        string fileFormat;
        int fileSize;
    public:
        EBook();
};

EBook::EBook(){
    this -> fileFormat = "";
    this -> fileSize = 0;
}

// int main()
// {
//     // Insert code here
//     cout << "Hello";
//     return 0;
// }