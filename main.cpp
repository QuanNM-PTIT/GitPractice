#include <bits/stdc++.h>
using namespace std;
class Person;
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
    }
    void In(Person x){
        cout << x.id << ' ' << x.name << ' ' << x.email << ' ' << x.sex << endl;
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
void DisplayMenu(){
	cout << "--------------------MENU--------------------" << endl;
	cout << "2. Dang ky." << endl;
	cout << "4. Sua thong tin sach." << endl;
	cout << "6. Muon sach." << endl;
	cout << "8. Lay thong tin cac quyen sach." << endl;
	cout << "10. Lay thong tin tat ca cac Ebook hien co." << endl;
	cout << "12. Hien thi thong tin tat ca cac quyen sach da muon." << endl;
	cout << "14. Chinh sua thong tin ca nhan" << endl;
	cout << "16. Dang xuat." << endl;
	cout << "---------------------------------------------" << endl;
	

}
int main() {
	// Person a("Tui", "Tui@gmail.com", "Nu", "14/02/2004", "Van Quan - Ha Dong", "0122345", "Sv");
	// a.In(a);
//	DisplayMenu();
	BorrowInfo a;
	a.updateInfo();
	return 0;
}