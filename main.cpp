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


int main() {
    cout<<"Hello world !";
    return 0;
}