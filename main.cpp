#include <bits/stdc++.h>
using namespace std;
class Book;
class User;
class Person;
class BorrowInfo;
vector<Book> v;
vector<User> v_user;
vector<Person> v_person; 
vector<BorrowInfo> v_borrowInfo;
class Person{
private:
    int id;
    string name = "", email = "", sex = "", birthdate = "", phoneNumber = "", role = "", address = "";
public:
	Person(){
	}
    Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role){
        if(v_person.size() == 0){
			 	this->id = 1;
			 } 
		else{
			this->id = v_person[v_person.size()-1].id + 1;
		} 
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
		return '[' + to_string(this->id) + "] " + '[' + this->name + "] " + '[' + this->email + "] " + '[' + sex + "] " + '[' + this->birthdate + "] " + '[' + this->address + "] " + '[' + this->phoneNumber + "] "+ '[' + this->role + "] ";
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
	void getPerson(){
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
			SapXepFilePeople();
			GhiDeFilePeople(); 
			input.close();
		}
		else{
			cout << "khong mo duoc file";
		}
	}
	string getRole(){
		return this->role;
	}
	string getEmail(){
		return this->email;
	}
	int getID(){
		return this->id;
	}
};
class BorrowInfo{
private:
    int id, personId = 0, bookId = 0, ebookId = 0;
public:
	BorrowInfo() {
    }
    BorrowInfo(int personId, int bookId, int ebookId ){
       if(v_borrowInfo.size() == 0){
			 	this->id = 1;
			} 
		else{
			this->id = v_borrowInfo[v_borrowInfo.size()-1].id + 1;
		} 
        this->personId = personId;
        this->bookId = bookId;
        this->ebookId = ebookId;
    }
	string Tong_Hop(){
			return '[' + to_string(this->id) + "] " + '[' + to_string(this->personId) + "] " + '[' + to_string(this->bookId) + "] " + '[' + to_string(this->ebookId) + "] ";
		}
	bool operator < ( const BorrowInfo& y){
		return this->id < y.id;
	}
	void SapXepFileBorrow(){
		sort(v_borrowInfo.begin(), v_borrowInfo.end()); 
	}	 
	void GhiDeFileBorrow(){
		ofstream output("borrowInfos.txt");
		if(output.is_open()){
			for(auto y : v_borrowInfo){
				output << y.Tong_Hop() << endl;
			}
			output.close();
		}
		else{
			cout << "khong mo duoc file\n"; 
		}
	} 
	void addInfo(){ // them thong tin muon sach 
		v_borrowInfo.push_back(*this);
        ofstream output("borrowInfos.txt", ios::app);
		if (output.is_open()){
			output << endl;
			output << '[' << to_string(id)  << ']'  << ' '  << '[' <<  to_string(personId) << ']' << ' '  << '[' << to_string(bookId) << ']' << ' '  << '[' << to_string(ebookId) << ']';
        	output.close();
		}
        else {
        	cout << "Khong mo duoc file\n";
		}
    }
	void getBorrowInfo(){
		v_borrowInfo.clear(); 
		ifstream input("borrowInfos.txt");
		
		if(input.is_open()){
			string tmp;
			while(getline(input,tmp)){
				BorrowInfo x;
				int start = 0, end = 0, i = 1;
				while(tmp.find('[', end) != -1){
					start =  tmp.find('[', end);
					end =  tmp.find(']', start);
					string tmp1 = tmp.substr(start + 1,end - start - 1); 
					if(i == 1)  x.id = stoi(tmp1) ; 
					else if (i == 2) x.personId = stoi(tmp1) ;
					else if (i == 3) x.bookId = stoi(tmp1);
					else  x.ebookId = stoi(tmp1);
					i++; 
				} 
				v_borrowInfo.push_back(x); 
			}
			SapXepFileBorrow();
			GhiDeFileBorrow(); 
			input.close();
		}
		else{
			cout << "khong mo duoc file";
		}
	} 
	void updateBook(int id, int personId, int bookId, int ebookId){
		int check = 0;
		for(int i= 0; i< v_borrowInfo.size(); i++){
			if(v_borrowInfo[i].id == id){
				check = 1;
				v_borrowInfo[i].personId = personId;
				v_borrowInfo[i].bookId= bookId;
				v_borrowInfo[i].ebookId = ebookId;
				break; 
			} 
		}
		if(check == 1){
			GhiDeFileBorrow();
		} 
		if(check == 0){
			cout << "Khong tim thay ID muon\n";
		}
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

class User{
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
		string getEmail(){
			return this->email; 
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
				
		void addUsers(){
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

void check(string &tmp_email , string &tmp_password){ 
		while(1){
			int n = tmp_email.size();
			int check_email = 1; 
			for(auto y : v_user){
				if(y.getEmail() == tmp_email){
					check_email = 0; 
					cout << "email da ton tai! \nVui long chon email khac\n";
					break; 
				}
			}
			if(check_email == 0){
				cout << "Email dang ky : "; 
				cin >> tmp_email;
				cout << endl; 
			}	 
			else{ 
				if(tmp_email.size() <= 10){
					cout << "email khong hop le \nVui long chon email khac\n";
					check_email = 0; 
					cout << "Email dang ky : "; 
					cin >> tmp_email;
					cout << endl;
				} 
				if(check_email == 1 && tmp_email.substr(n-10,10) != "@gmail.com"){
					cout << "duoi email khong hop le \nVui long chon email khac\n";
					check_email = 0; 
					cout << "Email dang ky : "; 
					cin >> tmp_email;
					cout << endl;  
				}
			}
			if(check_email == 1){
				break; 
			} 
		}		
		while(1){
			int check_password = 0;
			string tmp2 = tmp_password;
			for(int i=0; i<tmp2.size(); i++){
				if(tmp2[i] >= '0' && tmp2[i] <= '9'){
					check_password = 1;
					break;
				}
			}
			if(check_password == 0){
				cout << "mat khau bao gom ca chu va so \nVui long chon password khac\n";
				cout << "Password : "; 
				cin >> tmp_password;
				cout << endl; 
			}
			else{
				for(int i=0; i<=tmp2.size(); i++){
					if((tmp2[i] >= 'a' && tmp2[i] <= 'z') || (tmp2[i] >= 'A' && tmp2[i] <= 'Z')){
						check_password = 2;
						break;
					}
				}
				if(check_password != 2){
					cout << "mat khau bao gom ca chu va so \nVui long chon password khac\n";
					cout << "Password : "; 
					cin >> tmp_password;
					cout << endl;
				}
			} 
			if(check_password == 2){
				break; 
			} 
			
		} 
		
}
string DangNhap(){
	string u_email, u_password ;
	cout << "email cua ban la : ";
	cin >> u_email;
	cout << "password cua ban la : ";
	cin >> u_password;
	cout << endl;
	cout << "Dang nhap thanh cong!\n";
	return u_email;
}
string DangKy(){
	cout << "------------------DANG KY------------------\n";
	// add person 
	string name, email, sex, birthdate, address, phoneNumber;
	cout << "Ho va ten: "; getline(cin, name);
	cout << "\nEmail: "; getline(cin, email);
	cout << "\nGioi tinh: "; getline(cin, sex);
	cout << "\nNgay sinh: "; getline(cin, birthdate);
	cout << "\nDia chi: "; getline(cin, address);
	cout << "\nSo dien thoai: "; getline(cin, phoneNumber);
	Person x(name, email, sex, birthdate, address, phoneNumber, "User");
	x.addPerson();
	// add user;
	string u_email, u_password;
	cout << "\nEmail dang ky : "; 
	getline(cin, u_email) ;
	cout << "\nPassword: ";
	getline(cin,u_password);
	cout << endl; 
	check(u_email, u_password); 
	cout << "Dang ky thanh cong!\n";
	cout << "Email cua ban la : " << u_email << endl;
	cout << "Password cua ban la : " << u_password << endl; 
	User y(u_email, u_password); 
	y.addUsers(); 
	return u_email;
}
void ManageBook(string u_email){
	bool check = false;
	for(auto person: v_person){
		if(person.getEmail() == u_email){
			if(person.getRole() == "Admin"){
				string title, author;
				int id, quality;
				cout << "Nhap ID sach: "; cin >> id; cin.ignore();
				cout << "\nNhap ten sach: "; getline(cin, title);
				cout << "\nNhap tac gia: "; getline(cin, author);
				cout << "\nNhap so luong: "; cin >> quality;
				Book x;
				x.updateBook(id, title, author, quality);
				check = true;
				return;
			}
		}
	}
	if(!check) cout << "Loi khong sua duoc sach!\n";
}
void BorrowBook(string u_email){
	bool check = false;
	for(auto person: v_person){
		if(person.getEmail() == u_email){
			if(person.getRole() == "User"){
				int id1 = person.getID();
				int id2 = -1, id3 = -1;
				cout << "Nhap ID sach: "; cin >> id2;
				// Need: check id sach co ton tai khong
				cout << "\nNhap Id ebook: "; cin >> id3; 	
				// Need: check xem id ebook co ton tai khong 
				BorrowInfo x(id1, id2, id3);
				x.addInfo();
				check = true;
				cout << "\nMuon sach thanh cong!\n";
				return;
			}
		}
	}
	if(!check) cout << "Loi khong muon duoc sach!\n";
}
int main() {
//	DisplayMenu();
	Person a;
	a.getPerson();
	BorrowInfo b;
	b.getBorrowInfo();
	// BorrowBook ("james.anderson@gmail.com");
	// Person b("Yen", "abc@gmail.com", "fermale", "10/02", "Van Quan", "123434", "user");
	// b.addPerson();
//  chuyen vao vector
	// User x;
 	// x.getusers(); 
	// Book k;
	// k.getBooks();
	// int input;
	// bool success = false;
	// string u_email;
	// while(!success){
	// 	cout << "Chon chuc nang ban muon su dung : ";
	// 	cin >> input;
	// 	cin.ignore();
	// 	if(input == 1){
	// 		u_email = DangNhap();
	// 		success = true;
	// 	}
	// 	else if(input == 2){
	// 		u_email = DangKy();
	// 		success = true;
	// 	} 
	// 	else cout << "Vui long dang nhap/dang ky!\n";
	// }
	// if(success){
	// 	cout << "Chon chuc nang ban muon su dung : ";
	// 	cin >> input;
	// 	switch(input){
	// 		case 1:
	// 			//Dang Nhap
	// 			break;
	// 		case 2:
	// 			//Dang ky
	// 			break;
	// 		case 3:
	// 			break; 
	// 		case 4: // sua thong tin sach
	// 			ManageBook(u_email);
	// 			break;
	// 		case 5:
	// 			break;
	// 		case 6: // Muon sach
	// 			BorrowBook(u_email);
	// 			break;
	// 		default: 
	// 			break;
	// 	}
	// }
	// return 0;
}

