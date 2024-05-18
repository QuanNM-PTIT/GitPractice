#include <bits/stdc++.h>
#include "../function/getSmallestId.h"
#include "../function/getKeyId.h"
#include "../function/validate.h"
#include "../data/fileName.h"

using namespace std;

#ifndef BORROWINFO_H
#define BORROWINFO_H

bool validate(int borrowId, int personId, int bookId, int eBookId);
int getPersonIdInLine(string dataLine);

class BorrowInfo {
    private:
        int id;
        int personId;
        int bookId;
        int eBookId;
    public:
        BorrowInfo(int personId, int bookId, int eBookId);
        friend BorrowInfo initBorrowInfo();
        friend void addBorrowInfo();
        friend void updateBorrowInfor(int updateBorrowId, int newPersonId, int newBookId, int newEBookId);
        friend void deleteBorrowInfo();
        friend void showBorrowedBook(int personId);
        friend void showBorrowedBookWithUserId();
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
BorrowInfo initBorrowInfo(int personId, int bookId, int eBookId){
    if (validate(-1, personId, bookId, eBookId)){
        return BorrowInfo(personId, bookId, eBookId);
    }
    else {
        cout << "Invalid!";
    }
}
void addBorrowInfo(){
    while (1) {
        system("cls");
        cout << "6. Muon sach.\n";
        int borrowId, personId, bookId, eBookId;
        cout << "Hay nhap thong tin!\n";
        borrowId = getSmallestId(BorrowInfosFile);
        cout << "PersonID: ";
        cin >> personId;
        cout << "BookID: ";
        cin >> bookId;
        cout << "EBookID: ";
        cin >> eBookId;
        if (validate(borrowId, personId, bookId, eBookId)){
            ofstream outFile(BorrowInfosFile, ios::app);
            outFile << "[" << borrowId << "] ";
            outFile << "[" << personId << "] ";
            outFile << "[" << bookId << "] ";
            outFile << "[" << eBookId << "]\n";
            outFile.close();
            cout << "Them thong tin muon sach thanh cong!!\n";
            break;
        }
        else {
            cout << "Invalid Data!\n";
            cout << "Ban co muon nhap lai thong tin? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                cout << "Ban da huy yeu cau them thong tin muon!\n";
                break;
            }
        }
    }
    return;
}
void updateBorrowInfor(int updateBorrowId, int newPersonId, int newBookId, int newEBookId){
    if (exsitedId(updateBorrowId, BorrowInfosFile) && validate(-1, newPersonId, newBookId, newEBookId)){
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
void deleteBorrowInfo(){
    while (1) {
        system("cls");
        cout << "7. Tra sach.\n";
        cout << "Nhap ID muon sach can tra: ";
        int deleteId;
        cin >> deleteId;
        if (exsitedId(deleteId, BorrowInfosFile)) {
            cout << "Ban co chac muon tra cuon sach nay? (1/0) ";
            int choose;
            cin >> choose;
            if (choose) {
                vector<string> borrowList;
                ifstream inFile(BorrowInfosFile);
                string tmp;
                while (getline(inFile, tmp)){
                    borrowList.push_back(tmp);
                }
                inFile.close();
                ofstream outFile(BorrowInfosFile);
                for (int i = 0; i < borrowList.size(); i++){
                    int borrowId = getKeyId(borrowList[i]);
                    if (borrowId != deleteId){
                        outFile << borrowList[i] << "\n";
                    }
                }
                outFile.close();
                cout << "Tra sach thanh cong!!\n";
            }
            else {
                cout << "Ban da huy yeu cau tra sach!!\n";
            }
            return;
        }
        else {
            cout << "ID muon sach khong ton tai!\n";
            cout << "Ban co muon nhap lai ID muon sach? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                cout << "Ban da huy yeu cau tra sach!\n";
                break;
            }
        }
    }
    return;
}
void showBorrowedBook(int personId){
    system("cls");
    cout << "12. Hien thi tat ca cac quyen sach da muon.\n";
    if (exsitedId(personId, BorrowInfosFile, 2)) {
        vector<string> borrowList;
        ifstream inFile(BorrowInfosFile);
        string tmp;
        while (getline(inFile, tmp)){
            borrowList.push_back(tmp);
        }
        inFile.close();
        int bookIdInFile = -1;
        int eBookIdInFile = -1;
        for (int i = 0; i < borrowList.size(); i++){
            int personIdInFile = getPersonIdInLine(borrowList[i]);
            if (personId == personIdInFile){
                stringstream ss(borrowList[i]);
                string tmp;
                ss >> tmp;
                ss >> tmp;
                ss >> tmp;
                bookIdInFile = stoi(tmp.substr(1, tmp.size()-2));
                ss >> tmp;
                eBookIdInFile = stoi(tmp.substr(1, tmp.size()-2));
                break;
            }
        }
        if (bookIdInFile != -1) {
            ifstream inFile(BooksFile);
            string tmp;
            while (getline(inFile, tmp)){
                if (getKeyId(tmp) == bookIdInFile) {
                    cout << tmp << "\n";
                    break;
                }
            }
            inFile.close();
        }
        if (eBookIdInFile != -1) {
            ifstream inFile(EBooksFile);
            string tmp;
            while (getline(inFile, tmp)){
                if (getKeyId(tmp) == eBookIdInFile) {
                    cout << tmp << "\n";
                    break;
                }
            }
            inFile.close();
        }
    }
    else {
        cout << "Ban chua muon cuon sach nao ca!!\n";
    }
    return;
}
void showBorrowedBookWithUserId(){
    while (1) {
        system("cls");
        cout << "13. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon.\n";
        cout << "Nhap ID nguoi dung can tra cuu: ";
        int personId;
        cin >> personId;
        if (!exsitedId(personId, PeopleFile)) {
            cout << "ID nguoi dung khong ton tai!!\n";
            cout << "Ban co muon nhap lai ID nguoi dung? (1/0) ";
            int choose;
            cin >> choose;
            if (!choose) {
                cout << "Ban da huy yeu cau sach da muon cua 1 nguoi dung!\n";
                break;
            }
        }
        else if (exsitedId(personId, BorrowInfosFile, 2)) {
            vector<string> borrowList;
            ifstream inFile(BorrowInfosFile);
            string tmp;
            while (getline(inFile, tmp)){
                borrowList.push_back(tmp);
            }
            inFile.close();
            int bookIdInFile = -1;
            int eBookIdInFile = -1;
            for (int i = 0; i < borrowList.size(); i++){
                int personIdInFile = getPersonIdInLine(borrowList[i]);
                if (personId == personIdInFile){
                    stringstream ss(borrowList[i]);
                    string tmp;
                    ss >> tmp;
                    ss >> tmp;
                    ss >> tmp;
                    bookIdInFile = stoi(tmp.substr(1, tmp.size()-2));
                    ss >> tmp;
                    eBookIdInFile = stoi(tmp.substr(1, tmp.size()-2));
                    break;
                }
            }
            if (bookIdInFile != -1) {
                ifstream inFile(BooksFile);
                string tmp;
                while (getline(inFile, tmp)){
                    if (getKeyId(tmp) == bookIdInFile) {
                        cout << tmp << "\n";
                        break;
                    }
                }
                inFile.close();
            }
            if (eBookIdInFile != -1) {
                ifstream inFile(EBooksFile);
                string tmp;
                while (getline(inFile, tmp)){
                    if (getKeyId(tmp) == eBookIdInFile) {
                        cout << tmp << "\n";
                        break;
                    }
                }
                inFile.close();
            }
            break;
        }
        else {
            cout << "Nguoi dung nay chua muon cuon sach nao ca!!\n";
            break;
        }
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

bool validate(int borrowId, int personId, int bookId, int eBookId){
    if (exsitedId(borrowId, BorrowInfosFile)){
        cout << "ID muon sach da ton tai!\n";
        return false;
    }
    if (!exsitedId(personId, PeopleFile)){
        cout << "ID nguoi muon sach khong hop le!\n";
        return false;
    }
    if (!exsitedId(bookId, BooksFile)){
        cout << "ID sach khong hop le!\n";
        return false;
    }
    if (!exsitedId(eBookId, EBooksFile)){
        cout << "ID sach dien tu khong hop le!\n";
        return false;
    }
    return true;
}
int getPersonIdInLine(string dataLine){
    stringstream ss(dataLine);
    string tmp;
    ss >> tmp;
    ss >> tmp;
    int id = stoi(tmp.substr(1, tmp.size()-2));
    return id;
}

#endif