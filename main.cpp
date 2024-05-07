#include <bits/stdc++.h>

using namespace std;

class Person{
	private:
		int id;
		string 	name, email, sex, birthday, 
				address, phoneNumber, role;
		
	public:
		friend istream& operator >> (istream &in, Person &a);
		friend ostream& operator << (ostream &out, Person a);
};

istream& operator >> (istream &in, Person &a)
{
	in >> a.id;
	scanf("\n");
	getline(in, a.name);
	in >> a.role;
	return in;
}

ostream& operator << (ostream &out, Person a)
{
	out << a.id << " " << a.name << " " << a.role << endl;
	return out;
}

class User{
	private:
		int id;
		string email, password;
};

int main() {
    Person a;
	cin >> a;
	cout << a;
    return 0;
}