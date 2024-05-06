#include <bits/stdc++.h>

using namespace std;

class Person{
    private:
    int id ; 
    string name , email , sex , birthdate, address, phoneNumber, role;
    public:
    Person( string name , string email , string sex ,string birthdate,string address,string phoneNumber,string role ){
        this->name = name ;
        this->email = email;
        this->sex = sex ;
        this-> birthdate = birthdate; 
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = role;
        ifstream in;
        in.open("people.txt");
        string tmp ;
        int cnt = 0 ; 
        while( getline( in , tmp ) )cnt ++ ; // dem so luong person
        in.close();
        this->id = cnt + 1 ; 
    }
    void addInfo(){
        ofstream out("people.txt", ios::app); 
        out << '[' << this->id << ']' << " " << '[' << this->name << ']' << " " << '[' << this->email << "]" << " " << '[' << this->sex << ']' << " " << '[' << this->birthdate << ']' << " " << '[' << this->address << ']' << " " << '[' << this->phoneNumber << ']' << " " << '[' << this->role << ']' << endl;
        out.close();
    }
    int getId(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    string getEmail(){
        return this->email;
    }
    string getSex(){
        return this->sex;
    }
    string getBirthdate(){
        return this->birthdate;
    }
    string getAddress(){
        return this->address;
    }
    string getPhoneNumber(){
        return this->phoneNumber;
    }
    string getRole(){
        return this->role;
    }
};

class BorrowInfo{
    private:
    int id , personId, bookId, eBookId;
    public:
    BorrowInfo( int personId, int bookId, int eBookId ){
        this->personId = personId ; 
        this->bookId = bookId ;
        this->eBookId = eBookId;
        ifstream in;
        in.open("borrowInfos.txt");
        string tmp ;
        int cnt = 0 ; 
        while( getline( in , tmp ) )cnt ++ ; // dem so luong borrowInfos
        in.close();
        this->id = cnt + 1 ;
    }
    void addInfo(){
        ofstream out("borrowInfos.txt", ios::app) ; 
        out << '[' << this->id << ']' << " " << '[' << this->personId << ']' << " " << '[' << this->bookId << "]" << " " << '[' << this->eBookId << ']' << endl;
        out.close();
    }
    int getId(){
        return this->id;
    }
    int getPersonId(){
        return this->personId;
    }
    int getBookId(){
        return this->bookId;
    }
    int getEbookId(){
        return this->eBookId;
    }
};

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

        vector<BookInfor> dsBooks ;

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

        void regist(string email, string password){ // check thong tin dang ki
            if(!checkUser(UserInfos(0, email, password))) cout << "thong tin sai!\n";
            else{
                int id = getNextId();
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

        
        // login logout se tra ve 1 object nen khi su dung thi gan no bang bien (kieu Person)
        Person login(string email, string password){ // check thong tin dang nhap
            if(!checkUser(UserInfos(0, email, password))) cout << "nhap du thong tin!\n";
            else{
                ifstream ifs("people.txt");
                if(ifs.is_open()){
                    string line;
                    while(getline(ifs, line)){
                        int id;
                        string name, emailCheck;
                        string sex, birthday, addre, phone, role;
                        char c;
                        ifs >> c >> id >> c >> c;
                        getline(ifs, name, ']');
                        ifs >> c;
                        getline(ifs, emailCheck, ']');
                        ifs >> c;
                        getline(ifs, sex, ']');
                        ifs >> c;
                        getline(ifs, birthday, ']');
                        ifs >> c;
                        getline(ifs, addre, ']');
                        ifs >> c;
                        getline(ifs, phone, ']');
                        ifs >> c;
                        getline(ifs, role, ']');
                        if(emailCheck == email){
                            ifs.close();
                            return Person(name, emailCheck, sex, birthday, addre, phone, role);
                        }
                    }
                    ifs.close();
                    return Person("", "", "", "", "", "", ""); // neu khong tim thay thong tin
                }
                else{
                    cout << "khong truy cap duoc vao data";
                    return Person("", "", "", "", "", "", ""); // neu khong tim thay thong tin
                }
            }
        }

        Person logout(Person currentUser){ // nhap vao thong tin cua nguoi dung hien tai va cho bien thong tin do bang rong
            return Person("", "", "", "", "", "", "");
        }
};

int main()
{

    freopen("output.txt", "w", stdout);

    // Book test1;
    // Users test2;

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

    // // test login() => okee
    // Person check = test2.login("john.smith@gmail.com", "pass1234");
    // cout << check.getEmail() << ' ' << check.getName() << ' ' << check.getPhoneNumber() << ' ' << check.getRole();

    return 0;
}
