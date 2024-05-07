#include <bits/stdc++.h>
using namespace std;
int IdPerson = 0, borrowInfoId = 0;
class Person;
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
int main() {
	return 0;
}