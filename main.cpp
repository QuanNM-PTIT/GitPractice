#include <bits/stdc++.h>
using namespace std;
int IdPerson = 0, borrowInfoId = 0;
class Person; 
class Book;
vector<Book> v;

void CapNhatIdPerson(){
	ifstream input("F:\\Project\\GitPractice\\people.txt");
	vector<string> v;
	if(input.is_open()){
		string s;
		while(getline(input, s)){
			v.push_back(s);
		}
		IdPerson = v.size();
		input.close();
	}
	else{
		cout << "Khong mo duoc file\n" ;
	}
}
void CapNhatBorrowInfoId(){
	ifstream input("F:\\Project\\GitPractice\\borrowInfos.txt");
	vector<string> v;
	if(input.is_open()){
		string s;
		while(getline(input, s)){
			v.push_back(s);
		}
		borrowInfoId = v.size();
		input.close();
	}
	else{
		cout << "Khong mo duoc file\n" ;
	}
}

class Person{
private:
    int id;
    string name = "", email = "", sex = "", birthdate = "", phoneNumber = "", role = "", address = "";
public:
	Person(){
		CapNhatIdPerson();
		IdPerson++;
		this->id = IdPerson;
	}
    Person(string name, string email, string sex, string birthdate, string address, string phoneNumber, string role){
    	CapNhatIdPerson();
        IdPerson++;
        this->id = IdPerson;
        this->name = name;
        this->email = email;
        this->sex = sex;
        this->birthdate = birthdate;
        this->address = address;
        this->phoneNumber = phoneNumber;
    }
    void In(Person x){
        cout << x.name << ' ' << x.email << ' ' << x.sex << endl;
    }

};
class BorrowInfo{
private:
    int id, personId = 0, bookId = 0, ebookId = 0;
public:
	BorrowInfo() {
        CapNhatBorrowInfoId();
        borrowInfoId++;
        this->id = borrowInfoId;
    }
    BorrowInfo(int personId, int bookId, int ebookId ){
    	CapNhatBorrowInfoId();
        borrowInfoId++;
        this->id = borrowInfoId;
        this->personId = personId;
        this->bookId = bookId;
        this->ebookId = ebookId;
    }
    void addInfo(){
    	int Id1, Id2, Id3;
    	cout << "Nhap personId: ";
    	cin >> Id1;
   		cout << "Nhap ID sach: ";
   		cin >> Id2;
   		cout << "Nhap ID Ebook: ";
   		cin >> Id3;
        ofstream output("F:\\Project\\GitPractice\\borrowInfos.txt", ios::app);
		if (output.is_open()){
			output << endl;
			output << '[' << id  << ']'  << ' '  << '[' << Id1 << ']' << ' '  << '[' << Id2 << ']' << ' '  << '[' << Id3 << ']';
        	output.close();
		}
        else {
        	cout << "Khong mo duoc file\n";
		}
    }
//	void updateInfor() 
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
int main() {
	 
	
	return 0;
}
