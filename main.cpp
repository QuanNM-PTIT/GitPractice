#include <bits/stdc++.h>

using namespace std;

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

class Book{ // thong tin cuon sach
    private:
        int id , qt;
        string title;
        string author;

    public:
        Book(string title, string author, int qt){
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

bool comp(Book &a , Book &b){ // Sap xep theo thu tu id
    return a.getId() < b.getId();
}

class Books{ // Làm vc với books.txt
    private:
        vector<Book> dsBooks;

        int getNextId(){
            if(dsBooks.empty()) return 1;
            else return dsBooks.size() +1;
        }

        bool checkBook(Book &check_Book){
            if(check_Book.getTitle().empty() || check_Book.getAuthor().empty() || check_Book.getQuantify() < 0)
                return false;
            return true;
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
                    dsBooks.push_back(Book(title,author,qt));
                }
                
                ifs.close();
            }
        }

        // Them thong tin 1 cuon sach (chi Admin)
        void addBook(Book &add_Book){
            ofstream ofs("books.txt",ios::app); // ghi xuong cuoi file
            int id = getNextId();
            string title = add_Book.getTitle();
            string author = add_Book.getAuthor();
            int qt = add_Book.getQuantify();

            dsBooks.push_back(Book(title,author,qt));

            if(ofs.is_open()){
                auto s = dsBooks[id-1];
                ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantify()<<"]"<<endl;

                ofs.close();
                cout<<"Ban vua them sach thanh cong !";
            }
        }

        void SortDsBooks(){ // Sap xep dsBooks theo id
            sort(dsBooks.begin(), dsBooks.end(),comp);
        }

        // Lay tat ca thong tin sach trong books.txt 
        void getBooks(){
            for(auto s : dsBooks) 
                cout<<s.getId()<<" "<<s.getTitle()<<" "<<s.getAuthor()<<" "<<s.getQuantify()<<endl;
        }

        //Cap nhat thong tin sach theo id (Chi Admin)
        void updateBook(Book &update_Book){
            int id  = update_Book.getId(); 
            bool check = true;
            if(id > dsBooks.size()){
                cout<<"Khong tim thay du lieu -_-\n";
                check = false;
            }
            else{
                if(!checkBook(update_Book)) cout<<"Thong tin update chua hop le !\n";
                else{
                    auto s = dsBooks[id-1];
                    s = update_Book; // cap nhat trong dsBooks
                }
            }
            if(check){
                ofstream ofs("books.txt",ios::trunc); // mo tep ghi de
                if(ofs.is_open()){
                    for(auto s : dsBooks)
                        ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantify()<<"]"<<endl;

                    ofs.close();
                    cout<<"Da cap nhat thanh cong !\n";
                }    
            }
        }

        //Xoa thong tin 1 cuon sach
        void deleteBook(Book &delete_Book){
            int id = delete_Book.getId();
            bool check = true;
            if(id > dsBooks.size()){
                cout<<"Du lieu khong ton tai !\n";
                check = false;
            }
            // else{
            //     cout<<"Ban co chac chan muon xoa sach ?\n";
            //     cout<<"Nhan 1 : Yes \t Nhan 2: Cancel";
            //     int chon ; cin>>chon;
            //     if(chon == 1){
                     dsBooks.erase(dsBooks.begin() + id-1); // xoa trong dsBooks
            //     }
            //     else return;
            // }
            if(check){
                ofstream ofs("books.txt",ios::trunc); // mo tep ghi de
                if(ofs.is_open()){
                    for(auto s : dsBooks)
                        ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantify()<<"]"<<endl;

                    ofs.close();
                    cout<<"Da xoa thanh cong !\n";
                }  
            }
        }
};

class EBook : public Book{ // thong tin eBook 
    private: 
        string fileFormat;
        int fileSize;

    public:
        EBook(string title, string author, int qt, string fileFormat, int fileSize):Book(title, author, qt){
            this->fileFormat = fileFormat;
            this->fileSize = fileSize;
        }

        string getFileFormat(){
            return fileFormat;
        }
        int getFileSize(){
            return fileSize;
        }
};


class User{ // thong tin 1 user
    private:
        int id;
        string email, pw;

    public:
        User(string email, string pw){
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

        bool checkUser(User &check_User){
            if(check_User.getEmail().empty() || check_User.getPassWord().empty())
                return false;
            return true;
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
                    
                    dsUsers.push_back(User(email,pw));
                }
                
                ifs.close();
            }   
        }

        bool checkEmail(string email){ // Kiem tra email da co trong data chua ?
            for(auto s : dsUsers){
                if(s.getEmail() == email ){
                    return false; //Email da ton tai
                }
            }
            return true; //email hop le 
        }

        bool checkPassWord(string pw){ //Kiem Pw co dung dinh dang : co it nhat 8 ki tu ( it nhat 1 chu in hoa, 1 chu in thuong , gom chu so )
            if(pw.size() < 8) return false;
            else{
                int cntH = 0 ,cntT = 0, cntS;
                for(int i=0;i<pw.size();++i){
                    if(pw[i] >=0 && pw[i] <= '9') cntS++;
                    else if(pw[i] >= 'A' && pw[i] <= 'Z') cntH++;
                    else if(pw[i] >= 'a' && pw[i] <= 'z') cntT++;
                }
                if(cntH == 0 || cntT == 0 || cntS == 0) return false;
                else return true;
            }
        }

        // Dang ky tai khoan
        void Register(Person &Info,string pw){
            if(!checkEmail(Info.getEmail())){
                cout<<"Email da ton tai !\n";
                return;
            }
            if(!checkPassWord(pw)){
                cout<<"Password chua dung dinh dang !\n";
                cout<<"Password can it nhat 8 ki tu\n Co it nhat 1 ki tu in hoa, 1 ki tu in thuong va chu so\n";
                return;
            }

            int id = getNextId();
            dsUsers.push_back(User(Info.getEmail(),pw));
            cout<<"Tao tai khoan thanh cong !\n";

            ofstream ofs1("users.txt",ios::app);
            if(ofs1.is_open()){
                ofs1<<"["<<id<<"] ["<<Info.getEmail()<<"] ["<<pw<<"]"<<endl;
                ofs1.close();
            } 

            ofstream ofs2("people.txt",ios::app);
            if(ofs2.is_open()){
                int id = Info.autoId();
                string role = "User";
                ofs2<<"["<<id<<"] ["<<Info.getName()<<"] ["<<Info.getEmail()<<"] ["<< Info.getSex() <<"] [" <<Info.getBirthdate()<<"] ["<<Info.getAddress()<<"] ["<<Info.getPhoneNumber()<<"] ["<<role<< ']' << endl;
                ofs2.close();
            } 
        }


        //Kiem tra thong tin dang nhap , trả ve Person voi email tuong ung
        Person login(User &Login,string email, string pw){ 
            // check thong tin dang nhap
            // string email, pw;
            // cout<<"Nhap email cua ban: "; cin>>email;
            // cout<<"Nhap password: "; cin>>pw;
            email = Login.getEmail();
            pw = Login.getPassWord();
            if(!checkUser(Login)) cout << "Chua nhap du thong tin!\n";
            else{
                bool check = false;
                for(auto s : dsUsers){
                    if(email == s.getEmail()){
                        if(pw != s.getPassWord()){
                            cout<<"Mat khau khong dung !\n";
                            return Person("","","","","","",""); // Sai du lieu / du lieu trong
                        }
                        else{
                            cout<<"Dang nhap thanh cong !\n";

                            // Your Profile
                            ifstream ifs("people.txt");
                            if(ifs.is_open()){
                                string line;
                                while(getline(ifs, line)){
                                    int id;
                                    string name, emailPerson , sex, birthday, address, phoneNumber, role;
                                    char s;
                                    ifs >> s >> id >> s >> s;
                                    getline(ifs, name, ']');
                                    ifs >> s;
                                    getline(ifs, emailPerson, ']');
                                    ifs >> s;
                                    getline(ifs, sex, ']');
                                    ifs >> s;
                                    getline(ifs, birthday, ']');
                                    ifs >> s;
                                    getline(ifs, address, ']');
                                    ifs >> s;
                                    getline(ifs, phoneNumber, ']');
                                    ifs >> s;
                                    getline(ifs, role, ']');

                                    if(emailPerson == email){
                                        ifs.close();
                                        check = true;
                                        cout<<"Welcome "<<name<<" !\n";
                                        return Person(name,emailPerson,sex,birthday,address,phoneNumber,role);
                                    }
                                }
                            }
                            if(!check){
                                ifs.close();
                                return Person("","","","","","",""); // Chua co du lieu trong people.txt
                            }
                        }
                    }
                }
            }   
        }


        //Dang xuat
        Person logout(Person &logOutUser){
            return Person("", "", "", "", "", "", "");
        }
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
            int updateId, updatePersonId, updateBookId, updateEBookId;
            cout<<"Cap nhat thong tin muon sach\n"<<"Nhap ID muon sach, ID nguoi muon, ID sach, ID Ebook: ";
            cin >> updateId >> updatePersonId >> updateBookId >> updateEBookId;
            cin.ignore(); 
            ifstream in;
            in.open("borowInfors.txt", ios::in);
            string tmp;
            vector<string> listBorrowInfors;
            while(getline(in, tmp)){
                int i = 1;
                string id = "";
                while(tmp[i] != ']'){
                    if(isdigit(tmp[i])) id += tmp[i];
                    i++;
                }
                if(stoi(id) != updateId){
                    listBorrowInfors.push_back(tmp);
                }
                else{
                    string update = '[' + to_string(updateId) + ']' + ' ' + '[' + to_string(updatePersonId) + ']' + ' ' + '[' + to_string(updateBookId) + ']' + ' ' + '[' + to_string(updateEBookId) + ']';
                    listBorrowInfors.push_back(update);
                }
            }
            in.close();
            ofstream out;
            out.open("borrowInfors.txt", ios :: out);
            for(string s : listBorrowInfors){
                out<<s<<endl;
            }
            out.close();
        }

        int getId(){
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