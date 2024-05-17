#include <bits/stdc++.h>

using namespace std;

class Person;
class Book;
class EBook;
class User;
class BorrowInfo;

vector<Book> dsBooks;
vector<EBook> dsEBooks;
vector<User> dsUsers;
vector<Person> dsPeople;

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

        int getNextId(){ // nhan id moi khi khoi tao 1 user moi
            if(dsPeople.empty()) return 1;
            else return dsUsers.size() + 1;
        }

    public:
        // Person(){
        //     this->id = autoId();
        //     this->name = "";
        //     this->email = "";
        //     this->sex = "";
        //     this->birthdate = "";
        //     this->address = "";
        //     this->phoneNumber = "";
        //     this->role = "";
        // }

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

        Person(){
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
                    
                    Person P(name, emailPerson , sex, birthday, address, phoneNumber, role);
                    P.setId(id);
                    dsPeople.push_back(P);
                }   
                ifs.close();
            }
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
                if(cnt != x) {
                    find = true;
                    break;
                }
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
        void setId(int id){
            this->id = id;
        }

        // thay doi password
        void updatePW(string newPw){ 
            ifstream ifs;
            ifs.open("users.txt");
            vector<string> listUsers;
            if(ifs.is_open()){
                string line;
                while(getline(ifs,line)){
                    stringstream ss(line);
                    int id;
                    string email, oldpw; 
                    char s ; 
                    ss>>s>>id>>s>>s;
                    getline(ss,email,']');
                    ss>>s;
                    getline(ss,oldpw,']');
                    if(email == this->getEmail()){
                        string data = "["+to_string(id)+"] ["+email+"] ["+newPw+"]";
                        listUsers.push_back(data);
                    }
                    else{
                        string data = "["+to_string(id)+"] ["+email+"] ["+oldpw+"]";
                        listUsers.push_back(data);
                    }
                }
                ifs.close();
            }

            ofstream ofs("users.txt",ios::trunc);
            if(ofs.is_open()){
                for(auto s : listUsers){
                    ofs<<s<<endl;
                }
                ofs.close();
                cout<<"Update thanh cong !\n";
            }
        }

        void updateProfile(){ //Sua thong tin ca nhan
                ifstream ifs; 
                ifs.open("people.txt");
                vector<string> listPerson;
                string old;
                if(ifs.is_open()){
                    string line; 
                    while(getline(ifs, line)){
                        stringstream ss(line);
                        int id;
                        char s;
                        ss>>s>>id>>s;
                        if(this->id != id) listPerson.push_back(line);
                        else old = line;
                    }   
                    ifs.close();
                }
                ofstream ofs("people.txt",ios::trunc);
                for(auto s : listPerson){
                    ofs<<s<<endl;
                }
                ofs.close();
                
                string name, sex, birthday, address, phoneNumber;
                bool update = false;
                cout<<"Thong tin hien tai:\n";
                cout<<old<<endl;
                while(!update){
                    cout<<"Thay doi name(n) - sex(s) - birthday(b) - address(a) - phoneNumber(p) - luu (l)\n";
                    char c; cin>>c; cin.ignore();
                    switch (c){
                        case 'n':
                            cout<<"Ten moi: "; 
                            getline(cin,name);
                            this->name = name;
                            break;
                        case 's':
                            cout<<"Doi gioi tinh: "; 
                            cin>>sex;
                            this->sex = sex;
                            break;
                        case 'b':
                            cout<<"Doi ngay sinh: "; 
                            cin>>birthday;
                            this->birthdate = birthday;
                            break;
                        case 'a':
                            cout<<"Doi dia chi: "; 
                            cin>>address;
                            this->address = address;
                            break;    
                        case 'p':
                            cout<<"Doi sdt: "; 
                            cin>>phoneNumber;
                            this->phoneNumber = phoneNumber;
                            break; 
                        case 'l':
                            update = true;
                            break;
                    }
                }
                if(update){
                    ofstream ofs("people.txt",ios::app);
                    if(ofs.is_open()){
                        ofs<<"["<<this->id<<"] ["<<this->name<<"] ["<<this->email<<"] ["<<this->sex<<"] ["<<this->birthdate<<"] ["<<this->address<<"] ["<<this->phoneNumber<<"] ["<<this->role<<"]"<<endl;
                        ofs.close();
                        cout<<"Update thanh cong !\n";
                    }
                }
                else{
                    ofstream ofs("people.txt",ios::app);
                    if(ofs.is_open()){
                        ofs<<old<<endl;
                        ofs.close();
                        cout<<"Loi update !\n";
                    }
                }
        }

        //Admin sua thong tin cua User
        void updatePerson(int personId){
                ifstream ifs;
                ifs.open("people.txt");
                vector<string> listPerson;
                string old;
                string name , sex, birthday, address, phoneNumber, role;
                if(ifs.is_open()){
                    string line; 
                    while(getline(ifs, line)){
                        stringstream ss(line);
                        int id;
                        char s;
                        ss>>s>>id>>s>>s;
                        if(id != personId) listPerson.push_back(line);
                        else{
                            old = line;
                            getline(ss, name, ']');
                            ss >> s;
                            getline(ss, email, ']');
                            ss >> s;
                            getline(ss, sex, ']');
                            ss >> s;
                            getline(ss, birthday, ']');
                            ss >> s;
                            getline(ss, address, ']');
                            ss >> s;
                            getline(ss, phoneNumber, ']');
                            ss >> s;
                            getline(ss, role, ']');
                        }   
                    }
                    ifs.close();
                }
                ofstream ofs("people.txt",ios::trunc);
                for(auto s : listPerson){
                    ofs<<s<<endl;
                }
                ofs.close();
                
                bool update = false;
                cout<<"Thong tin hien tai:\n";
                cout<<old<<endl;
                while(!update){
                    cout<<"Thay doi name(n) - sex(s) - birthday(b) - address(a) - phoneNumber(p) - role(r) - luu (l)\n";
                    char c; cin>>c; cin.ignore();
                    string data;
                    switch (c){
                        case 'n':
                            cout<<"Ten moi: "; 
                            getline(cin,name);
                           // this->name = name;
                            break;
                        case 's':
                            cout<<"Doi gioi tinh: "; 
                            cin>>sex;
                            //this->sex = sex;
                            break;
                        case 'b':
                            cout<<"Doi ngay sinh: "; 
                            cin>>birthday;
                           // this->birthdate = birthday;
                            break;
                        case 'a':
                            cout<<"Doi dia chi: "; 
                            cin>>address;
                           // this->address = address;
                            break;    
                        case 'p':
                            cout<<"Doi sdt: "; 
                            cin>>phoneNumber;
                            //this->phoneNumber = phoneNumber;
                            break; 
                        case 'r':
                            cout<<"Doi role thanh \"Admin\""; 
                            role = "Admin";
                            break;   
                        case 'l':
                            update = true;
                            break;
                    }
                }
                if(update){
                    ofstream ofs("people.txt",ios::app);
                    if(ofs.is_open()){
                        ofs<<"["<<personId<<"] ["<<name<<"] ["<<email<<"] ["<<sex<<"] ["<<birthday<<"] ["<<address<<"] ["<<phoneNumber<<"] ["<<role<<"]"<<endl;
                        ofs.close();
                        cout<<"Update thanh cong !\n";
                    }
                }
                else{
                    ofstream ofs("people.txt",ios::app);
                    if(ofs.is_open()){
                        ofs<<old<<endl;
                        ofs.close();
                        cout<<"Loi update !\n";
                    }
                }
        }

        //Cap nhat khi nguoi dung tra sach
        void returnBook(int personId, int idBook, int idEbook){
            ifstream in;
            in.open("borrowInfos.txt", ios::in);
            string line; 
            bool check = false;
            vector<vector<int>> listBorrowInfors;
            int cnt = 0; cin.ignore();
            while(getline(in, line)){
                ++cnt;
                stringstream ss(line);
                int id, pId, bId, eId;
                char s;
                ss>>s>>id>>s>>s>>pId>>s>>s>>bId>>s>>s>>eId>>s;
                if(pId != personId || bId != idBook || eId != idEbook){
                    listBorrowInfors.push_back({id,pId,bId,eId});
                }
            }
            in.close();

            ofstream out;
            out.open("borrowInfos.txt", ios :: out);
            for(auto s : listBorrowInfors){
                out<<'['<<s[0]<<"] ["<<s[1]<<"] ["<<s[2]<<"] ["<<s[3]<<"]"<<endl;
            }
            out.close();  
            if(cnt == listBorrowInfors.size()) cout<<"Thong tin tra sach khong dung!\n";
            else cout<<"Sach khong con trong thu vien cua ban!\n";
        }

        //Hien thi all sach da muon cua User
        vector<pair<int,int>> AllBorrowUser(int personId){
            ifstream in;
            in.open("borrowInfos.txt", ios::in);
            vector<pair<int,int>> D;
            if(in.is_open()){
                string line; 
                int cnt = 0; cin.ignore();
                while(getline(in, line)){
                    stringstream ss(line);
                    int id, pId, bId, eId;
                    char s;
                    ss>>s>>id>>s>>s>>pId>>s>>s>>bId>>s>>s>>eId>>s;
                    if(pId == personId){
                        ++cnt;
                        D.push_back({bId,eId});
                    }
                }
                if(cnt == 0){
                    cout<<"Khong tim thay thong tin muon sach !\n"; 
                }
                else{
                    cout<<"Nguoi dung da muon "<<cnt<<" quyen sach.\n";
                }
                in.close();
            }
            return D;
        }

};

class Book{ // thong tin cuon sach
    private:
        int id , qt;
        string title;
        string author;

    public:
        Book(){}

        Book(string title, string author, int qt){
            this->id = autoId();
            this->title = title;
            this->author = author;
            this->qt = qt;
        }
        int autoId(){
            ifstream in;
            in.open("books.txt");
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
                if(cnt != x) {
                    find = true;
                    break;
                }
                cnt ++;
            }
            return cnt;
        }

        // lay ra gia tri
        int getId(){
            return this -> id;
        }
        string getTitle(){
            return this -> title;
        }
        string getAuthor(){
            return this -> author;
        }
        int getQuantity(){
            return this -> qt;
        }
        void setId(int id){
            this->id = id;
        }

};

bool comp(Book &a , Book &b){ // Sap xep theo thu tu id
    return a.getId() < b.getId();
}

class Books{ // Làm vc với books.txt
    private:

        int getNextId(){ 
            if(dsBooks.empty()) return 1;
            else return dsBooks.size() +1;
        }

        bool checkBook(Book &check_Book){
            if(check_Book.getTitle().empty() || check_Book.getAuthor().empty() || check_Book.getQuantity() < 0)
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
                    string tmp;
                    ss >> tmp;
                    id = stoi(tmp.substr(1, tmp.size() - 2));
                    ss >> tmp; 
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        title += tmp+ " ";
                        ss >> tmp;
                    }
                    title += tmp.substr(0, tmp.size() - 1);
                    ss >> tmp;
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        author += tmp+ " ";
                        ss >> tmp;
                    }
                    author += tmp.substr(0, tmp.size() - 1);
                    ss >> tmp;
                    qt =  stoi(tmp.substr(1, tmp.size() - 2));
                    Book B(title, author, qt);
                    B.setId(id);
                    dsBooks.push_back(B);

                }
                
                ifs.close();
            }
        }

        // Them thong tin 1 cuon sach (chi Admin)
        void addBook(Book &add_Book){
            int id = add_Book.autoId();
            cout<<"Sach co id la: "<<id<<endl;
            string title = add_Book.getTitle();
            string author = add_Book.getAuthor();
            int qt = add_Book.getQuantity();
            dsBooks.push_back(add_Book);
            cout<<endl;
            ofstream ofs1("books.txt", ios::app);
            if(ofs1.is_open()){
                ofs1<<"["<<id<<"] ["<<title<<"] ["<<author<<"] ["<<qt<<"]"<<endl;
                ofs1.close();
                cout<<"Ban vua them sach thanh cong !\n";
            }
        }

        void SortDsBooks(){ // Sap xep dsBooks theo id
            sort(dsBooks.begin(), dsBooks.end(),comp);
        }

        // Lay tat ca thong tin sach trong books.txt 
        void getBooks(){
            for(auto s : dsBooks) 
                cout<<s.getId()<<" "<<s.getTitle()<<" "<<s.getAuthor()<<" "<<s.getQuantity()<<endl;
        }

        //Cap nhat thong tin sach theo id (Chi Admin)
        void updateBook(int id){
            int qt;
            string title, author;
            bool check = false;
            for(auto &s : dsBooks){
                if(s.getId() == id){
                    cout<<"Ten sach: ";
                    cin.ignore();
                    getline(cin, title);
                    cout<<"Tac gia: ";
                    getline(cin, author);
                    cout<<"So luong: ";
                    cin >> qt;
                    Book book(title, author, qt);
                    book.setId(id);
                    if(!checkBook(book)){
                        cout<<"Thong tin update chua hop le !\n";
                        check = false;
                    }
                    else{
                        s = book; // cap nhat trong dsBooks
                        check = true;
                    }
                    break;
                }
            }
            if(check){
                ofstream ofs("books.txt",ios::trunc); // mo tep ghi de
                if(ofs.is_open()){
                    for(auto s : dsBooks)
                        ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantity()<<"]"<<endl;

                    ofs.close();
                    cout<<"Da cap nhat thanh cong !\n";
                }    
            }
        }

        //Xoa thong tin 1 cuon sach
        void deleteBook(int id){
            dsBooks.erase(dsBooks.begin() + id-1);
            ofstream ofs("books.txt",ios::trunc); // mo tep ghi de
            if(ofs.is_open()){
                for(auto s : dsBooks)
                    ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantity()<<"]"<<endl;

                ofs.close();
                cout<<"Da xoa thanh cong !\n";
            }  
        }

        //Lay thong tin
        void AllBooks(){
            cout<<"Danh sach tat ca sach: \n";
            cout<<"ID-Ten sach-Tac gia-So luong\n";
            SortDsBooks();
            for(auto x: dsBooks){
                cout<<"["<<x.getId()<<"]-"<<x.getTitle()<<"-"<<x.getAuthor()<<"-"<<x.getQuantity()<<endl;
            }
        }

        void ABook(int id){
            bool check = false;
            for(auto x : dsBooks){
                if(x.getId() == id){
                    cout<<"["<<x.getId()<<"]-"<<x.getTitle()<<"-"<<x.getAuthor()<<"-"<<x.getQuantity()<<endl;
                    check  = true;
                    break;
                }
            }
            if(!check) cout<<"Khong tim thay thong tin sach !\n";
        }
};

class EBook : public Book{ // thong tin eBook 
    private: 
        string fileFormat;
        int fileSize;

    public:
        EBook(){}

        EBook(string title, string author, int qt, string fileFormat, int fileSize):Book(title, author, qt){
            this->fileFormat = fileFormat;
            this->fileSize = fileSize;
        }

        int autoId(){
            ifstream in;
            in.open("ebooks.txt");
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
                if(cnt != x) {
                    find = true;
                    break;
                }
                cnt ++;
            }
            return cnt;
        }


        string getFileFormat(){
            return fileFormat;
        }
        int getFileSize(){
            return fileSize;
        }
        bool comp(EBook &a , EBook &b){ // Sap xep theo thu tu id
            return a.getId() < b.getId();
        }
};

class EBooks{
    private:

        int getNextId(){ 
            if(dsEBooks.empty()) return 1;
            else return dsEBooks.size() +1;
        }

        bool checkBook(EBook &check_Book){
            if(check_Book.getTitle().empty() || check_Book.getAuthor().empty() || check_Book.getQuantity() < 0 || check_Book.getFileFormat().empty() || check_Book.getFileSize() < 0)
                return false;
            return true;
        }
    public:
        EBooks(){
            ifstream ifs("ebooks.txt");
            
            if(ifs.is_open()){
                string line;
                while(getline(ifs,line)){
                    stringstream ss(line);
                    int id, qt, fileSize;
                    string title = "", author = "", fileFormat = ""; 
                    string tmp;
                    ss >> tmp;
                    id = stoi(tmp.substr(1, tmp.size() - 2));
                    ss >> tmp; 
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        title += tmp+ " ";
                        ss >> tmp;
                    }
                    title += tmp.substr(0, tmp.size() - 1);
                    ss >> tmp;
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        author += tmp+ " ";
                        ss >> tmp;
                    }
                    author += tmp.substr(0, tmp.size() - 1);
                    ss >> tmp;
                    qt =  stoi(tmp.substr(1, tmp.size() - 2));
                    ss >> tmp;
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        fileFormat += tmp + " ";
                        ss >> tmp;
                    }
                    fileFormat += tmp.substr(0, tmp.size() - 1);
                    ss >> tmp;
                    fileSize = stoi(tmp.substr(1, tmp.size() - 2));
                    EBook EB(title, author, qt, fileFormat, fileSize);
                    EB.setId(id);
                    dsEBooks.push_back(EB);
                }
                
                ifs.close();
            }
        }

        // Them thong tin 1 cuon sach (chi Admin)
        void addBook(EBook &add_Book){
            int id = add_Book.autoId();
            cout<<"Sach co id la: "<<id<<endl;
            string title = add_Book.getTitle();
            string author = add_Book.getAuthor();
            int qt = add_Book.getQuantity();
            string fileFormat = add_Book.getFileFormat();
            int fileSize = add_Book.getFileSize();
            dsEBooks.push_back(add_Book);
            cout<<endl;
            ofstream ofs1("ebooks.txt", ios::app);
            if(ofs1.is_open()){
                ofs1<<"["<<id<<"] ["<<title<<"] ["<<author<<"] ["<<qt<<"] ["<<fileFormat<<"] ["<<fileSize<<"]"<<endl;
                ofs1.close();
                cout<<"Ban vua them ebook thanh cong !\n";
            }
        }

         //Cap nhat thong tin sach theo id (Chi Admin)
        void updateEBook(int id){
            int qt, fileSize;
            string title, author, fileFormat;
            bool check = false;
            for(auto &s : dsEBooks){
                if(s.getId() == id){
                    cout<<"Ten sach: ";
                    cin.ignore();
                    getline(cin, title);
                    cout<<"Tac gia: ";
                    getline(cin, author);
                    cout<<"So luong: ";
                    cin >> qt;
                    cout<<"File format: ";
                    cin>>fileFormat;
                    cout<<"File size: ";
                    cin>>fileSize;
                    EBook ebook(title, author, qt, fileFormat, fileSize);
                    ebook.setId(id);
                    if(!checkBook(ebook)){
                        cout<<"Thong tin update chua hop le !\n";
                        check = false;
                    }
                    else{
                        s = ebook; // cap nhat trong dsEBooks
                        check = true;
                    }
                    break;
                }
            }
                
            if(check){
                ofstream ofs("ebooks.txt",ios::trunc); // mo tep ghi de
                if(ofs.is_open()){
                    for(auto s : dsEBooks)
                        ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantity()<<"] ["<<s.getFileFormat()<<"] ["<<s.getFileSize()<<"]"<<endl;

                    ofs.close();
                    cout<<"Da cap nhat thanh cong !\n";
                }    
            }
        }

        //Xoa thong tin 1 cuon sach
        void deleteBook(int id){
            dsEBooks.erase(dsEBooks.begin() + id-1);
            ofstream ofs("ebooks.txt",ios::trunc); // mo tep ghi de
            if(ofs.is_open()){
                for(auto s : dsEBooks)
                    ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantity()<<"] ["<<s.getFileFormat()<<"] ["<<s.getFileSize()<<"]"<<endl;

                ofs.close();
                cout<<"Da xoa thanh cong !\n";
            }  
        }

        void SortEBooks(){ // Sap xep dsBooks theo id
            sort(dsEBooks.begin(), dsEBooks.end(),comp);
        }

        void AllBooks(){
            cout<<"Danh sach tat ca Ebook: \n";
            cout<<"ID-Ten sach-Tac gia-So luong-Dang file-Do lon file\n";
            SortEBooks();
            for(auto x: dsEBooks){
                cout<<"["<<x.getId()<<"]-"<<x.getTitle()<<"-"<<x.getAuthor()<<"-";
                cout<<x.getQuantity()<<"-"<< x.getFileFormat()<<"-"<< x.getFileSize()<<endl;
            }
        }

        void ABook(int id){
            bool check = false;
            for(auto x : dsEBooks){
                if(x.getId() == id){
                    cout<<"["<<x.getId()<<"]-"<<x.getTitle()<<"-"<<x.getAuthor()<<"-";
                    cout<<x.getQuantity()<<"-"<<x.getFileFormat()<<"-"<<x.getFileSize()<<endl;
                    check = true;
                    break;
                }
            }
            if(!check) cout<<"Khong tim thay thong tin sach !\n";
    
        }

};


class User{ // thong tin 1 user
    private:
        int id;
        string email, pw;

    public:
        User(){
            this->id = 0;
            this->email = "";
            this->pw = "";
        }
        User(string email, string pw){
            this->id =  autoId();
            this->email = email;
            this->pw = pw;
        }

        int autoId(){
            ifstream in;
            in.open("users.txt");
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
                if(cnt != x) {
                    find = true;
                    break;
                }
                cnt ++;
            }
            return cnt;
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
        
        //Dang xuat
        void logout(bool &check){
            cout<<"Dang xuat thanh cong!\n";
            check = false;
        }
};

class Users{ // Làm vc với users.txt
    private:

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
            while(!checkPassWord(pw)){
                cout<<"Password chua dung dinh dang !\n";
                cout<<"Password can it nhat 8 ki tu\nCan it nhat 1 ki tu in hoa, 1 ki tu in thuong va chu so\n";
                cout<<"Nhap lai password: ";
                cin >> pw;
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
        Person login(bool &check){ 
            // check thong tin dang nhap
            string email;
            cout<<"   Email: ";
            cin >> email;
            for(auto s : dsPeople){
                if(email == s.getEmail() && s.getRole() == "Admin"){
                    check = true;
                    cout<<"Dang nhap thanh cong !\n";
                    cout<<"Welcome "<<s.getName()<<" !\n";
                    return s;
 
                }
            }
            string pw;
            cout<<"Password: ";
            cin>> pw;
            cout<<endl;
            while(1){
                check = false;
                for(auto s : dsUsers){
                    if(email == s.getEmail()){
                        while(pw != s.getPassWord()){
                            cout<<"Mat khau khong dung !\n";
                            cout<<"Hay nhap lai: ";
                            cin>>pw;
                        }
                        if(pw == s.getPassWord()){
                            check = true;
                            break;
                        }
                    }
                }
                if(check){
                    cout<<"Dang nhap thanh cong !\n";
                    for(auto s : dsPeople){
                        if(s.getEmail() == email){
                            cout<<"Welcome "<<s.getName()<<" !\n";
                            return s;
                        }
                    }
                    break;
                }           
                else{
                    cout<<"Sai thong tin dang nhap !\n";
                    cout<<"   Email: ";
                    cin >> email;
                    cout<<"Password: ";
                    cin>> pw;
                }
            }
            Person P;
            return P;
        }

};


class BorrowInfo{
    private:
        int id;
        int personId;
        int bookId;
        int eBookId;
    public:
    BorrowInfo(){}

    BorrowInfo(int personId, int bookId, int eBookId){
        this->id = autoId();
        this->personId = personId;
        this->bookId = bookId;
        this->eBookId = eBookId;
    }
    int autoId(){
        ifstream in;
        in.open("borrowInfos.txt");
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
            if(cnt != x){
                find = true;
                break;
            } 
            cnt ++;
        }
        return cnt;
    }

    //Them thong tin muon sach
    void addInfo(int personId, int bookId, int eBookId){
        int id = autoId();
        ofstream out("borrowInfos.txt", ios::app);
        out<<'['<< id <<']'<<' '<<'['<< personId <<']'<<' '<<'['<< bookId <<']'<<' '<<'['<< eBookId <<']'<<endl;
        out.close();
    }

    //Cap nhat thong tin muon sach
    void updateInfo(int updateId, int updatePersonId, int updateBookId, int updateEBookId){ 
        ifstream in;
        in.open("borrowInfos.txt", ios::in);
        string tmp;
        vector<string> listBorrowInfors;
        bool find = false;
        while(getline(in, tmp)){
            int i = 1;
            stringstream ss(tmp);
            string id;
            ss >> id;
            if(stoi(id.substr(1, id.length() - 2)) != updateId){
                listBorrowInfors.push_back(tmp);
            }
            else{
                find = true;
                string update = '[' + to_string(updateId) + ']' + ' ' + '[' + to_string(updatePersonId) + ']' + ' ' + '[' + to_string(updateBookId) + ']' + ' ' + '[' + to_string(updateEBookId) + ']';
                listBorrowInfors.push_back(update);
            }
        }
        if(!find){
            cout<<"Khong tim thay id muon sach "<< updateId <<endl;
        }
        in.close();
        ofstream out;
        out.open("borrowInfos.txt", ios :: out);
        for(string s : listBorrowInfors){
            out<<s<<endl;
        }
        out.close();
        cout<<"Cap nhat thanh cong !\n";
    }

    //Cap nhat thong tin tra sach
    void updateReturnInfo(int updateBookId){ 
        ifstream in;
        in.open("borrowInfos.txt", ios::in);
        string tmp;
        vector<string> listBorrowInfors;
        bool find = false;
        while(getline(in, tmp)){
            int i = 1;
            string id = "";
            stringstream ss(tmp);
            ss >> id;
            ss >> id;
            ss >> id;
            if(stoi(id.substr(1, id.length() - 2)) != updateBookId){
                listBorrowInfors.push_back(tmp);
            }
            else{
                find = true;
            }
        }
        if(!find){
            cout<<"Khong tim thay id sach duoc tra "<<updateBookId<<endl;
        }
        in.close();
        ofstream out;
        out.open("borrowInfos.txt", ios :: out);
        for(string s : listBorrowInfors){
            out<<s<<endl;
        }
        out.close();
        cout<<"Sach khong con trong thu vien cua ban !\n";
    }

    //Cap nhat thong tin tra sach
    void updateReturnEbook(int updateEBookId){ 
        ifstream in;
        in.open("borrowInfos.txt", ios::in);
        string tmp;
        vector<string> listBorrowInfors;
        bool find = false;
        while(getline(in, tmp)){
            int i = 1;
            string id = "";
            stringstream ss(tmp);
            ss >> id;
            ss >> id;
            ss >> id;
            ss >> id;
            if(stoi(id.substr(1, id.length() - 2)) != updateEBookId){
                listBorrowInfors.push_back(tmp);
            }
            else{
                find = true;
            }
        }
        if(!find){
            cout<<"Khong tim thay id sach duoc tra "<<updateEBookId<<endl;
        }
        in.close();
        ofstream out;
        out.open("borrowInfos.txt", ios :: out);
        for(string s : listBorrowInfors){
            out<<s<<endl;
        }
        out.close();
        cout<<"Sach khong con trong thu vien cua ban !\n";
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

void menu() {
    cout << " === Danh sach chuc nang ===\n";
    cout << " 3. Them sach (chi Admin)\n";
    cout << " 4. Sua thong tin sach (chi Admin)\n";
    cout << " 5. Xoa sach (Chi Admin)\n";
    cout << " 6. Muon sach\n";
    cout << " 7. Tra sach\n";
    cout << " 8. Lay thong tin cac quyen sach \n";
    cout << " 9. Lay thong tin 1 quyen sach co id nam trong file books.txt\n";
    cout << "10. Lay thong tin cac eBook\n";
    cout << "11. Lay thong tin 1 eBook co id nam trong file eBooks.txt\n";
    cout << "12. Hien thi cac cuon sach da muon cua ban than (User)\n";
    cout << "13. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon (Chi Admin)\n";
    cout << "14. Chinh sua thong tin ca nhan  \n";
    cout << "15. Chinh sua thong tin ca nhan cua nguoi khac (Chi Admin)\n";
    cout << "16. Dang xuat\n";
    cout << "17. Thoat chuong trinh\n";
    cout << "-----------------------------------------------------------------------------\n\n";
}

int main() {
    int query ,option;
    User U;
    Users list_users;
    Books list_books;
    list_books.SortDsBooks();
    EBooks list_ebooks;
    list_ebooks.SortEBooks();
    Person P;
    BorrowInfo BI;
    bool success = false;
    while(1){
        cout << "Dang nhap - chon phim 1\n";
        cout << "Dang ki - chon phim 2\n";
        cout << "De thoat chuong trinh - chon 17\n\n";
        cout << "Lua chon cua ban: "; cin>>option;
        cout << endl;

        if(option == 17) return 0;
        else if(option == 2){
            //Dang ki
            string name, email, sex, birthdate, address, phoneNumber, role;
            cin.ignore();
            cout<<"Ten cua ban: ";
            getline(cin, name);
            cout<<"Email: ";
            getline(cin, email);
            cout<<"Gioi tinh: ";
            getline(cin, sex);
            cout<<"Ngay sinh: ";
            getline(cin, birthdate);
            cout<<"Dia chi: ";
            getline(cin, address);
            cout<<"So dien thoai: ";
            getline(cin, phoneNumber);
            role = "User";
            Person P1(name, email, sex, birthdate, address, phoneNumber, role);
            P = P1;
            string password;
            cout<<"Nhap password: ";
            cin >> password;
            list_users.Register(P, password);
        }
        else if(option == 1){
            //Dang nhap  
            P = list_users.login(success);

            if(!success) continue;
            else{
                menu();
                bool in = true;
                while(in){
                    
                    cout<<"Nhap tinh nang muon su dung: ";
                    cin >> query;
                    
                    if(query == 3){
                        //Them sach 
                        if(P.getRole() != "Admin"){
                            cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        int id , qt, fileSize;
                        string title, author, fileFormat;
                        char c;
                        cout<<"Ban muon muon sach (b) hay ebook (e) ?\n";
                        cout<<"Chon: "; cin>>c;
                        if(c == 'b'){
                            cout<<"Ten sach: ";
                            cin.ignore();
                            getline(cin, title);
                            cout<<"Tac gia: ";
                            getline(cin, author);
                            cout<<"So luong: ";
                            cin >> qt;
                            Book book(title, author, qt);
                            list_books.addBook(book);  
                        }          
                        else if(c == 'e'){
                            cout<<"Ten sach: ";
                            cin.ignore();
                            getline(cin, title);
                            cout<<"Tac gia: ";
                            getline(cin, author);
                            cout<<"So luong: ";
                            cin >> qt;
                            cout<<"File format: ";
                            cin>>fileFormat;
                            cout<<"File size: ";
                            cin>>fileSize;
                            EBook ebook(title, author, qt, fileFormat, fileSize) ;
                            list_ebooks.addBook(ebook); 
                        }
                    }
                    else if(query == 4){
                        // sua thong tin sach
                        if(P.getRole() != "Admin"){
                            cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        int id;
                        char c;
                        cout<<"Ban muon sua sach (b) hay ebook (e) ?\n";
                        cout<<"Chon: "; cin>>c;
                        if(c == 'e'){
                            cout<<"Nhap thong tin sach can update:\n";
                            cout<<"Nhap ID sach: ";
                            cin >> id;
                            cout<<"Thong tin sach hien tai: \n";
                            list_ebooks.ABook(id);
                            list_ebooks.updateEBook(id);
                        }
                        else if(c == 'b'){
                            cout<<"Nhap thong tin sach can update:\n";
                            cout<<"Nhap ID sach: ";
                            cin >> id;
                            cout<<"Thong tin sach hien tai: \n";
                            list_books.ABook(id);
                            list_books.updateBook(id);  
                        }          
                    }
                    else if(query == 5){
                        //delete book
                        if(P.getRole() != "Admin"){
                            cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        char c;
                        int id;
                        cout<<"Ban muon sua sach (b) hay ebook (e) ?\n";
                        cout<<"Chon: "; cin>>c;
                        if(c == 'b'){
                            cout<<"Nhap ID sach can xoa: ";
                            cin >> id;
                            list_books.deleteBook(id);  
                        }
                        else if(c == 'e'){
                            cout<<"Nhap ID ebook can xoa: ";
                            cin >> id;
                            list_ebooks.deleteBook(id);
                        }
                    }
                    else if(query == 6){
                        //Muon sach
                        if(P.getRole() != "User"){
                            cout<<"Chi user moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        char c; int idBook;
                        cout<<"Ban muon muon sach (b) hay ebook (e) ?\n";
                        cout<<"Chon: "; cin>>c;
                        if(c == 'b'){
                            cout<<"Nhap ID sach can muon: ";
                            cin >> idBook;
                            list_books.ABook(idBook);
                            cout<<"Ban co chac chan muon muon cuon sach nay ?\n";
                            cout<<"Nhap \'y\' (co) - \'n\' (khong): ";
                            cin>>c;
                            if(c == 'y'){
                                int personId = P.getId();
                                BI.addInfo(personId,idBook,-1);
                                cout<<"Sach da trong thu vien cua ban !\n";
                            }
                            else continue;
                        }
                        else{
                            cout<<"Nhap ID sach can muon: ";
                            cin >> idBook;
                            list_ebooks.ABook(idBook);
                            cout<<"Ban co chac chan muon muon cuon sach nay ?\n";
                            cout<<"Nhap \'y\' (co) - \'n\' (khong): ";
                            cin>>c;
                            if(c == 'y'){
                                int personId = P.getId();
                                BI.addInfo(personId,-1,idBook);
                                cout<<"Sach da trong thu vien cua ban !\n";
                            }
                            else continue;
                        }                    
                    }
                    else if(query == 7){
                        //Tra sach
                        if(P.getRole() != "User"){
                            cout<<"Chi user moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        char c; int idBook;
                        cout<<"Ban tra sach (b) hay ebook (e) ?\n";
                        cout<<"Chon: "; cin>>c;
                        if(c == 'b'){
                            cout<<"Nhap ID sach muon tra: ";
                            cin >> idBook;
                            list_books.ABook(idBook);
                            cout<<"Ban co chac chan muon tra cuon sach nay ?\n";
                            cout<<"Nhap \'y\' (co) - \'n\' (khong): ";
                            cin>>c;
                            if(c == 'y'){
                                int personId = P.getId();
                                //BI.updateReturnInfo(idBook);        //} hai cach nay deu dung
                                P.returnBook(personId,idBook,-1);     //}
                            }
                            else continue;
                        }
                        else{
                            cout<<"Nhap ID sach muon tra: ";
                            cin >> idBook;
                            list_ebooks.ABook(idBook);
                            cout<<"Ban co chac chan muon tra cuon sach nay ?\n";
                            cout<<"Nhap \'y\' (co) - \'n\' (khong): ";
                            cin>>c;
                            if(c == 'y'){
                                int personId = P.getId();
                                //BI.updateReturnEbook(idBook);
                                P.returnBook(personId,-1,idBook);
                            }
                            else continue;
                        }                  
                    }
                    else if(query == 8){
                        // Thong tin tat ca sach
                        list_books.AllBooks();
                    }
                    else if(query == 9){
                        // Thong tin 1 quyen sach theo id
                        int idBook;
                        cout<<"Nhap Id quyen sach ban muon tim: ";
                        cin>>idBook;
                        list_books.ABook(idBook);
                    }
                    else if(query == 10){
                        //Thong tin tat ca ebook
                        list_ebooks.AllBooks();
                    }
                    else if(query == 11){
                        //Thong tin 1 ebook
                        int idBook;
                        cout<<"Nhap Id quyen sach ban muon tim: ";
                        cin>>idBook;
                        list_ebooks.ABook(idBook);
                    }
                    else if(query == 12){
                        // hien thi all sach da muon cua ban than (user)
                        if(P.getRole() != "User"){
                            cout<<"Chi user moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        int personId = P.getId();
                        vector<pair<int,int>> D = P.AllBorrowUser(personId);
                        for(pair<int,int> s : D){
                            if(s.first > 0 && s.second == -1) list_books.ABook(s.first);
                            else if(s.first == -1 && s.second > 0) list_ebooks.ABook(s.second);
                        }
                    }
                    else if(query == 13){
                        //hien thi all sach da muon cua nguoi dung (admin)
                        if(P.getRole() != "Admin"){
                            cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        int personId ;
                        cout<<"Nhap id nguoi dung ban muon xem: ";
                        cin>>personId; 
                        vector<pair<int,int>> D = P.AllBorrowUser(personId);
                        for(pair<int,int> s : D){
                            if(s.first >0 && s.second == -1) list_books.ABook(s.first);
                            else if(s.first == -1 && s.second > 0) list_ebooks.ABook(s.second);
                        }
                    }
                    else if(query == 14){
                        //Chinh sua thong tin ca nhan
                        cout<<"Thay doi mat khau - 1\n";
                        cout<<"Thay doi your profile - 2\n";
                        int c; cin>>c;
                        if(c == 1){
                            string newPw;
                            cout<<"Nhap mat khau moi: ";
                            cin>>newPw;
                            while(!list_users.checkPassWord(newPw)){
                                cout<<"Password chua dung dinh dang !\n";
                                cout<<"Password can it nhat 8 ki tu\nCan it nhat 1 ki tu in hoa, 1 ki tu in thuong va chu so\n";
                                cout<<"Nhap lai password moi: ";
                                cin >> newPw;
                            }
                            P.updatePW(newPw);
                        }
                        else if(c == 2){
                           P.updateProfile();
                        }
                    }
                    else if(query == 15){
                        //Chinh sua thong tin ca nhan cua nguoi khac (chi admin)
                        if(P.getRole() != "Admin"){
                            cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                            continue;
                        }
                        int personId;
                        cout<<"Nhap id cua nguoi dung ban muon sua thong tin: ";
                        cin>>personId;
                        P.updatePerson(personId);
                    }
                    else if(query == 16){
                        //dang xuat
                        U.logout(in);
                    }
                    else if(query == 17){
                        //Thoat chuong trinh
                        return 0;
                    }
                    else {
                        cout<<"Khong co chuc nang trong danh sach!\n";
                        continue;
                    }
                }
            }
        }
    }
    return 0;
}