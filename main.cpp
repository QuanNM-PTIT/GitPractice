#include <bits/stdc++.h>
using namespace std;
class Book;
class User;
class Person;
vector<Book> v;
vector<User> v_user;
static vector<Person> v_person; 
int UpdateIdPerson(){ // cap nhat ID person
	ifstream input("people.txt");
	set<int> se;
	if(input.is_open()){
		string s;
		while(getline(input, s)){
			int i = 0;
			string tmp = "";
			while(s[i] != ']'){
				if(isdigit(s[i])) tmp += s[i];
				i++;
			}
			se.insert(stoi(tmp));
		}
		input.close();
	}
	else cout << "Khong mo duoc file!" << endl;
	int NextId = 1;
	while(se.count(NextId)){
		NextId++;
	}
	return NextId;
}
int UpdateIdBorrowInfo(){ // cap nhat ID muon sach
	ifstream input("borrowInfos.txt");
	set<int> se;
	if(input.is_open()){
		string s;
		while(getline(input, s)){
			int i = 0;
			string tmp = "";
			while(s[i] != ']'){
				if(isdigit(s[i])) tmp += s[i];
				i++;
			}
			se.insert(stoi(tmp));
		}
		input.close();
	}
	else cout << "Khong mo duoc file!" << endl;
	
	int NextId = 1;
	while(se.count(NextId)){
		NextId++;
	}
	return NextId;
}

class Person{
private:
    int id;
    string name = "", email = "", sex = "", birthdate = "", phoneNumber = "", role = "", address = "";
public:
	Person(){
		this->id = UpdateIdPerson();
	}
    Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role){
        this->id = UpdateIdPerson();
        this->name = name;
        this->email = email;
        this->sex = sex;
        this->birthdate = birthdate;
        this->address = address;
        this->phoneNumber = phoneNumber;
		this->role = role;
    }
    void In(Person x){
        cout << x.id << ' ' << x.name << ' ' << x.email << ' ' << x.sex << endl;
    }
	string Tong_Hop(){
		return '[' + this->id + "] " + '[' + this->name + "] " + '[' + this->email + "] " + '[' + sex + "] " + '[' + this->birthdate + "] " + '[' + this->address + "] " + '[' + this->phoneNumber + "] "+ '[' + this->role + "] ";
	}
	bool operator < ( const Person& y){
		return this->id < y.id;
	}
	void SapXepFilePeople(){
		sort(v_person.begin(), v_person.end()); 
	}	 
	void GhiDeFilePeople(){
		ofstream output("people.txt");
		if(output.is_open()){
			for(auto y : v_person){
				output << y.Tong_Hop() << endl;
			}
			output.close();
		}
		else{
			cout << "khong mo duoc file\n"; 
		}
	} 
	void addPerson(){
		v_person.push_back(*this); 
		ofstream output("people.txt", ios::app);
		if(output.is_open()){
			output << '[' << id << "] "  << '[' << name << "] " << '[' << email << "] " << '[' << sex << "] " << '[' << birthdate << "] " << '[' << address << "] " << '[' << phoneNumber << "] "  << '[' << role << "] " << endl ;
			GhiDeFilePeople();
			output.close(); 
		} 
		else{
			cout << "khong mo duoc file\n"; 
		} 
	} 
	static vector<Person> getPerson(){
		v_person.clear(); 
		ifstream input("people.txt");
		if(input.is_open()){
			string tmp;
			while(getline(input,tmp)){
				Person x;
				int start = 0, end = 0, i = 1;
				while(tmp.find('[', end) != -1){
					start =  tmp.find('[', end);
					end =  tmp.find(']', start);
					string tmp1 = tmp.substr(start + 1,end - start - 1); 
					switch (i){
						case 1:  
							x.id = stoi(tmp1) ; 
							break;
						case 2: 
							x.name = tmp1 ;
							break;
						case 3: 
							x.email = tmp1;
							break;
						case 4: 
							x.sex = tmp1;
							break;
						case 5: 
							x.birthdate = tmp1;
							break;
						case 6: 
							x.address = tmp1;
							break;
						case 7: 
							x.phoneNumber = tmp1;
							break;
						default: 
							x.role = tmp1;
					}
					i++; 
				} 
				v_person.push_back(x); 
			}
			input.close();
		}
		else{
			cout << "khong mo duoc file";
		}
		return v_person;	
	}

};
class BorrowInfo{
private:
    int id, personId = 0, bookId = 0, ebookId = 0;
public:
	BorrowInfo() {
        this->id = UpdateIdBorrowInfo();
    }
    BorrowInfo(int personId, int bookId, int ebookId ){
        this->id = UpdateIdBorrowInfo();
        this->personId = personId;
        this->bookId = bookId;
        this->ebookId = ebookId;
    }
    void addInfo(){ // them thong tin muon sach 
    	int Id1, Id2, Id3;
    	cout << "Nhap ID nguoi muon: ";
    	cin >> Id1;
   		cout << "Nhap ID sach: ";
   		cin >> Id2;
   		cout << "Nhap ID Ebook: ";
   		cin >> Id3;
        ofstream output("borrowInfos.txt", ios::app);
		if (output.is_open()){
			output << endl;
			output << '[' << id  << ']'  << ' '  << '[' << Id1 << ']' << ' '  << '[' << Id2 << ']' << ' '  << '[' << Id3 << ']';
        	output.close();
		}
        else {
        	cout << "Khong mo duoc file\n";
		}
    }
	void updateInfo(){
		BorrowInfo update;
		cout << "__Cap nhat thong tin muon sach__\n";
		cout << "Nhap ID muon sach: ";
		cin >> update.id;
		cout << "\nNhap ID nguoi muon: ";
		cin >> update.personId;
		cout << "\nNhap ID sach: ";
		cin >> update.bookId;
		cout << "\nNhap ID Ebook: ";
		cin >> update.ebookId;
		// Doc du lieu tu file BorrowInfos.txt
		ifstream input("borrowInfos.txt");
		// doc du lieu tu file borrowInfos.txt 
		vector<BorrowInfo> info;
		if(input.is_open()){
			string s; 
			while(getline(input, s)){
				BorrowInfo oldInfo;
				string tmp;
				stringstream ss(s);
				int cnt = 0;
				while(ss >> tmp){
					if(!tmp.empty()){
						// xoa dau []
						cnt++;
						tmp.erase(0, 1);
						tmp.erase(tmp.size() - 1, 1);
						if(cnt == 1){
							oldInfo.id = stoi(tmp);
						} 
						else if(cnt == 2) oldInfo.personId = stoi(tmp);
						else if(cnt == 3) oldInfo.bookId = stoi(tmp);
						else if(cnt == 4){
							oldInfo.ebookId = stoi(tmp);
							info.push_back(oldInfo);
						}
					}
				}
			}
			input.close();
		}
		else cout << "Khong mo duoc file!\n";
		// ghi lai vao file
		ofstream output("borrowInfos.txt");
		if(output.is_open()){
			bool check = true;
			for(auto borrowRecord: info){
				if(borrowRecord.id == update.id){
					borrowRecord.personId = update.personId;
					borrowRecord.bookId = update.bookId;
					borrowRecord.ebookId = update.ebookId;
					check = false;
					cout << "Cap nhat thong tin thanh cong!\n";
				}
				output << "[" << borrowRecord.id << "] [" << borrowRecord.personId << "] [" << borrowRecord.bookId << "] [" << borrowRecord.ebookId << "]" << endl;
			}
			if(check) cout << "Khong tim thay thong tin muon cap nhat!\n"; 
			output.close();
		}
		else cout << "Khong mo duoc file!\n";
	} 
};
class Book{
	private:
		int id;
		string title;
		string author;
		int quality;
	public:
		Book(){
		} 
		Book(string title, string author, int quality){
			this->title = title;
			this->author = author;
			this->quality = quality;
			if(v.size() == 0){
			 	this->id = 1;
			 } 
			else{
			 	this->id = v[v.size()-1].id + 1;
			} 
				
		} 
		string Tong_Hop(){
			return '[' + to_string(this->id) + "] " + '[' + this->title + "] " + '[' + this->author + "] " + '[' + to_string(this->quality) + "] ";
		}
		bool operator < ( const Book& y){
			return this->id < y.id;
		}
		void SapXepFileBook(){
			sort(v.begin(), v.end()); 
		}	 
		void GhiDeFileBook(){
			ofstream output("books.txt");
			if(output.is_open()){
				for(auto y : v){
					output << y.Tong_Hop() << endl;
				}
				output.close();
			}
			else{
				cout << "khong mo duoc file\n"; 
			}
		} 
		
		void addBook(){
				v.push_back(*this); 
				ofstream output("books.txt", ios::app);
				if(output.is_open()){
					output << '[' << id << "] "  << '[' << title << "] " << '[' << author << "] " << '[' << quality << "] " << endl ;
					GhiDeFileBook();
					output.close(); 
				} 
				else{
					cout << "khong mo duoc file\n"; 
				} 
		} 
		vector<Book> getBooks(){
			v.clear(); 
			ifstream input("books.txt");
			
			if(input.is_open()){
				string tmp;
				while(getline(input,tmp)){
					Book x;
					int start = 0, end = 0, i = 1;
					while(tmp.find('[', end) != -1){
						start =  tmp.find('[', end);
						end =  tmp.find(']', start);
						string tmp1 = tmp.substr(start + 1,end - start - 1); 
						if(i == 1)  x.id = stoi(tmp1) ; 
						else if (i == 2) x.title = tmp1 ;
						else if (i == 3) x.author = tmp1;
						else  x.quality = stoi(tmp1);
						i++; 
					} 
					v.push_back(x); 
				}
				SapXepFileBook();
				GhiDeFileBook(); 
				input.close();
			}
			else{
				cout << "khong mo duoc file";
			}
			return v;	
		} 
		void updateBook(int id, string title, string author, int quality){
				int check = 0;
				for(int i= 0; i<v.size(); i++){
					if(v[i].id == id){
						check = 1;
						v[i].title = title;
						v[i].author = author;
						v[i].quality = quality;
						break; 
					} 
				}
				if(check == 1){
					GhiDeFileBook();
				} 
				if(check == 0){
					cout << "Khong ton tai id sach " << id << "\n";
				}
		}
		
		void deleteBook(int id){
			int check = 0;
			for(int i = 0; i<v.size(); i++){
				if(v[i].id == id){
					check = 1;
					v.erase(v.begin() + i);
					break; 
				}
			}
			if(check == 1){
				GhiDeFileBook();
			}
			else{
				cout << "id sach " << id << " khong ton tai" << "\n"; 
			} 
		
		}
		
}; 
class EBook : public Book{
	private:
		string fileFormat;
		int fileSize;
};

class User : public Person{
	private:
		int id;
		string email;
		string password;
		
	public:
		User(){
		} 
		User(string email, string password){
			this->email = email;
			this->password = password;
			
			if(v_user.size() == 0){
			 	this->id = 1;
			 } 
			else{
			 	this->id = v_user[v_user.size()-1].id + 1;
			} 		
		}
		string Tong_Hop(){
			return '[' + to_string(this->id) + "] " + '[' + this->email + "] " + '[' + this->password + "]";
		}
		void GhiDeFileUser(){
			ofstream output("users.txt");
			if(output.is_open()){
				for(auto y : v_user){
					output << y.Tong_Hop() << endl;
				}
				output.close();
			}
			else{
				cout << "khong mo duoc file\n"; 
			}
		}
		void getusers(){
			v_user.clear(); 
			ifstream input("users.txt");
			if(input.is_open()){
				string tmp;
				while(getline(input,tmp)){
					User x;
					int start = 0, end = 0, i = 1;
					while(tmp.find('[', end) != -1){
						start =  tmp.find('[', end);
						end =  tmp.find(']', start);
						string tmp1 = tmp.substr(start + 1,end - start - 1); 
						if(i == 1)  x.id = stoi(tmp1) ; 
						else if (i == 2) x.email = tmp1 ;
						else x.password = tmp1;
						i++; 
					} 
					v_user.push_back(x); 
				} 
				input.close();
			}
			else{
				cout << "khong mo duoc file";
			}
		} 
		bool check(){
			string tmp = this->email; 
			for(auto y : v_user){
				if(y.email == tmp){
					cout << "email da ton tai! \nVui long chon email khac\n";
					return 0;
				}
			}
			int n = tmp.size();
			if(tmp.substr(n-10,10) != "@gmail.com"){
				cout << "duoi email khong hop le\n";
				return 0;
			}
			if(tmp.substr(0,10) == "@gmail.com"){
				cout << "ten email khong hop le\n";
				return 0;
			}
			
			int check_password = 0;
			string tmp2 = this->password;
			for(int i=0; i<tmp2.size(); i++){
				if(tmp2[i] >= '0' && tmp2[i] <= '9'){
					check_password = 1;
					break;
				}
			}
			if(check_password == 0){
				cout << "mat khau bao gom ca chu va so\n";
				return 0;
			}
			for(int i=0; i<=tmp2.size(); i++){
				if((tmp2[i] >= 'a' && tmp2[i] <= 'z') || (tmp2[i] >= 'A' && tmp2[i] <= 'Z')){
					check_password = 2;
					break;
				}
			}
			if(check_password != 2){
				cout << "mat khau bao gom ca chu va so\n";
				return 0;
			}
			return 1;
		}
				
		void addUsers(){
			if(this->check() != 0){
				v_user.push_back(*this); 
				ofstream output("users.txt", ios::app);
				if(output.is_open()){
					output << '[' << id << "] "  << '[' << email << "] " << '[' << password << "] "<< endl ;
					GhiDeFileUser();
					output.close(); 
				} 
				else{
					cout << "khong mo duoc file\n"; 
				} 
			} 	
		}  
		// Person login(){
			
		// } 
		
}; 
void DisplayMenu(){
	cout << "-----------------------------------------------MENU--------------------------------------------" << endl;
	cout << "	1. Dang nhap.																			" << endl;
	cout << "	2. Dang ky.																				" << endl;
	cout << "	3. Them sach.																			" << endl;
	cout << "	4. Sua thong tin sach.																	" << endl;
	cout << "	5. Xoa sach.																			" << endl;
	cout << "	6. Muon sach.																			" << endl;
	cout << "	7. Tra sach.																			" << endl;
	cout << "	8. Lay thong tin cac quyen sach.														" << endl;
	cout << "	9. Lay thong tin 1 quyen sach.															" << endl;
	cout << "	10. Lay thong tin tat ca cac Ebook hien co.												" << endl;
	cout << "	11. Hien thi thong tin tat ca cac quyen sach da muon (User).							" << endl;
	cout << "	12. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon voi id nguoi dung (Admin).	" << endl;
	cout << "	13. Sua thong tin sach.																	" << endl;
	cout << "	14. Chinh sua thong tin ca nhan															" << endl;
	cout << "	15. Chinh sua thong tin ca nhan cua nguoi khac.											" << endl;
	cout << "	16. Dang xuat.																			" << endl;
	cout << "	17. Thoat chuong trinh.																	" << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;
}
int main() {
	// Person a("Tui", "Tui@gmail.com", "Nu", "14/02/2004", "Van Quan - Ha Dong", "0122345", "Sv");
	// a.In(a);
	DisplayMenu();
	// BorrowInfo a;
	// a.updateInfo();
	// cout << "Chon chuc nang ban muon su dung : ";
	// int input ; cin >> input;
	// cin.ignore();
	// if(input == 1){
	// 	string email, password ;
	//  	cout << "email cua ban la : ";
	// 	cin >> email;
	// 	cout << endl << "password cua ban la : ";
	// 	cin >> password;
	// 	cout << endl; 
	// }
	if (input == 2){
		cout << "------------------DANG KY------------------\n";
		string name, email, sex, birthdate, address, phoneNumber;
		cout << "Ho va ten: "; getline(cin, name);
		cout << "\nEmail: "; getline(cin, email);
		cout << "\nGioi tinh: "; getline(cin, sex);
		cout << "\nNgay sinh: "; getline(cin, birthdate);
		cout << "\nDia chi: "; getline(cin, address);
		cout << "\nSo dien thoai: "; getline(cin, phoneNumber);
		Person x(name, email, sex, birthdate, address, phoneNumber, "user");
		x.addPerson();
	}
	vector<Person> people = Person::getPerson();
	// for(auto x: people){
	// 	x.In(x);
	// 	cout << endl;
	// }
	// return 0;
}
