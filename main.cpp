#include <bits/stdc++.h>
using namespace std;
class Book;
class User;
class Person;
class BorrowInfo;
class Ebook;
vector<Book> v;
vector<User> v_user;
vector<Person> v_person; 
vector<BorrowInfo> v_borrowInfo; 
vector<Ebook> v_ebook;
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
			output << '[' << to_string(id) << "] "  << '[' << name << "] " << '[' << email << "] " << '[' << sex << "] " << '[' << birthdate << "] " << '[' << address << "] " << '[' << phoneNumber << "] "  << '[' << role << "] " << endl ;
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
	void updatePerson(int id, string name, string sex, string birthdate, string address, string phoneNumber){
		int check = 0;
		for(int i= 0; i< v_person.size(); i++){
			if(v_person[i].id == id){
				check = 1;
				v_person[i].name = name;
				v_person[i].sex = sex;
				v_person[i].birthdate = birthdate;
				v_person[i].address = address;
				v_person[i].phoneNumber = phoneNumber;
				break; 
			} 
		}
		if(check == 1){
			GhiDeFilePeople();
		} 
		if(check == 0){
			cout << "Khong tim thay thong tin\n";
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
	string getName(){
		return this->name; 
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
	void updateBorrowInfo(int id, int personId, int bookId, int ebookId){
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
			cout << "Khong tim thay ID sach da muon\n";
		}
	}
	void CapNhat(int i,int input){
		if(input == 1) 
			v_borrowInfo[i].ebookId = -1; 
		else{
			v_borrowInfo[i].bookId = -1; 
		} 
		if(v_borrowInfo[i].bookId == -1 && v_borrowInfo[i].ebookId == -1){
			v_borrowInfo.erase(v_borrowInfo.begin() + i); 
		}
		GhiDeFileBorrow(); 
	} 
	
	int getPersonId(){
		return this->personId;
	}
	int getBookId(){
		return this->bookId;
	}
	int getEbookId(){
		return this->ebookId;
	}
};
class Book{
	protected:
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
		
		void deleteBook(string title){
			int id = -1; 
			vector<int> Ma_Sach;
			int check = 1; 
			while(1){
				for(auto x : v){
				if(x.title == title){
					Ma_Sach.push_back(x.id);
					if(Ma_Sach.size() == 1){
						cout << "Ban muon xoa quyen nao ? \n"; 
					} 
					cout << x.Tong_Hop() << endl; 
				} 
				}
				if(Ma_Sach.size() == 0){
					check = 0; 
					cout << "Khong co sach nay trong kho \n";
					break; 
				}
				else{
					break; 
				} 	
			} 
			if(check == 1){
				int pick; cin >> pick;
				if(find(Ma_Sach.begin(), Ma_Sach.end(), pick) !=  Ma_Sach.end()){
					id = pick; 
				} 
				
				for(int i = 0; i<v.size(); i++){
					if(v[i].id == id){
						v.erase(v.begin() + i);
						break; 
					}
				}
				cout << "Xoa sach thanh cong \n"; 
				GhiDeFileBook();	
			} 
			
		}
		void print(){
			cout <<this->id << ' ' << this->title << ' ' << this->author << ' ' << this->quality << endl;
		}
		void print1(){
			cout << "ID sach: " <<this->id << "\nTen sach: " << this->title << "\nTac gia: " << this->author << endl;
		}
		int getId(){
			return this->id;
		}
		string getTitle(){
			return this->title;
		}
		string getAuthor(){
			return this->author;
		}
		int getQuality(){
			return this->quality;
		}
}; 
class Ebook : public Book{
private:
	string fileFormat;
	int fileSize;
public:
	Ebook (){} 
	Ebook (string title, string author, int quality, string fileFormat, int fileSize) : Book(title, author, quality){	
		this->fileFormat = fileFormat;
		this->fileSize = fileSize;
	} 
	string Tong_Hop(){
		return '[' + to_string(this->id) + "] " + '[' + this->title + "] " + '[' + this->author + "] " + '[' + to_string(this->quality) + "] " + '[' + this->fileFormat + "] " + '[' + to_string(this->fileSize) + "] " ;
	}
	bool operator < ( const Ebook& y){
		return this->id < y.id;
	}
	void SapXepFileEbooks(){
		sort(v_ebook.begin(), v_ebook.end()); 
	}	 
	void GhiDeFileEbooks(){
		ofstream output("ebooks.txt");
		if(output.is_open()){
			for(auto y : v_ebook){
				output << y.Tong_Hop() << endl;
			}
			output.close();
		}
		else{
			cout << "khong mo duoc file\n"; 
		}
	} 	
	void addEbook(){
			v_ebook.push_back(*this); 
			ofstream output("ebooks.txt", ios::app);
			if(output.is_open()){
				output << '[' << to_string(id) << "] "  << '[' << title << "] " << '[' << author << "] " << '[' << to_string(quality) << "] " << '[' << fileFormat << "] " << '[' << to_string(fileSize) << "] " << endl ;
				GhiDeFileEbooks();
				output.close(); 
			} 
			else{
				cout << "khong mo duoc file\n"; 
			} 
	} 
	void getEbooks(){
		v_ebook.clear(); 
		ifstream input("ebooks.txt");
		if(input.is_open()){
			string tmp;
			while(getline(input,tmp)){
				Ebook x;
				int start = 0, end = 0, i = 1;
				while(tmp.find('[', end) != -1){
					start =  tmp.find('[', end);
					end =  tmp.find(']', start);
					string tmp1 = tmp.substr(start + 1,end - start - 1); 
					if(i == 1)  x.id = stoi(tmp1) ; 
					else if (i == 2) x.title = tmp1 ;
					else if (i == 3) x.author = tmp1;
					else if(i == 4) x.quality = stoi(tmp1);
					else if(i == 5) x.fileFormat = tmp1;
					else  x.fileSize = stoi(tmp1);
					i++; 
				} 
				v_ebook.push_back(x); 
			}
			SapXepFileEbooks();
			GhiDeFileEbooks(); 
			input.close();
		}
		else{
			cout << "khong mo duoc file";
		}
	} 
	void updateEbook(int id, string title, string author, int quality, string fileFormat, int fileSize){
		int check = 0;
		for(int i= 0; i<v_ebook.size(); i++){
			if(v_ebook[i].id == id){
				check = 1;
				v_ebook[i].title = title;
				v_ebook[i].author = author;
				v_ebook[i].quality = quality;
				v_ebook[i].fileFormat = fileFormat;
				v_ebook[i].fileSize = fileSize;
				break; 
			} 
		}
		if(check == 1){
			GhiDeFileEbooks();
		} 
		if(check == 0){
			cout << "Khong ton tai id sach " << id << "\n";
		}
	}
	
	void deleteEbook(string title){
			int id = -1; 
			vector<int> Ma_Sach;
			int check = 1; 
			while(1){
				for(auto x : v_ebook){
				if(x.title == title){
					Ma_Sach.push_back(x.id);
					if(Ma_Sach.size() == 1){
						cout << "Ban muon xoa quyen nao ? \n"; 
					} 
					cout << x.Tong_Hop() << endl; 
				} 
				}
				if(Ma_Sach.size() == 0){
					check = 0; 
					cout << "Khong co sach nay trong kho \n";
					break; 
				}
				else{
					break; 
				} 	
			} 
			if(check == 1){
				int pick; cin >> pick;
				if(find(Ma_Sach.begin(), Ma_Sach.end(), pick) !=  Ma_Sach.end()){
					id = pick; 
				} 
				
				for(int i = 0; i<v_ebook.size(); i++){
					if(v_ebook[i].id == id){
						v_ebook.erase(v_ebook.begin() + i);
						break; 
					}
				}
				cout << "Xoa sach thanh cong \n"; 
				GhiDeFileEbooks();	
			} 
			
		}
	void print(){
		cout << this->id << ' ' << this->title << ' ' << this->author << ' ' << this->quality << ' ' << this->fileFormat << ' ' << this->fileSize << endl;
	}
	void print1(){
		cout << "ID ebook: " <<this->id << "\nTen ebook: " << this->title << "\nTac gia: " << this->author << "\nDinh dang file: " << this->fileFormat << "\nKich thuoc file: " << this->fileSize << endl;
	}
	int getId(){
		return this->id;
	}
	
	
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
		string getPassword(){
			return this->password;
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
						else if (i == 2){
							 x.email = tmp1 ;
						}
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
}; 

void DisplayMenu1(){
	cout << "-----------------------------------------------MENU--------------------------------------------" << endl;
	cout << "	1. Dang nhap.(H)																			" << endl;
	cout << "	2. Dang ky.(Y)																			" << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;	
}	
void DisplayMenuAdmin(){
	cout << "-----------------------------------------------------------------------------------------------" << endl;	
	cout << "	3. Them sach.(H)																			" << endl;
	cout << "	4. Sua thong tin sach.(Y)																" << endl;
	cout << "	5. Xoa sach.(H)																			" << endl;	
	cout << "	6. Hien thi tat ca cac quyen sach cua 1 nguoi dung da muon voi id nguoi dung (H).	" << endl;	
	cout << "	7. Chinh sua thong tin ca nhan cua nguoi khac.(H)											" << endl;

}
void DisplayMenuUser(){
	cout << "-----------------------------------------------------------------------------------------------" << endl; 
	cout << "	8. Muon sach.(Y)																			" << endl;
	cout << "	9. Tra sach.(H)																			" << endl;
	cout << "	10. Hien thi thong tin tat ca cac quyen sach da muon (Y).							" << endl;
} 
void DisplayMenuBoth(){
	cout << "	11. Lay thong tin cac quyen sach.(Y)														" << endl;
	cout << "	12. Lay thong tin 1 quyen sach.(H)														" << endl;
	cout << "	13. Lay thong tin tat ca cac Ebook hien co.(Y)												" << endl;
	cout << "	14. Lay thong tin 1 Ebook. (H)																" << endl;
	cout << "	15. Chinh sua thong tin ca nhan. (Y)															" << endl;
	cout << "	16. Dang xuat. (Y)																			" << endl;
	cout << "	17. Thoat chuong trinh. (H)																	" << endl;
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
Person DangNhap(){
	string u_email, u_password ;
	cout << "email cua ban la : ";
	cin >> u_email; 
	cout << "password cua ban la : ";
	cin >> u_password;
	cout << endl;
	while(1){
			int check = 0; 
			for(auto x : v_user){
				if((x.getEmail() == u_email) && (x.getPassword() != u_password)){
					cout << "password bi sai" << endl << "vui long nhap lai password" << endl;
					cin >> u_password; 
					break; 
				}
				else if((x.getEmail() == u_email) && (x.getPassword() == u_password)){
					check = 1; 
					break; 
				}
			}
			if(check == 1){
				cout << "Dang nhap thanh cong\n"; 
				for(auto x : v_person){
					if(x.getEmail() == u_email){
						return x; 
					} 
				} 
				break; 
			}
			else{
					cout << "thong tin dang nhap bi sai" << endl;
					cout << "email cua ban la : ";
					cin >> u_email;
					cout << "password cua ban la : ";
					cin >> u_password; 
			} 
	} 
	Person y;
	return y; 
}
Person DangKy(){
	// add person 
	string name, email, sex, birthdate, address, phoneNumber;
	cout << "Ho va ten: "; getline(cin, name);
	cout << "\nEmail: "; getline(cin, email);
	cout << "\nGioi tinh: "; getline(cin, sex);
	cout << "\nNgay sinh: "; getline(cin, birthdate);
	cout << "\nDia chi: "; getline(cin, address);
	cout << "\nSo dien thoai: "; getline(cin, phoneNumber);
	string  u_password;
	cout << "\nPassword: ";
	getline(cin,u_password);
	cout << endl; 
	check(email, u_password); 
	Person x(name, email, sex, birthdate, address, phoneNumber, "User");
	x.addPerson();
	cout << "Dang ky thanh cong!\n";
	cout << "Email cua ban la : " << email << endl;
	cout << "Password cua ban la : " << u_password << endl; 
	User y(email, u_password); 
	y.addUsers(); 
	return x;

}
void ManageBook(){
	int i;
	cout << "Chon 1 de sua sach, chon 2 de sua ebook.\n";
	cin >> i; 
	if(i == 1){
		string title, author;
		int id, quality;
		cout << "\nNhap ID sach: "; cin >> id; cin.ignore();
		cout << "\nNhap ten sach: "; getline(cin, title);
		cout << "\nNhap tac gia: "; getline(cin, author);
		cout << "\nNhap so luong: "; cin >> quality;
		Book x;
		x.updateBook(id, title, author, quality);
		return;
	}
	if(i == 2){
		string title, author, fileformat;
		int id, quality, filesize;
		cout << "Nhap ID sach: "; cin >> id; cin.ignore();
		cout << "\nNhap ten sach: "; getline(cin, title);
		cout << "\nNhap tac gia: "; getline(cin, author);
		cout << "\nNhap so luong: "; cin >> quality;
		cout << "\nNhap dinh dang file: "; cin >> fileformat;
		cout << "\nNhap kich thuoc file: "; cin >> filesize;
		Ebook x;
		x.updateEbook(id, title, author, quality, fileformat, filesize);
		return;
	}
}
void BorrowBook(int ID){
	bool check = false;
	for(auto person: v_person){
		if(person.getID() == ID){
			int id1 = ID;
			int id2 = -1, id3 = -1;
			cout << "Nhap ID Book: "; cin >> id2;
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
	if(!check) cout << "Loi khong muon duoc sach!\n";
}
void GetInfoBook(){
	cout << "Danh sach cac sach co trong thu vien:\n";
	for(auto temp: v){
		temp.print();
	}
}
void UpdatePersonInfo(Person x){
	cin.ignore();
	string name, sex, birthdate, address, phoneNumber;
	cout << "Nhap ho va ten: "; getline(cin, name);
	cout << "\nNhap gioi tinh: "; getline(cin, sex);
	cout << "\nNhap ngay sinh: "; getline(cin, birthdate);
	cout << "\nNhap dia chi: "; getline(cin, address);
	cout << "\nNhap so dien thoai: "; getline(cin, phoneNumber);
	int id = x.getID();
	x.updatePerson(id, name, sex, birthdate, address, phoneNumber);
}
void ShowBorrowInfoU(int personID){
	vector<int> IdB;
	vector<int> IdEb;
	for(BorrowInfo temp: v_borrowInfo){
		if(temp.getPersonId() == personID){
			if(temp.getBookId() > 0) IdB.push_back(temp.getBookId());
			if(temp.getEbookId() > 0) IdEb.push_back(temp.getEbookId());
		}
	}
	if (!IdB.empty()){
		cout << "Danh sach cac sach da muon:\n";
		cout << "ID" << " Ten" << " Tac gia" << " So luong" << endl;
		for(int x: IdB){
			for(auto temp: v){
				if (temp.getId() == x){
					temp.print1();
				}
			}
		}
	}
	else{
		cout << "Ban khong muon Book\n"; 
	} 
	// in ra thong tin ebook
	if(IdEb.size() > 0){
		cout << "Danh sach cac ebook da muon:\n";
		for(int x: IdEb){
			for(auto temp: v_ebook){
				if (temp.getId() == x){
					temp.print1();
				}
			}
		}
	}
	cout << "Ban khong muon ebook\n"; 
}

void GetInfoEbook(){
	cout << "ID" << " Ten" << " Tac gia" << " So luong" << " Dinh dang file" << " Kich thuoc file\n";
	for(Ebook tmp: v_ebook){
		tmp.print();
	}
}


void Them_Sach(){
	cout << "Ban muon them sach Ebook hay Book ? \n 1.Ebook\n 2.Book\n";
					int in; cin >> in; cin.ignore(); 
					if(in == 1){
						string m,n; 
						int SoLg; 
						cout << "Nhap ten sach : "; getline(cin,m);
						cout << "\nNhap ten tac gia : "; getline(cin,n);
						cout << "\nNhap so luong sach : "; cin >> SoLg; cin.ignore(); 
						string format;
						int sotrang;
						cout << "Dinh dang cua sach : "; getline(cin,format);
						cout << "\nSo luong trang sach : "; cin >> sotrang; 
						Ebook y(m, n, SoLg, format, sotrang);
						y.addEbook();
					}
					else{ 
						string m,n; 
						int SoLg; 
						cout << "Nhap ten sach : "; getline(cin,m);
						cout << "\nNhap ten tac gia : "; getline(cin,n);
						cout << "\nNhap so luong sach : "; cin >> SoLg; cin.ignore();
						Book x(m, n, SoLg); 
						x.addBook();
					} 
} 
void Xoa_Sach(){
	int pick; 
	cout << "Ban muon xoa Ebook hay Book ?\n 1.Ebook\n 2.Book\n"; cin >> pick; cin.ignore(); 
	string TenSach; 
	cout << "Ten sach muon xoa : "; getline(cin,TenSach);
	if(pick == 1){
		Ebook x;
		x.deleteEbook(TenSach); 
	} 
	else{
		Book x;
		x.deleteBook(TenSach); 
	} 
} 

void Sach_da_muon(){
	int id = -1; 
	cout << "ID cua nguoi muon : "; cin >> id; 
	int check = 0; 
	for(auto x : v_borrowInfo){
		if(x.getPersonId() == id){
			 check = 1; 
			if(x.getBookId() != -1){			
				for(auto y : v){
					if(y.getId() == x.getBookId()){
						cout << y.Tong_Hop();
						cout << "\n"; 
					} 
				} 
			}
			if(x.getEbookId() != -1){
				for(auto y : v_ebook){
					if(y.getId() == x.getEbookId()){
						cout << y.Tong_Hop();
						cout << "\n"; 
					} 
				} 
			} 
		} 
	}
	if(check == 0){
		cout << "Khong ton tai sach da muon\n"; 
	} 
} 

void Cap_Nhat_Thong_Tin(){
	int tid;
	cout << "ID nguoi dung muon cap nhat : "; cin >> tid; cin.ignore();
	cout << "Vui long nhap thong tin moi : \n";
	string tname,  temail,  tsex,  tbirthdate,  taddress,  tphoneNumber;
	cout << "\nTen nguoi dung : "; getline(cin,tname);
	cout << "\nGioi tinh : "; getline(cin,tsex);
	cout << "\nNgay sinh : "; getline(cin,tbirthdate);
	cout << "\nDia chi : "; getline(cin,taddress);
	cout << "\nSDT : "; getline(cin,tphoneNumber);
	Person x;
	x.updatePerson( tid, tname, tsex,  tbirthdate,  taddress,  tphoneNumber); 
	cout << "Sua thong tin thanh cong\n"; 
} 

void Tra_Sach(int ID_nguoi){	
		while(1){
			cout << "Tra loai sach nao ?\n 1.Ebook\n 2.Book\n";
	    	int input; cin >> input; 
	    	int ID_Sach; 
	    	cout << "ID sach : "; cin >> ID_Sach; 
			int check = 0; 
	    	for(int i = 0; i < v_borrowInfo.size(); i++){
	    		if(v_borrowInfo[i].getPersonId() == ID_nguoi){
	    			check = 1; 
					if(input == 1){
						if(v_borrowInfo[i].getEbookId() == ID_Sach){
							check = 2; 
							BorrowInfo x; 
							x.CapNhat(i, input);	 
							cout << "Tra sach thanh cong\n"; 
						} 
					}
					else{
						if(v_borrowInfo[i].getBookId() == ID_Sach){
							check = 2; 
							BorrowInfo x; 
							x.CapNhat(i, input);
							cout << "Tra sach thanh cong\n"; 
						}  
					}
					if(check == 2){
						break; 
					} 
				}		
			}
			if(check == 0){
				cout << " Ban da tra het sach \n";
				break; 
			}
			else if(check == 1){
				cout << "Ban khong muon ID sach nay \n"; 
			} 
			cout << "Ban co tra sach nua khong ?\n 1.Co\n 2.Thoat";
			int ktra = -1;
			int input1; cin >> input1;
			if(input1 == 2){
				break; 
			}	
		} 	
} 

void Get_Infor_One_Book(){
	while(1){
		int ID_Book; 
		cout << "Nhap id quyen sach ban can : "; cin >> ID_Book;
		int check = 0; 
		for(auto x : v){
			if(x.getId() == ID_Book){
				cout << x.Tong_Hop() << endl;
				check = 1; 
				break; 
			} 
		} 
		if(check == 0){
			cout << "Khong ton tai ID sach \n"; 
		} 
		cout << "Ban co muon biet them thong tin ve cuon sach nao nua khong ? \n 1. Co \n 2. Khong \n";
		int input; cin >> input;
		if(input == 2){
			break; 
		} 
	} 
	
} 
void Get_Infor_One_Ebook(){
	while(1){
		int ID_Ebook; 
		cout << "Nhap id quyen sach ban can : "; cin >> ID_Ebook;
		int check = 0; 
		for(auto x : v_ebook){
			if(x.getId() == ID_Ebook){
				cout << x.Tong_Hop() << endl;
				check = 1; 
				break; 
			} 
		} 
		if(check == 0){
			cout << "Khong ton tai ID sach \n"; 
		} 
		cout << "Ban co muon biet them thong tin ve cuon sach nao nua khong ? \n 1. Co \n 2. Khong \n";
		int input; cin >> input;
		if(input == 2){
			break; 
		} 
	} 
	
} 
int main(){
	Person a;
	a.getPerson();
	User b;
 	b.getusers(); 
	Book k;
	k.getBooks(); 
	BorrowInfo c;
	c.getBorrowInfo();
	Ebook d;
	d.getEbooks();
	bool success = false;
//	cin.ignore();
	Person x; 
	while(true){
		int thoat = 0; 
		if(!success){
			DisplayMenu1();
			int input;
			cout << "Chon chuc nang muon su dung: ";
			cin >> input; cout << endl;
			if(input == 1){
				x =  DangNhap();
				cout << "Welcome " << x.getName() << endl; 
				success = true;
			}
			else {
				cin.ignore();
				x = DangKy();
				success = true;
			}
		}
		if(success){
			if(x.getRole() == "Admin"){
			DisplayMenuAdmin();
			DisplayMenuBoth(); 
			} 
			else{
				DisplayMenuUser();
				DisplayMenuBoth(); 
			} 
			cout << "Chon chuc nang ban muon su dung : " << endl;
			int input2 = 0;
			cin >> input2;
			switch (input2){
				case 3:
					Them_Sach(); 
					break; 
				case 4:
					ManageBook();
					break;
				case 5:
					Xoa_Sach(); 
					break; 
				case 6:
					Sach_da_muon();
					break;
				case 7:
					Cap_Nhat_Thong_Tin(); 
					break; 
				case 8:
					BorrowBook(x.getID());	
					break;
				case 9:
					Tra_Sach(x.getID());
					break; 	 
				case 10:
					ShowBorrowInfoU(x.getID());
					break;
				case 11:
					GetInfoBook();
					break;
				case 12:
					Get_Infor_One_Book();
					break; 
				case 13:
					GetInfoEbook();
					break;
				case 14:
					Get_Infor_One_Ebook();
					break; 
				case 15: 
					UpdatePersonInfo(x);
					break;
				case 16:
					cout << "Dang xuat thanh cong!\n";
					success = false;
					break;
				case 17:
					cout << "Tam biet\n"; 
					thoat = 1; 
					break; 
				default:
					break;
			
			}
			if(thoat == 1){
				break; 
			} 
		}
	}
	
}


