#include <bits/stdc++.h>

using namespace std;


class Book{ // thong tin cuon sach
    private:
        int id , qt;
        string title;
        string author;

    public:
        Book(int id, string title, string author, int qt){
            this->id = id;
            this->title = title;
            this->author = author;
            this->qt = qt;
        }

        // lay ra gia tri
        int getId(){
            return id;
        }
        string getTitle(){
            return title;
        }
        string getAuthor(){
            return author;
        }
        int getQuantify(){
            return qt;
        }
};

class Books{ // Làm vc với books.txt
    private:
        vector<Book> dsBooks;

        int getNextId(){
            if(dsBooks.empty()) return 1;
            else return dsBooks.size() +1;
        }

    public:
        Books(){
            ifstream ifs("books.txt");
            
            if(ifs.is_open()){
                string line;
                while(getline(ifs,line)){
                    stringstream ss(line);
                    int id, qt;
                    string title, author; 
                    char s ; // de doc ki tu [,]
                    ss>>s>>id>>s>>s;
                    getline(ss,title,']');
                    ss>>s;
                    getline(ss,author,']');
                    cin>>s>>qt>>s;
                    dsBooks.push_back(Book(id,title,author,qt));
                }
                
                ifs.close();
            }
        }

        // Them thong tin 1 cuon sach
        void addBook(){

        }

        // Lay tat ca thong tin sach trong books.txt 
        void getBooks(){
            for(auto s : dsBooks) 
                cout<<s.getId()<<" "<<s.getTitle()<<" "<<s.getAuthor()<<" "<<s.getQuantify()<<endl;
        }

        //Cap nhat thong tin sach theo id
        void updateBook(){

        }

        //Xoa thong tin 1 cuon sach
        void deleteBook(){

        }


};

class EBook : public Book{
    private: 
        string fileFormat;
        int fileSize;

    public:

};

class Person{
    private: 
        int id;
        string name;
        string email;
        string sex;
        string birthdate;
        string address;
        string phoneNumber;
        string role;
    public:
    Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role){
        this->id = autoId();
        this->name = name;
        this->email = email;
        this->sex = sex;
        this->birthdate = birthdate;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = role;
    }
    int autoId(){
        ifstream in;
        in.open("people.txt");
        set<int> s;
        string tmp;
        while(getline(in, tmp)){
            int i = 1;
            string id = "";
            while(tmp[i] != ']'){
                if(isdigit(tmp[i])) id += tmp[i];
                i++;
            }
            s.insert(stoi(id));
        }
        in.close();
        bool find = false;
        int cnt = 1;
        for(int x : s){
            if(cnt == x) find = true;
            cnt ++;
        }
        return cnt;
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


class User{ // thong tin 1 user
    private:
        int id;
        string email;
        string pw;

    public:
        User(int id, string email, string pw){
            this->id = id;
            this->email = email;
            this->pw = pw;
        }

        //Lay gia tri
        int getId(){
            return id;
        }
        string getEmail(){
            return email;
        }
        string getPassWord(){
            return pw;
        }
};

class Users{ // Làm vc với users.txt
    private:
        vector<User> dsUsers;

        int getNextId(){ // nhan id moi khi khoi tao 1 user moi
            if(dsUsers.empty()) return 1;
            else return dsUsers.size() + 1;
        }

    public:
        Users(){
            ifstream ifs("users.txt");

            if(ifs.is_open()){
                string line;
                while(getline(ifs,line)){
                    stringstream ss(line);
                    int id;
                    string email, pw; 
                    char s ; 
                    ss>>s>>id>>s>>s;
                    getline(ss,email,']');
                    ss>>s;
                    getline(ss,pw,']');
                    
                    dsUsers.push_back(User(id,email,pw));
                }
                
                ifs.close();
            }   
        }

        // Them thong tin dang nhap
        void regist(){

        }

        //Kiem tra thong tin dang nhap , trả ve Person voi email tupng ung
        

        //Dang xuat

};

class BorrowInfo{
    private:
        int id;
        int personId;
        int bookId;
        int eBookId;
    public:
    BorrowInfo(int personId, int bookId, int eBookId){
        this->id = autoId();
        this->personId = personId;
        this->bookId = bookId;
        this->eBookId = eBookId;
    }
    int autoId(){
        ifstream in;
        in.open("borrowInfors.txt");
        set<int> s;
        string tmp;
        while(getline(in, tmp)){
            int i = 1;
            string id = "";
            while(tmp[i] != ']'){
                if(isdigit(tmp[i])) id += tmp[i];
                i++;
            }
            s.insert(stoi(id));
        }
        in.close();
        bool find = false;
        int cnt = 1;
        for(int x : s){
            if(cnt == x) find = true;
            cnt ++;
        }
        return cnt;
    }
    void addInfo(){
        ofstream out("borrowInfors.txt", ios::app);
        out<<'['<<this->id<<']'<<' '<<'['<<this->personId<<']'<<' '<<'['<<this->bookId<<']'<<' '<<'['<<this->eBookId<<']'<<endl;
        out.close();
    }
    void updateInfo(){
        int updateId, updatePersonId, updatepersonId, updateBookId, updateEBookId;
        cout<<"Nhap ID muon sach: ";
        cin >> updateId >> updatePersonId >> updatepersonId >> updateBookId >> updateEBookId;
        // ifstream in;
        // in.open("borowInfors.txt", ios::in);
        // string tmp;
        // vector<B> listBorrowInfor;

        
    }
    int getid(){
        return this->id;
    }
    int getpersonId(){
        return this->personId;
    }
    int getbookId(){
        return this->bookId;
    }
    int geteBookId(){
        return this->eBookId;
    }

};


int main() {
    cout<<"Hello world !";
    return 0;
}