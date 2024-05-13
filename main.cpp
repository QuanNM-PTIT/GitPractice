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
        Person(){
            this->id = autoId();
            this->name = "";
            this->email = "";
            this->sex = "";
            this->birthdate = "";
            this->address = "";
            this->phoneNumber = "";
            this->role = "";

        }
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
                if(cnt == x) {
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
};

class Book{ // thong tin cuon sach
    private:
        int id , qt;
        string title;
        string author;

    public:
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
        vector<Book> dsBooks;

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
                    char s ; // de doc ki tu [,]
                    string tmp;
                    ss >> tmp;
                    id = stoi(tmp.substr(1, tmp.size() - 2));
                    ss >> tmp; 
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        title += tmp+ " ";
                        ss >> tmp;
                    }
                    title += tmp.substr(0, tmp.size() - 2);
                    ss >> tmp;
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        author += tmp+ " ";
                        ss >> tmp;
                    }
                    author += tmp.substr(0, tmp.size() - 2);
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
            cout<<id<<endl;
            string title = add_Book.getTitle();
            string author = add_Book.getAuthor();
            int qt = add_Book.getQuantity();
            dsBooks.push_back(add_Book);
            ofstream ofs1("books.txt", ios::app);
            if(ofs1.is_open()){
                ofs1<<"["<<id<<"] ["<<title<<"] ["<<author<<"] ["<<qt<<"]"<<endl;
                ofs1.close();
            }
            


                cout<<"Ban vua them sach thanh cong !\n";
            // }
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
        void updateBook(Book update_Book){
            int id = update_Book.getId();
            bool check = true;
            if(id > dsBooks.size()){
                cout<<"Khong tim thay du lieu -_-\n";
                check = false;
            }
            else{
                if(!checkBook(update_Book)) cout<<"Thong tin update chua hop le !\n";
                else{
                    dsBooks[id-1] = update_Book; // cap nhat trong dsBooks
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
                        ofs<<"["<<s.getId()<<"] ["<<s.getTitle()<<"] ["<<s.getAuthor()<<"] ["<<s.getQuantity()<<"]"<<endl;

                    ofs.close();
                    cout<<"Da xoa thanh cong !\n";
                }  
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
        bool comp(EBook &a , EBook &b){ // Sap xep theo thu tu id
            return a.getId() < b.getId();
}
};

class EBooks{
    private:
       vector<EBook> list_EBooks;

    public:
        EBooks(){
            ifstream ifs("ebooks.txt");
            
            if(ifs.is_open()){
                string line;
                while(getline(ifs,line)){
                    stringstream ss(line);
                    int id, qt, fileSize;
                    string title = "", author = "", fileFormat = ""; 
                    char s ; // de doc ki tu [,]
                    string tmp;
                    ss >> tmp;
                    id = stoi(tmp.substr(1, tmp.size() - 2));
                    ss >> tmp; 
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        title += tmp+ " ";
                        ss >> tmp;
                    }
                    title += tmp.substr(0, tmp.size() - 2);
                    ss >> tmp;
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        author += tmp+ " ";
                        ss >> tmp;
                    }
                    author += tmp.substr(0, tmp.size() - 2);
                    ss >> tmp;
                    qt =  stoi(tmp.substr(1, tmp.size() - 2));
                    ss >> tmp;
                    tmp = tmp.erase(0, 1);
                    while(tmp[tmp.size() - 1] != ']'){
                        fileFormat += tmp + " ";
                        ss >> tmp;
                    }
                    fileFormat += tmp.substr(0, tmp.size() - 2);
                    ss >> tmp;
                    fileSize = stoi(tmp.substr(1, tmp.size() - 2));
                    EBook EB(title, author, qt, fileFormat, fileSize);
                    EB.setId(id);
                    list_EBooks.push_back(EB);
                }
                
                ifs.close();
            }
        }

        void SortEBooks(){ // Sap xep dsBooks theo id
            sort(list_EBooks.begin(), list_EBooks.end(),comp);
        }

        void AllBooks(){
            cout<<"Danh sach tat ca Ebook: \n";
            cout<<"ID-Ten sach-Tac gia-So luong-Dang file-Do lon file\n";
            SortEBooks();
            for(auto x: list_EBooks){
                cout<<"["<<x.getId()<<"]-"<<x.getTitle()<<"-"<<x.getAuthor()<<"-";
                cout<<x.getQuantity()<<"-"<< x.getFileFormat()<<"-"<< x.getFileSize()<<endl;
            }
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
            this->id = autoId();
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
        Person logout(Person &logOutUser){
            return Person("", "", "", "", "", "", "");
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
                cout<<"Password can it nhat 8 ki tu\n Co it nhat 1 ki tu in hoa, 1 ki tu in thuong va chu so\n";
                cout<<"Nhap lai password: ";
                cin >> pw;
            }

            int id = getNextId();
            dsUsers.push_back(User(Info.getEmail(),pw));
            cout<<"Tao tai khoan thanh cong !\n";

            ofstream ofs1("users.txt",ios::app);
            if(ofs1.is_open()){
                ofs1<<endl;
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
        Person login(User &Login){ 
            // check thong tin dang nhap
            string email, pw;
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
                            ifs.close();
                        }
                    }
                }
                if(!check){
                    cout<<"Tai khoan khong ton tai!"<<endl;
                    return Person("","","","","","",""); // Chua co du lieu trong people.txt
                }
            }
            return Person("","","","","","","");   
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
            if(cnt == x){
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
        ofstream out("borrowInfors.txt", ios::app);
        out<<'['<< id <<']'<<' '<<'['<< personId <<']'<<' '<<'['<< bookId <<']'<<' '<<'['<< eBookId <<']'<<endl;
        out.close();
    }

    //Cap nhat thong tin muon sach
    void updateInfo(int updateId, int updatePersonId, int updateBookId, int updateEBookId){ 
        ifstream in;
        in.open("borowInfors.txt", ios::in);
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
        out.open("borrowInfors.txt", ios :: out);
        for(string s : listBorrowInfors){
            out<<s<<endl;
        }
        out.close();
        return;
    }

    //Cap nhat thong tin tra sach
    void updateReturnInfo(int updateBookId){ 
        ifstream in;
        in.open("borowInfors.txt", ios::in);
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
        out.open("borrowInfors.txt", ios :: out);
        for(string s : listBorrowInfors){
            out<<s<<endl;
        }
        out.close();
        return;
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
    cout << " 1. Dang nhap\n" ;                                                                   
    cout << " 2. Dang ki\n";
    cout << " 3. Them sach\n";
    cout << " 4. Sua thong tin sach\n";
    cout << " 5. Xoa sach\n";
    cout << " 6. Muon sach\n";
    cout << " 7. Tra sach\n";
    cout << " 8. Lay thong tin cac quyen sach\n";
    cout << " 9. Lay thong tin 1 quyen sach\n";
    cout << "10. Lay thong tin 1 eBook co id nam trong file eBooks.txt\n";
    cout << "11. Hien thi tat ca quyen sach cua 1 nguoi dung da muon voi id cua 1 nguoi dung\n";
    cout << "12. Hien thi cac cuon sach da muon của ban than\n";
    cout << "13. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon\n";
    cout << "14. Chinh sưa thong tin ca nhan  \n";
    cout << "15. Chinh sua thong tin ca nhan cua nguoi khac\n";
    cout << "16. Dang xuat\n";
    cout << "17. Thoat chuong trinh\n";
}

int main() {
    menu();
    int query;
    User U;
    Users list_users;
    Books list_books;
    list_books.SortDsBooks();
    EBooks list_ebooks;
    list_ebooks.SortEBooks();
    Person P;
    while(1){
        cout<<"Nhap tinh nang muon su dung: ";
        cin >> query;
        if(query == 1){
            string email, pw;
            cout<<"   Email: ";
            cin >> email;
            cout<<"Password: ";
            cin>> pw;
            User u(email, pw);
            U = u;
            P = list_users.login(U);
        }
        else if(query == 2){
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
        else if(query == 3){
            if(P.getRole() != "Admin"){
                cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                continue;
            }
            int id , qt;
            string title;
            string author;
            cout<<"Ten sach: ";
            cin.ignore();
            getline(cin, title);
            cout<<"Tac gia: ";
            getline(cin, author);
            cout<<"So luong: ";
            cin >> qt;
            Book B(title, author, qt);
            list_books.addBook(B);            
        }
        else if(query == 4){
            if(P.getRole() != "Admin"){
                cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                continue;
            }
            int id, qt;
            string title, author;
            cout<<"Nhap thong tin sach can update:\n";
            cout<<"Nhap ID sach: ";
            cin >> id;
            cout<<"Ten sach: ";
            cin.ignore();
            getline(cin, title);
            cout<<"Tac gia: ";
            getline(cin, author);
            cout<<"So luong: ";
            cin >> qt;
            Book B(title, author, qt);
            B.setId(id);
            list_books.updateBook(B);            
        }
        else if(query == 5){
            //delete book
            if(P.getRole() != "Admin"){
                cout<<"Chi admin moi duoc su dung tinh nang nay\n";
                continue;
            }
            cout<<"Nhap ID sach can xoa: ";
            int id;
            cin >> id;
            list_books.deleteBook(id);  
            
        }
        else if(query == 6){
            if(P.getRole() != "User"){
                cout<<"Chi user moi duoc su dung tinh nang nay\n";
                continue;
            }
            // int idBook;
            // cout<<"Nhap ID sach can muon: ";
            // cin >> idBook;
            // int personId = P.getId();

        }
        else if(query == 7){
            if(P.getRole() != "User"){
                cout<<"Chi user moi duoc su dung tinh nang nay\n";
                continue;
            }
            
        }
        else if(query == 8){
            list_books.AllBooks();
        }
        else if(query == 9){

            
        }
        else if(query == 10){
            list_ebooks.AllBooks();
        }
        else if(query == 11){
            
        }
        else if(query == 12){
            
        }
        else if(query == 13){
            
        }
        else if(query == 14){
            
        }
        else if(query == 15){
            
        }
        else if(query == 16){
            U.logout(P);
        }
        else if(query == 17){
            break;
        }
        else {
            cout<< "Nhap lai lưa chon cua ban: ";
            cin >> query;
        }
    }
    return 0;
}