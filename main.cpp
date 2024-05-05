#include <bits/stdc++.h>

using namespace std;

class BookInfor{ // dung 1 class rieng cho thong tin cua sach

    private:
        int id;
        string title;
        string author;
        int quantity;

    public:

        BookInfor(int id, string title, string author, int quantity) : id(id), title(title), author(author), quantity(quantity) {}

        int getId() {return id;} // lay ra id
        string getTitle() {return title;} // lay ra title
        string getAuthor() {return author;} // lay ra author
        int getQuantity() {return quantity;} // lay ra quantity
};

class Book{ // class chua nhung thuoc tinh theo yeu cau

    private:

        vector<BookInfor> dsBooks;

        int getNextId(){
            if(dsBooks.empty())  return 1;
            return dsBooks.size() + 1;
        }

        bool checkBook(BookInfor &Book){
            if(Book.getTitle().empty() || Book.getAuthor().empty() || Book.getQuantity() <= 0)
                return false;
            return true;
        }

    public:

        Book(){
            ifstream ifs("books.txt");
            if(ifs.is_open()){
                string line;
                while(getline(ifs, line)){
                    stringstream ss(line);
                    int id, quantity;
                    string title, author;
                    // Bo qua ky tu [ va ]
                    char c;
                    ss >> c >> id >> c >> c; // Bo qua ky tu [, sau do doc id, sau do bo qua ky tu ] [
                    getline(ss, title, ']'); // doc title den khi gap ky tu ]
                    ss >> c; // bo qua ky tu [
                    getline(ss, author, ']'); // doc author den khi gap ky tu ]
                    ss >> c >> quantity >> c; // Bo qua ky tu [, sau do doc quantity, sau do bo qua ky tu ]
                    dsBooks.push_back(BookInfor(id, title, author, quantity));
                }
                ifs.close();
            }
        }

        void AddBook(BookInfor &Book){ // chi user co tai khoan admin moi su dung duoc
            if(!checkBook(Book)){
                cout << "thong tin sach con thieu! \n";
                return;
            }
            else{
                int id = getNextId();
                string title = Book.getTitle();
                string author = Book.getAuthor();
                int quantity = Book.getQuantity();
                dsBooks.push_back(BookInfor(id, title, author, quantity)); // them data vao vector
                ofstream ofs("books.txt");
                if(ofs.is_open()){
                    for(auto x : dsBooks)
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getTitle() << ']' << ' ' << '[' << x.getAuthor() << ']' << ' ' << '[' << x.getQuantity() << ']' << endl;
                    ofs.close();
                    cout << "sach duoc them vao thanh cong!\n";
                } 
                else cout << "loi khi khong truy cap duoc vao data!\n";
            }
        }

        void getBooks(){ // in ra thong tin cua tat ca sach co trong thu vien
            for(auto x : dsBooks)
                cout << x.getId() << ' ' << x.getTitle() << ' ' << x.getAuthor() << ' ' << x.getQuantity() << '\n';
        }

        void updateBook(BookInfor &bookUpdate){ // update theo id cua sach
            bool check = false;
            for(auto &x : dsBooks){
                if(x.getId() == bookUpdate.getId()){
                    check = true;
                    if(!checkBook(bookUpdate)) cout << "thong tin update khong hop le\n";
                    else x = bookUpdate; // cap nhat trong vector dsBooks
                    break;
                }
            }
            if(!check) cout << "khong tim thay thong tin!\n";
            else{
                ofstream ofs("books.txt", ios::trunc); // mo tep trong che đo ghi đe
                if(ofs.is_open()){ // cap nhat lai trong file Book.txt
                    for(auto x : dsBooks)
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getTitle() << ']' << ' ' << '[' << x.getAuthor() << ']' << ' ' << '[' << x.getQuantity() << ']' << endl;
                    ofs.close();
                    cout << "update thanh cong!\n";
                }
                else cout << "loi khi khong truy cap duoc vao data.\n";
            }
        }

        void deleteBook(int id){
            bool check = false;
            for(int i = 0; i < dsBooks.size(); i ++){
                if(dsBooks[i].getId() == id){
                    check = true;
                    dsBooks.erase(dsBooks.begin() + i); // xoa data tren vector dsBooks
                    break;
                }
            }
            if(!check) cout << "khong tim thay thong tin!\n";
            else{
                ofstream ofs("books.txt", ios::trunc); // mo tep trong che đo ghi đe
                if(ofs.is_open()){ // cap nhat lai trong file Book.txt
                    for(auto x : dsBooks)
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getTitle() << ']' << ' ' << '[' << x.getAuthor() << ']' << ' ' << '[' << x.getQuantity() << ']' << endl;
                    ofs.close();
                    cout << "delete thanh cong!\n";
                }
                else cout << "loi khi khong truy cap duoc vao data.\n";
            }
        }
};

bool cmp(BookInfor a, BookInfor b){ // sap xep theo thu tu tu be den lon
    return a.getId() < b.getId();
}

class UserInfos{
    private:

        int id;
        string email;
        string password;

    public:
        
        UserInfos(int id, string email, string password) : id(id), email(email), password(password) {}

        int getId() {return id;}
        string getEmail() {return email;}
        string getPassword() {return password;}
};

class Users{

    private:

        vector<UserInfos> dsUsers;

        bool checkUser(UserInfos check){
            if(check.getEmail().empty() || check.getPassword().empty()) return false;
            return true;
        }

        int getNextId(){
            if(dsUsers.empty()) return 1;
            return dsUsers.size() + 1;
        }

    public:

        Users(){
            ifstream ifs("users.txt");
            if(ifs.is_open()){
                string line;
                while(getline(ifs, line)){
                    stringstream ss(line);
                    int id;
                    string email, password;
                    char c;
                    ss >> c >> id >> c >> c;
                    getline(ss, email, ']');
                    ss >> c;
                    getline(ss, password, ']');
                    dsUsers.push_back(UserInfos(id, email, password));
                }
                ifs.close();
            }
        }

        void regist(UserInfos newUser){
            if(!checkUser(newUser)) cout << "thong tin sai!\n";
            else{
                int id = getNextId();
                string email = newUser.getEmail();
                string password = newUser.getPassword();
                dsUsers.push_back(UserInfos(id, email, password)); // add them vao vector
                ofstream ofs("users.txt");
                if(ofs.is_open()){
                    for(auto &x : dsUsers) // cap nhat lai file txt
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getEmail() << ']' << ' ' << '[' << x.getPassword() << ']' << endl;
                    cout << "user duoc them thanh cong!\n";
                    ofs.close();
                }
                else cout << "khong truy cap duoc data!\n";
            }
        }
};

int main()
{

    freopen("output.txt", "w", stdout);

    // Book test1;
    Users test2;

    // // test addBook => oke
    // BookInfor info1(20, "The Great Gatsby", "F. Scott Fitzgerald", 3);
    // test1.AddBook(info1);

    // // test updateBook => oke
    // BookInfor info2(10, "To Kill a Mockingbird", "Harper Lee", 2);
    // test1.updateBook(info2);

    // // test getBooks => oke
    // test1.getBooks();

    // // test deleteBook => okee
    // test1.deleteBook(12);

    // // test regist => okee
    // test2.regist(UserInfos(0, "ahsdfkjbadugh", "safhdakjg"));

    return 0;
}
