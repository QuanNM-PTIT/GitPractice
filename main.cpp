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

class bookInfo{ // dung 1 class rieng cho thong tin cua sach

    private:
        int id;
        string title;
        string author;
        int quantity;

    public:

        // bookInfo(int id, string title, string author, int quantity){ // ham khoi tao
        //     id = id;
        //     title = title;
        //     author = author;
        //     quantity = quantity;
        // }
        bookInfo(int id, string title, string author, int quantity) : id(id), title(title), author(author), quantity(quantity) {}

        int getId() {return id;} // lay ra id

        string getTitle() {return title;} // lay ra title

        string getAuthor() {return author;} // lay ra author

        int getQuantity() {return quantity;} // lay ra quantity
};

class book{ // class chua nhung thuoc tinh theo yeu cau

    private:

        vector<bookInfo> Books;

        int getNextId(){
            if(Books.empty()){
                return 1;
            }
            else return Books.size() + 1;
        }

        bool checkBook(bookInfo &Book){
            if(Book.getTitle().empty() || Book.getAuthor().empty() || Book.getQuantity() <= 0){
                return false;
            }
            return true;
        }

    public:

        book(){
            ifstream ifs("books.txt");
            if(ifs.is_open()){
                string line;
                while(getline(ifs, line)){
                    stringstream ss(line);
                    int id, quantity;
                    string title, author;
                    // Bỏ qua ký tự [ và ]
                    char c;
                    ss >> c >> id >> c >> c; // Bo qua ky tu [, sau do doc id, sau do bo qua ky tu ] [
                    getline(ss, title, ']'); // doc title den khi gap ky tu ]
                    ss >> c; // bo qua ky tu [
                    getline(ss, author, ']'); // doc author den khi gap ky tu ]
                    ss >> c >> quantity >> c; // Bo qua ky tu [, sau do doc quantity, sau do bo qua ky tu ]
                    Books.push_back(bookInfo(id, title, author, quantity));
                }
                ifs.close();
            }
        }

        void AddBook(bookInfo &Book){ // chi user co tai khoan admin moi su dung duoc
            if(!checkBook(Book)){
                cout << "thong tin sach con thieu! \n";
                return;
            }
            else{
                int id = getNextId();
                string title = Book.getTitle();
                string author = Book.getAuthor();
                int quantity = Book.getQuantity();
                Books.push_back(bookInfo(id, title, author, quantity)); // them data vao vector
                ofstream ofs("books.txt");
                if(ofs.is_open()){
                    // ofs.clear();
                    for(auto x : Books){
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getTitle() << ']' << ' ' << '[' << x.getAuthor() << ']' << ' ' << '[' << x.getQuantity() << ']' << endl;
                    }
                    ofs.close();
                    cout << "sach duoc them vao thanh cong!\n";
                } 
                else{
                    cout << "loi khi khong truy cap duoc vao data!\n";
                }
            }
        }

        void getBooks(){ // in ra thong tin cua tat ca sach co trong thu vien
            for(auto x : Books){
                cout << x.getId() << ' ' << x.getTitle() << ' ' << x.getAuthor() << ' ' << x.getQuantity() << '\n';
            }
        }

        void updateBook(bookInfo &bookUpdate){ // update theo id cua sach
            bool check = false;
            for(auto &x : Books){
                if(x.getId() == bookUpdate.getId()){
                    check = true;
                    if(!checkBook(bookUpdate)) cout << "thong tin update khong hop le\n";
                    else x = bookUpdate; // cap nhat trong vector Books
                    break;
                }
            }
            if(!check) cout << "khong tim thay thong tin!\n";
            else{
                ofstream ofs("books.txt", ios::trunc); // mo tep trong che đo ghi đe
                if(ofs.is_open()){ // cap nhat lai trong file book.txt
                    // ofs.clear();
                    for(auto x : Books){
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getTitle() << ']' << ' ' << '[' << x.getAuthor() << ']' << ' ' << '[' << x.getQuantity() << ']' << endl;
                    }
                    ofs.close();
                    cout << "update thanh cong!\n";
                }
                else cout << "loi khi khong truy cap duoc vao data.\n";
            }
        }
};

bool cmp(bookInfo a, bookInfo b){ // sap xep theo thu tu tu be den lon
    return a.getId() < b.getId();
}

int main()
{
    string name, email, sex , birthdate , address , phone , role;
    getline( cin , name );
    getline( cin , email );
    getline( cin , sex );
    getline( cin , birthdate );
    getline( cin , address );
    getline( cin , phone );
    getline( cin , role );
    Person a( name , email , sex , birthdate , address , phone , role );
    a.addInfo();
    return 0;
}
// Nguyen Tien Trong
// trongbg2692004@gmail.com
// male
// 16/09/2004
// Bac Giang
// 0838947749
// Admin
