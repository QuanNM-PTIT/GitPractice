#include <bits/stdc++.h>
#include "../function/getSmallestId.cpp"
#include "../function/getKeyId.cpp"
#include "../function/validate.cpp"

using namespace std;

const string BorrowInfosFile = "../data/borrowInfos.txt";
const string PeopleFile = "../data/people.txt";
const string BooksFile = "../data/books.txt";
const string EBooksFile = "../data/ebooks.txt";

bool validate(int borrowId, int personId, int bookId, int eBookId);

class BorrowInfo {
    private:
        int id;
        int personId;
        int bookId;
        int eBookId;
    public:
        BorrowInfo(int personId, int bookId, int eBookId);
        friend void addBorrowInfo(BorrowInfo newBorrowInfo);
        friend void updateBorrowInfor(int updateBorrowId, int newPersonId, int newBookId, int newEBookId);
        int getBorrowId();
        int getPersonId();
        int getBookId();
        int getEBookId();
};

BorrowInfo::BorrowInfo(int personId, int bookId, int eBookId){
    this -> id = getSmallestId(BorrowInfosFile);
    this -> personId = personId;
    this -> bookId = bookId;
    this -> eBookId = eBookId;
}
void addBorrowInfo(BorrowInfo newBorrowInfo){
    int borrowId = newBorrowInfo.getBorrowId();
    int personId = newBorrowInfo.getPersonId();
    int bookId = newBorrowInfo.getBookId();
    int eBookId = newBorrowInfo.getEBookId();
    if (validate(borrowId, personId, bookId, eBookId)){
        ofstream outFile(BorrowInfosFile, ios::app);
        outFile << "[" << borrowId << "] ";
        outFile << "[" << personId << "] ";
        outFile << "[" << bookId << "] ";
        outFile << "[" << eBookId << "]\n";
        outFile.close();
    }
    else {
        cout << "Invalid Data!\n";
    }
    return;
}
void updateBorrowInfor(int updateBorrowId, int newPersonId, int newBookId, int newEBookId){
    if (validateId(updateBorrowId, BorrowInfosFile) && validate(-1, newPersonId, newBookId, newEBookId)){
        vector<string> borrowList;
        ifstream inFile(BorrowInfosFile);
        string tmp;
        while (getline(inFile, tmp)){
            borrowList.push_back(tmp);
        }
        inFile.close();
        for (int i = 0; i < borrowList.size(); i++){
            int borrowId = getKeyId(borrowList[i]);
            if (borrowId == updateBorrowId){
                borrowList[i] = "[" + to_string(updateBorrowId) + "] ";
                borrowList[i] += "[" + to_string(newPersonId) + "] ";
                borrowList[i] += "[" + to_string(newBookId) + "] ";
                borrowList[i] += "[" + to_string(newEBookId) + "]";
                break;
            }
        }
        ofstream outFile(BorrowInfosFile);
        for (int i = 0; i < borrowList.size(); i++){
            outFile << borrowList[i] << "\n";
        }
        outFile.close();
    }   
    else {
        cout << "Invalid Data!!\n";
    }
    return;
}
int BorrowInfo::getBorrowId(){
    return this -> id;
}
int BorrowInfo::getPersonId(){
    return this -> personId;
}
int BorrowInfo::getBookId(){
    return this -> bookId;
}
int BorrowInfo::getEBookId(){
    return this -> eBookId;
}

int main(){
    // Insert code here
    cout << "Hello BorrowInfo\n";
    int borrowId = 1;
    int personId = 1;
    int bookId = 1;
    int eBookId = 1;

    if (validate(-1, 1, 1, 1)){
        cout << "Khoi tao Thanh cong!\n";
        BorrowInfo newBorrow = BorrowInfo(personId, bookId, eBookId);
        cout << "BorrowID: " << newBorrow.getBorrowId() << "\n";
        addBorrowInfo(newBorrow);
        updateBorrowInfor(11, 2, 3, 4);
    }
    else {
        cout << "Hay nhap lai thong tin!!\n";
    }
    return 0;
}

bool validate(int borrowId, int personId, int bookId, int eBookId){
    if (validateId(borrowId, BorrowInfosFile)){
        cout << "ID muon sach da ton tai!\n";
        return false;
    }
    if (!validateId(personId, PeopleFile)){
        cout << "ID nguoi muon sach khong hop le!\n";
        return false;
    }
    if (!validateId(bookId, BooksFile)){
        cout << "ID sach khong hop le!\n";
        return false;
    }
    if (!validateId(eBookId, EBooksFile)){
        cout << "ID sach dien tu khong hop le!\n";
        return false;
    }
    return true;
}