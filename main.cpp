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
        this->id = createId();
        chuanHoa();
    }
    int createId(){
        ifstream in;
        in.open("people.txt");
        map<int,bool> used ; 
        string line;
        while( getline( in, line ) ){
            string id = "";
            for( int i = 1 ; i < line.size() ; i ++ ){
                if ( line[ i ] == ']' )break ; 
                if( isdigit( line[ i ] ) )id.push_back( line[ i ] );
            }
            used[ stoi(id) ] = true ; 
        }
        in.close();
        int cnt = 0;
        for( auto x : used ){
            if ( x.first != cnt + 1 )return cnt + 1 ; 
            cnt = x.first; 
        }
        return cnt + 1 ; 
    }
    void addInfo(){ // write into people.txt
        ofstream out("people.txt", ios::app); 
        out << '[' << this->id << ']' << " " << '[' << this->name << ']' << " " << '[' << this->email << "]" << " " << '[' << this->sex << ']' << " " << '[' << this->birthdate << ']' << " " << '[' << this->address << ']' << " " << '[' << this->phoneNumber << ']' << " " << '[' << this->role << ']' << endl;
        out.close();
    }
    void chuanHoa(){
        // chuan hoa ten 
        stringstream ss ( this->name );
        string tmp;
        string res="";
        while( ss >> tmp ){
            for( auto &x : tmp ) x = tolower( x );
            tmp[ 0 ] = toupper( tmp[ 0 ] );
            res += tmp + " ";
        }
        res.pop_back();
        this->name = res ; 
        // chuan hoa ngay sinh
        if(this->birthdate[ 1 ] == '/') this->birthdate = "0" + this->birthdate;
        if(this->birthdate[ 4 ] == '/') this->birthdate.insert( 3 , "0" ); 
        // chuan hoa sex 
        for( auto &x : this->sex )x = tolower( x );
        this->sex[ 0 ] = toupper( this->sex[ 0 ] );
        // chuan hoa role
        for( auto &x : this->role )x = tolower( x );
        this->role[ 0 ] = toupper( this->role[ 0 ] );
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
        this->id = createId() ;
    }
    int createId(){
        ifstream in;
        in.open("borrowInfos.txt");
        map<int,bool> used ; 
        string line;
        while( getline( in, line ) ){
            string id = "";
            for( int i = 1 ; i < line.size() ; i ++ ){
                if ( line[ i ] == ']' )break ; 
                if( isdigit( line[ i ] ) )id.push_back( line[ i ] );
            }
            used[ stoi(id) ] = true ; 
        }
        in.close();
        int cnt = 0;
        for( auto x : used ){
            if ( x.first != cnt + 1 )return cnt + 1 ; 
            cnt = x.first; 
        }
        return cnt + 1 ; 
    }
    void addInfo(){// write into borrowInfos.txt
        ofstream out("borrowInfos.txt", ios::app) ; 
        out << '[' << this->id << ']' << " " << '[' << this->personId << ']' << " " << '[' << this->bookId << "]" << " " << '[' << this->eBookId << ']' << endl;
        out.close();
    }
    bool checkBook(){
        if ( this->bookId == -1 )return true ; 
        ifstream in;
        in.open("books.txt");
        string line;
        while( getline( in, line ) ){
            string id = "";
            for( int i = 1 ; i < line.size() ; i ++ ){
                if ( line[ i ] == ']' )break ; 
                if( isdigit( line[ i ] ) )id.push_back( line[ i ] );
            }
            if ( stoi( id ) == this->bookId )return true ; 
        }
        in.close();
        return false ; 
    }
    bool checkEbook(){
        if ( this->eBookId == -1 )return true ; 
        ifstream in;
        in.open("ebooks.txt");
        string line;
        while( getline( in, line ) ){
            string id = "";
            for( int i = 1 ; i < line.size() ; i ++ ){
                if ( line[ i ] == ']' )break ; 
                if( isdigit( line[ i ] ) )id.push_back( line[ i ] );
            }
            if ( stoi( id ) == this->eBookId )return true ; 
        }
        in.close();
        return false ;
    }
    bool checkInfo(){
        return !( this->bookId == -1 and this->eBookId == -1 ) and checkBook() and checkEbook();
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

class Books{ // class chua nhung thuoc tinh theo yeu cau

    private:

        vector<BookInfor> dsBooks ;

        int getNextId(){
            if(dsBooks.empty())  return 1;
            return dsBooks.size() + 1;
        }

        bool checkBook(BookInfor &Books){
            if(Books.getTitle().empty() || Books.getAuthor().empty() || Books.getQuantity() <= 0)
                return false;
            return true;
        }

    public:

        Books(){
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

        void AddBook(BookInfor &Books){ // chi user co tai khoan admin moi su dung duoc
            if(!checkBook(Books)){
                cout << "thong tin sach con thieu! \n";
                return;
            }
            else{
                int id = getNextId();
                string title = Books.getTitle();
                string author = Books.getAuthor();
                int quantity = Books.getQuantity();
                dsBooks.push_back(BookInfor(id, title, author, quantity)); // them data vao vector
                ofstream ofs("books.txt", ios::app) ; 
                if(ofs.is_open()){
                    ofs << '[' << id << ']' << ' ' << '[' << title << ']' << ' ' << '[' << author << ']' << ' ' << '[' << quantity << ']' << endl;
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
                if(ofs.is_open()){ // cap nhat lai trong file Books.txt
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
                if(ofs.is_open()){ // cap nhat lai trong file Books.txt
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

        void regist(Person info, string password){ // check thong tin dang ki
            if(!checkUser(UserInfos(0, info.getEmail(), password))) cout << "thong tin sai!\n";
            else{
                int id = getNextId();
                dsUsers.push_back(UserInfos(id, info.getEmail(), password)); // add them vao vector
                ofstream ofs("users.txt");
                if(ofs.is_open()){
                    for(auto &x : dsUsers) // cap nhat lai file txt
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getEmail() << ']' << ' ' << '[' << x.getPassword() << ']' << endl;
                    cout << "dang ki thanh cong!\n";
                    cout << "hay dang nhap bang email cua ban!\n";
                    ofs.close();
                    info.addInfo();
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

// khai bao cac bien he thong
Users acesstUsers; // class he thong => khai bao 1 lan
Books acesstUsersBooks;
Person infoUser("", "", "", "", "", "", "");
bool checkInfoUser; // check xem dang nhap thanh cong khong?
char option; // cac thao tac khi dang nhap thanh cong



// funtion chuc nang

void Login(){
    checkInfoUser = false;
    // infoUser = Person("", "", "", "", "", "", ""); // moi khi dang nhap lai tu dau
    string email, password;
    cout << "nhap email:\n";
    cin >> email;
    cout << "nhap password:\n";
    cin >> password;
    infoUser = acesstUsers.login(email, password);
    if(infoUser.getEmail().empty()){ // chua dang ki
        cout << "dang nhap that bai!\n";
        cout << "vui long dang ki tai khoan!\n";
    }
    else{
        cout << "Welcome \n" << infoUser.getName() << endl;
        checkInfoUser = true;
    }
}

int main()
{

    // freopen("output.txt", "w", stdout);

    while(1){
        cout << "dang nhap - bam \"a\"\n";
        cout << "dang ki - bam \"b\"\n";
        cout << "thoat chuong trinh - bam \"r\"\n";
        cin >> option;
        if(option == 'r') return 0;
        if(option == 'b'){
            // code thu tuc dang ki
        }
        if(option == 'a'){
            Login();
            while(checkInfoUser){
                cout << "CHON CAC CHUC NANG:\n";
                cout << "bam \"c\" de them sach - quyen cua admin\n";
                cout << "bam \"d\" de sua thong tin sach - quyen cua admin\n";
                cout << "bam \"e\" de xoa sach - quyen cua admin\n";
                cout << "bam \"f\" de muon sach\n";
                cout << "bam \"g\" de tra sach\n";
                cout << "bam \"h\" de hien thi tat ca sach\n";
                cout << "bam \"i\" de lay thong tin cuon sach trong Books\n";
                cout << "bam \"j\" de hien thi tat ca sach trong Ebooks\n";
                cout << "bam \"k\" de lay thong tin cuon sach trong Ebooks\n";
                cout << "bam \"m\" de hien thi tat ca sach ban da muon\n";
                cout << "bam \"n\" de hien thi tat ca sach cua mot nguoi - quyen cua admin\n";
                cout << "bam \"o\" de chinh sua thong tin ca nhan cua ban\n";
                cout << "bam \"p\" de chinh sua thong tin ca nhan cua mot nguoi - quyen cua admin\n";
                cout << "bam \"q\" de dang suat\n";
                cout << "bam \"r\" de thoat chuong trinh\n";
                cout << endl;
                cin >> option;
                if(option == 'r') return 0; // dang ki
                if(option == 'q') break; // dang xuat
                // if(option == 'c')
                // if(option == 'd')
                // if(option == 'e')
                // if(option == 'f')
                // if(option == 'g')
                // if(option == 'h')
                // if(option == 'i')
                // if(option == 'j')
                // if(option == 'k')
                // if(option == 'm')
                // if(option == 'n')
                // if(option == 'o')
                // if(option == 'p')
            }
        }
    }
    

    // Books test1;
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