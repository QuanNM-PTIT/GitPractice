#include <bits/stdc++.h>

using namespace std;

class Person{
    private:
    int id ; 
    string name , email , sex , birthdate, address, phoneNumber, role;
    public:
    Person( string name , string email , string sex ,string birthdate,string address,string phoneNumber,string role = "User", int id = 0){
        this->name = name ;
        this->email = email;
        this->sex = sex ;
        this-> birthdate = birthdate; 
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = role;
        if( id )this->id = id ; 
        else this->id = createId();
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

    Person getInforPeople(int idCheck){
        ifstream ifs("people.txt");
        if(ifs.is_open()){
            string line;
            while(getline(ifs, line)){
                int id;
                string name, email, sex, birthday, address, phone, role;
                char c;
                stringstream ss(line);
                ss >> c >> id >> c >> c;
                getline(ss, name, ']');
                ss >> c;
                getline(ss, email, ']');
                ss >> c;
                getline(ss, sex, ']');
                ss >> c;
                getline(ss, birthdate, ']');
                ss >> c;
                getline(ss, address, ']');
                ss >> c;
                getline(ss, phone, ']');
                ss >> c;
                getline(ss, role, ']');
                if(id == idCheck) return Person(name, email, sex, birthdate, address, phone, role, id);
            }
            ifs.close();
            return Person("", "", "", "", "", "", "");
        }
        else{
            cout << "loi truy cap data!\n";
            return Person("", "", "", "", "", "", "");
        }
    }

    void addInfo(){ // write into people.txt
        ofstream out("people.txt", ios::app); 
        out << '[' << this->id << ']' << " " << '[' << this->name << ']' << " " << '[' << this->email << "]" << " " << '[' << this->sex << ']' << " " << '[' << this->birthdate << ']' << " " << '[' << this->address << ']' << " " << '[' << this->phoneNumber << ']' << " " << '[' << this->role << ']' << endl;
        out.close();
    }
    void deleteInfo(){
        ifstream in ;
        in.open("people.txt");
        vector<string> data;
        string line;
        while( getline(in , line) ){
            stringstream ss( line );
            int oldId;
            char c ; 
            ss >> c >> oldId;
            if ( this->id != oldId )data.push_back( line );
        }
        in.close();
        ofstream out;
        out.open("people.txt", ios::trunc);
        for( auto x : data ){
            out << x << endl;
        }
        out.close();
    }
    void chuanHoa(){
        // chuan hoa ten
        stringstream ss( this->name );
        string tmp ;
        this->name = "";
        while( ss >> tmp ){
            for( auto &x : tmp ) x = tolower( x );
            tmp[ 0 ] = toupper( tmp[ 0 ] );
            this->name += tmp + " ";
        }
        this->name.pop_back();
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
    void giveBookback( int bookId ){
        ifstream in ;
        in.open("borrowInfos.txt");
        vector<vector<int>> data;
        string line;
        int cnt = 0;// dem so dong
        cin.ignore();
        while( getline(in , line) ){
            cnt ++; 
            stringstream ss( line );
            int id, person_Id, book_Id, eBook_Id;
            char c;
            ss >> c >> id >> c >> c >> person_Id >> c >> c >> book_Id >> c >> c >> eBook_Id;
            if( bookId != book_Id or person_Id != this->id )data.push_back( { id, person_Id, book_Id, eBook_Id } );
        }
        in.close();
        ofstream out;
        out.open("borrowInfos.txt", ios::trunc);
        for( auto x : data ){
            out << '[' << x[ 0 ] << ']' << " " << '[' << x[ 1 ] << ']' << " " << '[' << x[ 2 ] << "]" << " " << '[' << x[ 3 ] << ']' << endl;
        }
        out.close();
        if( cnt == data.size() )cout << "khong tim thay thong tin!\n";
        else cout << "tra sach thanh cong!\n";
    }
    void giveEbookback( int ebookId ){
        ifstream in ;
        in.open("borrowInfos.txt");
        vector<vector<int>> data;
        string line;
        int cnt = 0;// dem so dong
        cin.ignore();
        while( getline(in , line) ){
            cnt ++ ; 
            stringstream ss( line );
            int id, person_Id, book_Id, eBook_Id;
            char c;
            ss >> c >> id >> c >> c >> person_Id >> c >> c >> book_Id >> c >> c >> eBook_Id;
            if( ebookId != eBook_Id or person_Id != this->id )data.push_back( { id, person_Id, book_Id, eBook_Id } );
        }
        in.close();
        ofstream out;
        out.open("borrowInfos.txt", ios::trunc);
        for( auto x : data ){
            out << '[' << x[ 0 ] << ']' << " " << '[' << x[ 1 ] << ']' << " " << '[' << x[ 2 ] << "]" << " " << '[' << x[ 3 ] << ']' << endl;
        }
        out.close();
        if( cnt == data.size() )cout << "khong tim thay thong tin!\n";
        else cout << "tra ebook thanh cong!\n";
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
    void setName( string name ){
        // sua name trong people.txt
        this->deleteInfo();
        this->name = name;
        this->chuanHoa();
        this->addInfo();
    }
    void setEmail( string newEmail ){
        // sua email trong user.txt
        ifstream in;
        in.open("users.txt");
        string line;
        vector<vector<string>> data;
        while( getline( in, line ) ){
            string oldEmail , oldPassword , userId;
            char c;
            for( auto &x : line )if ( x == '[' or x == ']' )x = ' ';
            stringstream ss ( line );
            ss >> userId >> oldEmail >> oldPassword;
            if ( oldEmail == this->email )data.push_back( { userId, newEmail, oldPassword } );
            else data.push_back( { userId, oldEmail, oldPassword } );
        }
        in.close();
        ofstream out;
        out.open("users.txt", ios::trunc);
        for( auto x : data ){
            out << '[' << x[ 0 ] << ']' << " " << '[' << x[ 1 ] << ']' << " " << '[' << x[ 2 ] << ']' << endl;
        }
        out.close();
        // sua email trong people.txt
        this->deleteInfo();
        this->email = newEmail;
        this->addInfo();
    }
    void setPassword( string newPassword ){
        // sua password trong user.txt
        ifstream in;
        in.open("users.txt");
        string line;
        vector<vector<string>> data;
        while( getline( in, line ) ){
            string oldEmail , oldPassword , userId;
            for( auto &x : line )if ( x == '[' or x == ']' )x = ' ';
            stringstream ss ( line );
            ss >> userId >> oldEmail >> oldPassword;
            if ( oldEmail == this->email )data.push_back( { userId, oldEmail, newPassword } );
            else data.push_back( { userId, oldEmail, oldPassword } );
        }
        in.close();
        ofstream out;
        out.open("users.txt", ios::trunc);
        for( auto x : data ){
            out << '[' << x[ 0 ] << ']' << " " << '[' << x[ 1 ] << ']' << " " << '[' << x[ 2 ] << ']' << endl;
        }
        out.close();
    }
    void setSex( string sex ){
        //sua sex trong people.txt
        this->deleteInfo();
        this->sex = sex;
        this->chuanHoa();
        this->addInfo();
    }
    void setBirthdate( string birthdate ){
        //sua birthdate trong people.txt
        this->deleteInfo();
        this->birthdate = birthdate;
        this->chuanHoa();
        this->addInfo();
    }
    void setAddress( string address ){
        //sua address trong people.txt
        this->deleteInfo();
        this->address = address;
        this->addInfo();
    }
    void setPhoneNumber( string phoneNumber ){
        //sua phoneNumber trong people.txt
        this->deleteInfo();
        this->phoneNumber = phoneNumber;
        this->addInfo();
    }
    void setRole(string newRole){
        // sua role trong people
        this -> deleteInfo();
        this -> role = newRole;
        this -> addInfo();
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
 
bool cmp(BookInfor a, BookInfor b){ // sap xep theo thu tu tu be den lon
    return a.getId() < b.getId();
}

class Books{ // class chua nhung thuoc tinh theo yeu cau

    private:

        vector<BookInfor> dsBooks;


        int getNextId(){
            if(dsBooks.empty()) return 1;
            return dsBooks[dsBooks.size() - 1].getId() + 1;
        }

        bool checkBook(BookInfor &Bookcheck){
            if(Bookcheck.getTitle().empty() || Bookcheck.getAuthor().empty() || Bookcheck.getQuantity() <= 0)
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
                sort(dsBooks.begin(), dsBooks.end(), cmp);
            }
        }

        bool checkIdBook(int id){
            for(int i = 0; i < dsBooks.size(); i ++){
                if(dsBooks[i].getId() == id) return true;
            }
            return false;
        }

        void Sx_dsBooks(){
            sort(dsBooks.begin(), dsBooks.end(), cmp);
        }

        void AddBook(BookInfor &addBook){ // chi user co tai khoan admin moi su dung duoc
            if(!checkBook(addBook)){
                cout << "thong tin sach con thieu! \n";
                return;
            }
            else{
                int id = getNextId();
                string title = addBook.getTitle();
                string author = addBook.getAuthor();
                int quantity = addBook.getQuantity();
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

        void getAllBooks(){ // in ra thong tin cua tat ca sach co trong thu vien
            for(auto x : dsBooks)
                cout << x.getId() << ' ' << x.getTitle() << ' ' << x.getAuthor() << ' ' << x.getQuantity() << '\n';
        }

        void getBook(int id){ // in ra thong tin cua 1 cuon sach
            if(checkIdBook(id)){
                for(auto x : dsBooks){
                    if(x.getId() == id){
                        cout << x.getId() << ' ' << x.getTitle() << ' ' << x.getAuthor() << ' ' << x.getQuantity() << '\n';
                        return;
                    }
                }
            }
            else cout << "khong co cuon sach ban can!\n";
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


class EbookInfor : public BookInfor{
    private:
         
        string fileFormat;
        int fileSize;

    public:

        EbookInfor(int id, string title, string author, int quantity, string fileFormat, int fileSize)
        : BookInfor(id, title, author, quantity), fileFormat(fileFormat), fileSize(fileSize) {}

        string getFileFormat() {return fileFormat;}
        int getFileSize() {return fileSize;}

};

bool cmp2(EbookInfor a, EbookInfor b){ // sap xep theo thu tu tu be den lon
    return a.getId() < b.getId();
}

class Ebooks{

    private:

        vector<EbookInfor> dsEbooks;

        int getNextId(){
            if(dsEbooks.empty()) return 1;
            return dsEbooks[dsEbooks.size() - 1].getId() + 1;
        }

        bool checkBook(EbookInfor &Bookcheck){
            if(Bookcheck.getTitle().empty() || Bookcheck.getAuthor().empty() || Bookcheck.getQuantity() <= 0 || Bookcheck.getFileFormat().empty() || Bookcheck.getFileSize() <= 0)
                return false;
            return true;
        }

    public:

        Ebooks(){
            ifstream ifs("ebooks.txt");
            if(ifs.is_open()){
                string line;
                while(getline(ifs, line)){
                    stringstream ss(line);
                    int id, quantity;
                    string title, author;
                    string fileFormat;
                    int fileSize;
                    char c;
                    ss >> c >> id >> c >> c; 
                    getline(ss, title, ']'); 
                    ss >> c;
                    getline(ss, author, ']');
                    ss >> c >> quantity >> c >> c;
                    getline(ss, fileFormat, ']');
                    ss >> c >> fileSize >> c;
                    dsEbooks.push_back(EbookInfor(id, title, author, quantity, fileFormat, fileSize));
                }
                ifs.close();
                sort(dsEbooks.begin(), dsEbooks.end(), cmp2);
            }
        }

        bool checkIdEbook(int id){
            for(int i = 0; i < dsEbooks.size(); i ++){
                if(dsEbooks[i].getId() == id) return true;
            }
            return false;
        }

        void AddBook(EbookInfor &addBook){ // chi user co tai khoan admin moi su dung duoc
            if(!checkBook(addBook)){
                cout << "thong tin sach con thieu! \n";
                return;
            }
            else{
                int id = getNextId();
                string title = addBook.getTitle();
                string author = addBook.getAuthor();
                int quantity = addBook.getQuantity();
                string fileFormat = addBook.getFileFormat();
                int fileSize = addBook.getFileSize();
                dsEbooks.push_back(EbookInfor(id, title, author, quantity, fileFormat, fileSize)); // them data vao vector
                ofstream ofs("ebooks.txt");
                if(ofs.is_open()){
                    for(auto x : dsEbooks)
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getTitle() << ']' << ' ' << '[' << x.getAuthor() << ']' << ' ' << '[' << x.getQuantity() << ']' << ' ' << '[' << x.getFileFormat() << ']' << ' ' << '[' << x.getFileSize() << ']' << endl;
                    ofs.close();
                    cout << "sach duoc them vao thanh cong!\n";
                } 
                else cout << "loi khi khong truy cap duoc vao data!\n";
            }
        }

        void getAllBooks(){ // in ra thong tin cua tat ca sach co trong thu vien
            for(auto x : dsEbooks)
                cout << x.getId() << ' ' << x.getTitle() << ' ' << x.getAuthor() << ' ' << x.getQuantity() << ' ' << x.getFileFormat() << ' ' << x.getFileSize() << '\n';
        }

        void getBook(int id){ // in ra thong tin cua 1 cuon sach
            if(checkIdEbook(id)){
                for(auto x : dsEbooks){
                    if(x.getId() == id){
                        cout << x.getId() << ' ' << x.getTitle() << ' ' << x.getAuthor() << ' ' << x.getQuantity() << ' ' << x.getFileFormat() << ' ' << x.getFileSize() << '\n';
                        return;
                    }
                }
            }
            else cout << "khong co cuon sach ban can!\n";
        }

        void updateBook(EbookInfor &bookUpdate){ // update theo id cua sach
            bool check = false;
            for(auto &x : dsEbooks){
                if(x.getId() == bookUpdate.getId()){
                    check = true;
                    if(!checkBook(bookUpdate)) cout << "thong tin update khong hop le\n";
                    else x = bookUpdate; // cap nhat trong vector dsEbooks
                    break;
                }
            }
            if(!check) cout << "khong tim thay thong tin!\n";
            else{
                ofstream ofs("ebooks.txt", ios::trunc); // mo tep trong che đo ghi đe
                if(ofs.is_open()){ // cap nhat lai trong file Ebooks.txt
                    for(auto x : dsEbooks)
                        cout << x.getId() << ' ' << x.getTitle() << ' ' << x.getAuthor() << ' ' << x.getQuantity() << ' ' << x.getFileFormat() << ' ' << x.getFileSize() << '\n';
                    cout << "update thanh cong!\n";
                }
                else cout << "loi khi khong truy cap duoc vao data.\n";
            }
        }

        void deleteBook(int id){
            bool check = false;
            for(int i = 0; i < dsEbooks.size(); i ++){
                if(dsEbooks[i].getId() == id){
                    check = true;
                    dsEbooks.erase(dsEbooks.begin() + i); // xoa data tren vector dsBooks
                    break;
                }
            }
            if(!check) cout << "khong tim thay thong tin!\n";
            else{
                ofstream ofs("ebooks.txt", ios::trunc); // mo tep trong che đo ghi đe
                if(ofs.is_open()){ // cap nhat lai trong file Books.txt
                    for(auto x : dsEbooks)
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getTitle() << ']' << ' ' << '[' << x.getAuthor() << ']' << ' ' << '[' << x.getQuantity() << ']' << ' ' << '[' << x.getFileFormat() << ']' << ' ' << '[' << x.getFileSize() << ']' << endl;
                    ofs.close();
                    cout << "delete thanh cong!\n";
                }
                else cout << "loi khi khong truy cap duoc vao data.\n";
            }
        }
};


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

        bool checkInfor(string email, string password){
            for(auto x : dsUsers){
                if(email == x.getEmail() && password == x.getPassword()) return true;
            }
            return false;
        }

        void updateUser(UserInfos &UserUpdate){
            bool check = false;
            for(auto &x : dsUsers){
                if(x.getId() == UserUpdate.getId()){
                    check = true;
                    if(!checkUser(UserUpdate)) cout << "thong tin update khong hop le\n";
                    else x = UserUpdate; // cap nhat trong vector dsUsers
                    break;
                }
            }
            if(!check) cout << "khong tim thay thong tin!\n";
            else{
                ofstream ofs("users.txt", ios::trunc); // mo tep trong che đo ghi đe
                if(ofs.is_open()){ // cap nhat lai trong file users.txt
                    for(auto x : dsUsers)
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getEmail() << ']' << ' ' << '[' << x.getPassword() << ']' << endl;
                    ofs.close();
                    cout << "update thanh cong!\n";
                }
                else cout << "loi khi khong truy cap duoc vao data.\n";
            }
        }

        void regist(Person info, string password){ // check thong tin dang ki
            if(!checkUser(UserInfos(0, info.getEmail(), password))) cout << "thong tin sai!\n";
            else{
                int id = getNextId();
                dsUsers.push_back(UserInfos(id, info.getEmail(), password)); // add them vao vector
                ofstream ofs("users.txt");
                if(ofs.is_open()){
                    for(auto &x : dsUsers) // cap nhat lai file user.txt
                        ofs << '[' << x.getId() << ']' << ' ' << '[' << x.getEmail() << ']' << ' ' << '[' << x.getPassword() << ']' << endl;
                    cout << "dang ki thanh cong!\n";
                    cout << "hay dang nhap bang email cua ban!\n";
                    ofs.close();
                    info.addInfo(); // them thong tin vao people.txt
                }
                else cout << "khong truy cap duoc data!\n";
            }
        }

        
        // login logout se tra ve 1 object nen khi su dung thi gan no bang bien (kieu Person)
        Person login(string email, string password){ // check thong tin dang nhap
            if(!checkUser(UserInfos(0, email, password))){
                cout << "thong tin dang nhap sai!\n";
                return Person("", "", "", "", "", "", "");
            }
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
                            return Person(name, emailCheck, sex, birthday, addre, phone, role, id );
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

};



// khai bao cac bien he thong
Users acesstUsers; // class he thong => khai bao 1 lan
Books acesstBooks;
Ebooks acesstEbooks;
Person infoUser("", "", "", "", "", "", "");
bool checkInfoUser; // check xem dang nhap thanh cong khong?
char option; // cac thao tac khi dang nhap thanh cong
 
 
// funtion option
 
void Login(){
    checkInfoUser = false;
    string email, password;
    cout << "nhap email:\n";
    cin >> email;
    cout << "nhap password:\n";
    cin >> password;
    if(!acesstUsers.checkInfor(email, password)){
        cout << "dang nhap that bai!\n";
    }
    else{
        infoUser = acesstUsers.login(email, password);
        cout << '\n' << "Welcome " << infoUser.getName() << '\n' << endl;
        checkInfoUser = true;
    }
}


void add_Book(){ // chi admin
    cout << "ban muon them vao:\n";
    while(1){
        cout << "books -> chon1    ----------    ebooks -> chon2\n";
        int op; cin >> op;
        if(op == 1){
            cout << "nhap thong tin cuon sach muon them\n";
            int id = 0;
            string name, author;
            int quantity;
            cout << "nhap ten sach:\n";
            cin.ignore();
            getline(cin, name);
            cout << "nhap tac gia:\n";
            getline(cin, author);
            cout << "nhap so luong:\n";
            cin >> quantity;
            BookInfor add(id, name, author, quantity);
            acesstBooks.AddBook(add);
            cout << '\n' << "them thanh cong!\n";
            break;
        }
        if(op == 2){
            cout << "nhap thong tin cuon sach muon them\n";
            int id = 0;
            string name, author, fileFormat;
            int quantity, fileSize;
            cout << "nhap ten sach:\n";
            cin.ignore();
            getline(cin, name);
            cout << "nhap tac gia:\n";
            getline(cin, author);
            cout << "nhap so luong:\n";
            cin >> quantity;
            cout << "nhap fileFormat:\n";
            cin >> fileFormat;
            cout << "nhap fileSize:\n";
            cin >> fileSize;
            EbookInfor add(id, name, author, quantity, fileFormat, fileSize);
            acesstEbooks.AddBook(add);
            cout << '\n' << "them thanh cong!\n";
            break;
        }
        else cout << "vui long nhap dung!\n";
    }
}

void delete_Book(){ // chi admin
    cout << "ban muon xoa?\n";
    while(1){
        cout << "books -> chon1    ----------    ebooks -> chon2\n";
        int op; cin >> op;
        if(op == 1){
            int id;
            cout << "nhap id cua sach muon xoa:\n";
            cin >> id;
            acesstBooks.deleteBook(id);
            break;
        }
        if(op == 2){
            int id;
            cout << "nhap id cua sach muon xoa:\n";
            cin >> id;
            acesstEbooks.deleteBook(id);
            break;
        }
        else{
            cout << "vui long nhap dung!\n";
        }
    }
}

void borrow_Book(){ // chi user
    cout << "ban muon muon loai sach gi?\n";
    while(1){
        cout << "books -> chon1    ----------    ebooks -> chon2\n";
        int op; cin >> op;
        if(op == 1){
            cout << "nhap id sach ban muon muon:\n";
            int id; cin >> id;
            BorrowInfo borrow(infoUser.getId(), id, -1);
            if(borrow.checkBook()){
                borrow.addInfo();
                cout << "thanh cong!\n";
            }
            else cout << "khong co sach ma ban muon!\n";
            break;
        }
        if(op == 2){
            cout << "nhap id sach ban muon muon:\n";
            int id; cin >> id;
            BorrowInfo borrow(infoUser.getId(), -1, id);
            if(borrow.checkEbook()){
                borrow.addInfo();
                cout << "muon thanh cong!\n";
            }
            else cout << "khong co sach ma ban muon muon!\n";
            break;
        }
        else cout << "vui long nhap dung!\n";
    }
}

void get_All_Books(){
    acesstBooks.getAllBooks();
}

void get_Book(){
    cout << "nhap id cuon sach:\n";
    int id; cin >> id;
    acesstBooks.getBook(id);
}

void get_All_Ebooks(){
    acesstEbooks.getAllBooks();
}

void get_Ebook(){
    cout << "nhap id ebook:\n";
    int id; cin >> id;
    acesstEbooks.getBook(id);
}

void update_Infor_User(){
    while(1){
        cout << "thay doi mat khau - chon 1\n";
        cout << "thay doi email - chon 2\n";
        cout << "thay doi ten - chon 3\n";
        cout << "thay doi gioi tinh - chon 4\n";
        cout << "thay doi ngay sinh - chon 5\n";
        cout << "thay doi dia chi - chon 6\n";
        cout << "thay doi so dien thoai - chon 7\n";
        cout << "thoat - chon 8\n";
        int op; cin >> op;
        UserInfos update(0, "", "");
        if(op == 1){
            string newPassword1, newPassword2;
            cout << "nhap mat khau moi:\n";
            cin >> newPassword1;
            cout << "nhap lai mat khau moi:\n";
            cin >> newPassword2;
            if ( newPassword1 != newPassword2 ){
                cout << "nhap lai dung mat khau!\n";
                continue;
            }
            cin.ignore();
            infoUser.setPassword(newPassword1);
            cout << "doi mat khau thanh cong!\n";
        }
        else if(op == 2){
            cout << "nhap email moi:\n";
            string newEmail;
            cin >> newEmail;
            cin.ignore();
            infoUser.setEmail(newEmail);
            cout << "doi email thanh cong!\n";
        }
        else if(op == 3){
            cout << "nhap ten moi:\n";
            string newName;
            cin.ignore();
            getline(cin, newName);
            infoUser.setName(newName);
            cout << "doi ten thanh cong!\n";
        }
        else if(op == 4){
            cout << "nhap gioi tinh moi:\n";
            string newSex;
            cin >> newSex;
            cin.ignore();
            infoUser.setSex(newSex);
            cout << "doi gioi tinh thanh cong!\n";
        }
        else if(op == 5){
            cout << "nhap ngay sinh moi:\n";
            string newBirthdate;
            cin >> newBirthdate;
            cin.ignore();
            infoUser.setBirthdate(newBirthdate);
            cout << "doi ngay sinh thanh cong!\n";
        }
        else if(op == 6){
            cout << "nhap dia chi moi:\n";
            string newAddress;
            cin.ignore();
            getline(cin, newAddress);
            infoUser.setAddress(newAddress);
            cout << "doi dia chi thanh cong!\n";
        }
        else if(op == 7){
            cout << "nhap so dien thoai moi:\n";
            string newPhoneNumber;
            cin >> newPhoneNumber;
            cin.ignore();
            infoUser.setPhoneNumber(newPhoneNumber);
            cout << "doi so dien thoai thanh cong!\n";
        }
        else if(op == 8) break;
        else cout << "chon khong hop le!\n";
    }
}

void edit_Info_User(int id){ // chi admin
    Person info = infoUser.getInforPeople(id);
    if(!info.getName().empty()){
        while(1){
            cout << "thay doi role - chon 1\n";
            cout << "thay doi email - chon 2\n";
            cout << "thay doi ten - chon 3\n";
            cout << "thay doi gioi tinh - chon 4\n";
            cout << "thay doi ngay sinh - chon 5\n";
            cout << "thay doi dia chi - chon 6\n";
            cout << "thay doi so dien thoai - chon 7\n";
            cout << "thoat - chon 8\n";
            int op; cin >> op;
            UserInfos update(0, "", "");
            if(op == 1){
                string newRole;
                cout << "nhap Role moi:\n";
                cin >> newRole;
                cin.ignore();
                info.setRole(newRole);
                cout << "doi Role thanh cong!\n";
            }
            else if(op == 2){
                cout << "nhap email moi:\n";
                string newEmail;
                cin >> newEmail;
                cin.ignore();
                info.setEmail(newEmail);
                cout << "doi email thanh cong!\n";
            }
            else if(op == 3){
                cout << "nhap ten moi:\n";
                string newName;
                cin.ignore();
                getline(cin, newName);
                info.setName(newName);
                cout << "doi ten thanh cong!\n";
            }
            else if(op == 4){
                cout << "nhap gioi tinh moi:\n";
                string newSex;
                cin >> newSex;
                cin.ignore();
                info.setSex(newSex);
                cout << "doi gioi tinh thanh cong!\n";
            }
            else if(op == 5){
                cout << "nhap ngay sinh moi:\n";
                string newBirthdate;
                cin >> newBirthdate;
                cin.ignore();
                info.setBirthdate(newBirthdate);
                cout << "doi ngay sinh thanh cong!\n";
            }
            else if(op == 6){
                cout << "nhap dia chi moi:\n";
                string newAddress;
                cin.ignore();
                getline(cin, newAddress);
                info.setAddress(newAddress);
                cout << "doi dia chi thanh cong!\n";
            }
            else if(op == 7){
                cout << "nhap so dien thoai moi:\n";
                string newPhoneNumber;
                cin >> newPhoneNumber;
                cin.ignore();
                info.setPhoneNumber(newPhoneNumber);
                cout << "doi so dien thoai thanh cong!\n";
            }
            else if(op == 8) break;
            else cout << "chon khong hop le!\n";
        }
    }
    else cout << "id khong hop le!\n";
}

void bookBack(){
    cout << "ban muon tra:\n";
    cout << "books -> chon1    ----------    ebooks -> chon2\n";
    int op; cin >> op;
    if ( op == 1 ){
        cout << "nhap id cuon sach ban muon tra:\n";
        int idBook; cin >> idBook;
        infoUser.giveBookback( idBook );
    }
    else if ( op == 2 ){
        cout << "nhap id ebook ban muon tra:\n";
        int idEbook; cin >> idEbook;
        infoUser.giveEbookback( idEbook );
    }else{
        cout << "chon khong hop le!\n";
    }
}


int main()
{
    acesstBooks.Sx_dsBooks(); // sap xep lai dsBooks
    while(1){
        cout << "dang nhap - bam \"a\"\n"; // xong
        cout << "dang ki - bam \"b\"\n"; // xong
        cout << "thoat chuong trinh - bam \"r\"\n"; // xong
        cin >> option;
        if(option == 'r') return 0;
        if(option == 'b'){// dang ky tai khoan
        string name , email, sex , birthdate , address, phoneNumber , password;
            cout << "DANG KY TAI KHOAN:\n";
            cout << "Email:\n";
            cin >> email;
            cout << "PASSWORD:\n";
            cin >> password;
            cout << "HO VA TEN:\n";
            cin.ignore();
            getline( cin, name );
            cout << "NGAY SINH:\n";
            cin >> birthdate;
            cout << "GIOI TINH:\n";
            cin >> sex ; 
            cout << "DIA CHI\n";
            cin.ignore();
            getline( cin , address );
            cout << "SDT:\n";
            cin >> phoneNumber;
            Person person(name, email, sex , birthdate, address, phoneNumber );
            acesstUsers.regist(person , password);
        }
        if(option == 'a'){
            Login();
            while(checkInfoUser){
                cout << "CHON CAC CHUC NANG:\n";
                cout << "bam \"c\" de them sach - quyen cua admin\n"; // xong
                cout << "bam \"d\" de sua thong tin sach - quyen cua admin\n"; // xong
                cout << "bam \"e\" de xoa sach - quyen cua admin\n"; // xong
                cout << "bam \"f\" de muon sach\n"; // xong
                cout << "bam \"g\" de tra sach\n";
                cout << "bam \"h\" de hien thi tat ca sach\n"; // xong
                cout << "bam \"i\" de lay thong tin cuon sach trong Books\n"; // xong
                cout << "bam \"j\" de hien thi tat ca sach trong Ebooks\n"; // xong
                cout << "bam \"k\" de lay thong tin cuon sach trong Ebooks\n"; // xong
                cout << "bam \"m\" de hien thi tat ca sach ban da muon\n";
                cout << "bam \"n\" de hien thi tat ca sach cua mot nguoi muon- quyen cua admin\n";
                cout << "bam \"o\" de chinh sua thong tin ca nhan cua ban\n"; // xong 1 nua
                cout << "bam \"p\" de chinh sua thong tin ca nhan cua mot nguoi - quyen cua admin\n";
                cout << "bam \"q\" de dang suat\n"; // xong
                cout << "bam \"r\" de thoat chuong trinh\n"; // xong
                cout << endl;
                cin >> option;
                if(option == 'c'){
                    if(infoUser.getRole() == "Admin") add_Book();
                    else{
                        cout << "ban khong phai admin!\n";
                        cout << "option khac:\n";
                    }
                }
                if(option == 'd'){
                    if( infoUser.getRole() != "Admin" ){
                        cout << "ban khong duoc cap quyen chinh sua thong tin sach\n";
                    }
                    else {
                        while(1){
                            int id, quantity ;
                            string title, author;
                            cout << "DANG CHINH SUA THONG TIN SACH\n";
                            cout << "nhap id cuon sach:\n";
                            cin >> id ;
                            cout << "chinh sua ten sach:\n";
                            cin.ignore();
                            getline( cin , title );
                            cout << "chinh sua tac gia:\n";
                            getline( cin , author );
                            cout << "chinh sua so luong sach\n";
                            cin >> quantity;
                            BookInfor bookInfor(id, title, author, quantity );
                            acesstBooks.updateBook(bookInfor);
                            cout << "tiep tuc chinh sua (yes/no)\n";
                            string choose;
                            cin >> choose; 
                            if ( choose != "yes" )break;;
                        }
                    }
                }
                if(option == 'e'){
                    if(infoUser.getRole() == "Admin") delete_Book();
                    else{
                        cout << "ban khong phai admin!\n";
                        cout << "option khac:\n";
                    }
                }
                if(option == 'f'){
                    if(infoUser.getRole() == "User") borrow_Book();
                    else{
                        cout << "ban khong phai user!\n";
                        cout << "option khac:\n";
                    }
                }
                if(option == 'g'){
                    bookBack();
                }
                if(option == 'h'){
                    get_All_Books();
                }
                if(option == 'i'){
                    get_Book();
                }
                if(option == 'j'){
                    get_All_Ebooks();
                }
                if(option == 'k'){
                    get_Ebook();
                }
                // if(option == 'm')
                // if(option == 'n')
                if(option == 'o'){
                    update_Infor_User();
                }
                if(option == 'p'){
                    if(infoUser.getRole() == "Admin"){
                        cout << "nhap vao id:\n";
                        int id; cin >> id;
                        edit_Info_User(id);
                    }
                    else{
                        cout << "ban khong phai admin!\n";
                        cout << "option khac!\n";
                    }
                }
                if(option == 'q'){ // dang xuat
                    break;
                }
                if(option == 'r') return 0; // thoat chuong trinh
            }
        }
    }
 
    return 0;
}