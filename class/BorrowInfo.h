#include <bits/stdc++.h>
#include "../function/getSmallestId.h"
#include "../function/getKeyId.h"
#include "../function/validate.h"
#include "../data/fileName.h"

using namespace std;

#ifndef BORROWINFO_H
#define BORROWINFO_H

bool validate(int borrowId, int personId, int bookId, int eBookId);

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
        int deleteBorrowId;
        cin >> deleteBorrowId;
        if (exsitedId(deleteBorrowId, BorrowInfosFile)) {
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
                    if (borrowId != deleteBorrowId){
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

#endif