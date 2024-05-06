#include <bits/stdc++.h>

using namespace std;

class User{
    private:
        int id;
        string email;
        string password;
    public:
        User(int id, string email, string password);
        void registerr();
        void login();
        void logout();

};

User::User(int id, string email, string password){
    this -> id = id;
    this -> email = email;
    this -> password = password;
}

int main()
{
    // Insert code here
    return 0;
}