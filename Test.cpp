#include <bits/stdc++.h>

using namespace std;

vector<string> getInformationFromFile(const string& filename, int n) {
    vector<string> info;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find("] [")) != string::npos) {
            string token = line.substr(1, pos - 1);
            tokens.push_back(token);
            line.erase(0, pos + 2);
        }

        if (!line.empty()) {
            line.pop_back();
            line.erase(0, 1);
            tokens.push_back(line);
        }

        if (tokens.size() >= 3) {
            info.push_back(tokens[n]);
        }
    }
    file.close();
    return info;
}

bool isExistAlphaOrNum(string& s) {
    for (char c : s) {
        if (isalnum(c)) {
            return true;
        }
    }
    return false;
}

bool emailExists(const string& email) {
    vector<string> emails = getInformationFromFile("users.txt", 1);
    for (const string& e : emails) {
        if (e == email) {
            return true;
        }
    }
    return false;
}

// Hàm tạo ID mới cho người dùng
int getNewUserID(const string& filename) {
    ifstream file(filename);
    vector<string> dataID = getInformationFromFile(filename, 0);

    set<long long> dataIDInt;
    for (string s : dataID) {
        dataIDInt.insert(stoi(s));
    } 

    int mex = 0;
    for (auto it = dataIDInt.begin(); it != dataIDInt.end(); ++it) {\
        if (*it > mex + 1) {
            break;
        }
        mex = *it;
    }
    
    file.close();
    return ++mex;
}

// Hàm thêm người dùng mới vào file people.txt
void addUserToFile(const string& filename, const string& userInfo) {
    ofstream file(filename, ios_base::app);
    if (file.is_open()) {
        file << endl << userInfo;
        file.close();
    } else {
        cerr << "Unable to open file " << filename << endl;
    }
}

// Hàm đăng ký người dùng mới
void registerUser() {
    string fullName, email, gender, birthdate, address, phoneNumber, password;
    
    // Nhập thông tin từ người dùng
    cout << "Enter full name: ";
    getline(cin, fullName);

    while (isExistAlphaOrNum(fullName) == false) {
        cout << "Wrong format, please enter correct format, no special characters: ";
        scanf("\n");
        getline(cin, fullName);
    }

    cout << "Enter email: ";
    cin >> email;

    // Kiểm tra email đã tồn tại chưa
    while (emailExists(email)) {
        cout << "Email already exists. Please choose another email: ";
        cin >> email;
    }

    cout << "Enter gender: ";
    cin >> gender;

    while (isExistAlphaOrNum(gender) == false) {
        cout << "Wrong format, please enter correct format, no special characters: ";
        scanf("\n");
        cin >> gender;
    }

    cout << "Enter birthdate: ";
    cin >> birthdate;

    while (isExistAlphaOrNum(birthdate) == false) {
        cout << "Wrong format, please enter correct format, no special characters: ";
        scanf("\n");
        cin >> birthdate;
    }

    cout << "Enter address: ";
    cin.ignore();
    getline(cin, address);

    while (isExistAlphaOrNum(address) == false) {
        cout << "Wrong format, please enter correct format, no special characters: ";
        scanf("\n");
        cin >> address;
    }

    cout << "Enter phone number: ";
    cin >> phoneNumber;

    while (isExistAlphaOrNum(phoneNumber) == false) {
        cout << "Wrong format, please enter correct format, no special characters: ";
        scanf("\n");
        cin >> phoneNumber;
    }

    // Tạo ID mới cho người dùng
    int personID = getNewUserID("people.txt");

    // Ghi thông tin người dùng vào file people.txt
    string userInfo = "[" + to_string(personID) + "] [" + fullName + "] [" + email + "] [" + gender + "] [" + birthdate + "] [" + address + "] [" + phoneNumber + "] [User]";
    addUserToFile("people.txt", userInfo);

    // Nhập mật khẩu
    cout << "Create password: ";
    cin >> password;

    while (password == "" or password.size() < 8) {
        cout << "Your password is too weak, please enter a password longer than 8 characters!" << endl;
        cout << "Create password: ";
        cin >> password;
    }

    // Ghi email và mật khẩu vào file user.txt
    int userID = getNewUserID("users.txt");
    ofstream userFile("users.txt", ios_base::app);
    if (userFile.is_open()) {
        userFile << endl << "[" + to_string(userID) + "] [" + email + "] [" + password + "]";
        userFile.close();
        cout << "Registration successful!" << endl;
    } 
    else {
        cerr << "Unable to open file users.txt" << endl;
    }
}

int main() {
    registerUser();
    return 0;
}
