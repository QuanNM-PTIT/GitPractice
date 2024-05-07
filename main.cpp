#include <bits/stdc++.h>

using namespace std;

class BorrowInfo{
private:
	int id = 1;
	int personId;
	int bookId;
	int eBookId;
public:
    BorrowInfo(int personId, int bookId, int eBookId){
        this->personId = personId;
        this->bookId = bookId;
        this->eBookId = eBookId;
        string file_name = "users.txt";
        ifstream file(file_name);
        string line;
        while(getline(file, line)){
            int pos;
            vector<string> tokens;
            while(pos = line.find("]")){
                string token = line.substr(1, pos - 1);
                tokens.push_back(token);
                line.erase(0, pos + 2);
            }
        }
        
        file.close();
    }
    void addInfo(){
        string file_name = "users.txt";
        ofstream file("file_name");
        file << endl;
        file << "[" << this->id << "] ";
        file << "[" << this->personId << "] ";
        file << "[" << this->bookId << "] ";
        file << "[" << this->eBookId << "]";
        file.close();
    }
    void updateInfo(){

    }
};

class User{
private:
	int id;
	string email;
	string password;
public:
    User(string email, string password){
        this->email = email;
        this->password = password;
    }
    void register(){

    }
    Person login(){

    }
    void logout(){

    }
};

int main() {
    cout << "Hello World";
    return 0;
}