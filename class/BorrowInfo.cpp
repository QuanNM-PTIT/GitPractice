#include <bits/stdc++.h>

using namespace std;

int getSmallestId();
int getId(string borrow);

class BorrowInfo {
    private:
        int id;
        int personId;
        int bookId;
        int eBookId;
    public:
        BorrowInfo(int personId, int bookId, int eBookId);
        friend void addInfo(BorrowInfo newBorrowInfo);
        friend void updateInfor(int updateBorrowId, int newPersonId, int newBookId, int newEBookId);
        int getBorrowId();
        int getPersonId();
        int getBookId();
        int getEBookId();
};

BorrowInfo::BorrowInfo(int personId, int bookId, int eBookId){
    this -> id = getSmallestId();
    this -> personId = personId;
    this -> bookId = bookId;
    this -> eBookId = eBookId;
}
void addInfo(BorrowInfo newBorrowInfo){
    ofstream outFile("../borrowInfos.txt", ios::app);
    outFile << "[" << newBorrowInfo.getBorrowId() << "] ";
    outFile << "[" << newBorrowInfo.getPersonId() << "] ";
    outFile << "[" << newBorrowInfo.getBookId() << "] ";
    outFile << "[" << newBorrowInfo.getEBookId() << "]\n";
    outFile.close();
    return;
}
void updateInfor(int updateBorrowId, int newPersonId, int newBookId, int newEBookId){
    vector<string> borrowList;
    ifstream inFile("../borrowInfos.txt");
    string tmp;
    while (getline(inFile, tmp)){
        borrowList.push_back(tmp);
    }
    for (int i = 0; i < borrowList.size(); i++){
        int borrowId = getId(borrowList[i]);
        if (borrowId == updateBorrowId){
            borrowList[i] = "[" + to_string(updateBorrowId) + "] ";
            borrowList[i] += "[" + to_string(newPersonId) + "] ";
            borrowList[i] += "[" + to_string(newBookId) + "] ";
            borrowList[i] += "[" + to_string(newEBookId) + "]";
            break;
        }
    }
    ofstream outFile("../borrowInfos.txt");
    for (int i = 0; i < borrowList.size(); i++){
        outFile << borrowList[i] << "\n";
    }
    outFile.close();
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

// int main(){
//     // Insert code here
//     cout << "Hello BorrowInfo\n";
//     BorrowInfo borrow1 = BorrowInfo(1, 1, 1);
//     addInfo(BorrowInfo(11, 12, 13));
//     cout << borrow1.getBorrowId() << "\n";
//     updateInfor(10, 1, 2, 5);
//     return 0;
// }

int getSmallestId(){
    vector<int> borrowIdList;
    ifstream inFile("../borrowInfos.txt");
    if (!inFile.good()) {
        cout << "Khong the mo tep tin." << endl;
        return -1;
    }
    string s;
    while (getline(inFile, s)){
        stringstream ss(s);
        string tmp;
        ss >> tmp;
        int id = stoi(tmp.substr(1, tmp.size()-2));
        borrowIdList.push_back(id);
    }

    int present[borrowIdList.size()] = {0};
    for (auto id : borrowIdList){
        present[id] = 1;
    }
    for (int i = 1; i <= borrowIdList.size(); i++){
        if (!present[i]){
            return i;
        } 
    }
    return borrowIdList.size()+1;
}
int getId(string borrow){
    stringstream ss(borrow);
    string tmp;
    ss >> tmp;
    int id = stoi(tmp.substr(1, tmp.size()-2));
    return id;
}