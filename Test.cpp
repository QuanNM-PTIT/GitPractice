#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Hàm để đọc thông tin từ file và lưu vào một vector các dòng
vector<string> getInformationFromFile(const string& filename, int n) {
    vector<string> info;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
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

// Hàm để ghi lại thông tin từ vector các dòng vào file
void writeBookInfoToFile(const string& filename, const vector<vector<string>>& bookInfo) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Không thể mở file." << endl;
        return;
    }
    for (const vector<string>& book : bookInfo) {
        for (size_t i = 0; i < book.size(); ++i) {
            file << "[" << book[i] << "]";
            if (i < book.size() - 1) {
                file << " ";
            }
        }
        file << endl;
    }
    file.close();
}

int main() {
    // string filename = "books.txt";

    // // Đọc thông tin từ file và lưu vào vector bookInfo
    // vector<vector<string>> bookInfo = readBookInfoFromFile(filename);

    // // Tìm vị trí của cuốn sách có id = 6 trong vector bookInfo
    // int idToUpdate = 6;
    // int idPos = -1;
    // for (size_t i = 0; i < bookInfo.size(); ++i) {
    //     if (!bookInfo[i].empty() && bookInfo[i][0] == to_string(idToUpdate)) {
    //         idPos = i;
    //         break;
    //     }
    // }

    // // Kiểm tra xem cuốn sách có id = 6 có tồn tại không
    // if (idPos == -1) {
    //     cout << "Không tìm thấy cuốn sách có id = " << idToUpdate << endl;
    // } else {
    //     // Thay đổi thông tin của cuốn sách tại vị trí idPos bằng thông tin mới
    //     string change = "[6] [C++] [LQM] [100]";
    //     bookInfo[idPos] = { "6", "C++", "LQM", "100" }; // hoặc có thể dùng change

    //     // Ghi lại các thông tin đã được cập nhật vào file
    //     writeBookInfoToFile(filename, bookInfo);

    //     cout << "Thông tin của cuốn sách có id = " << idToUpdate << " đã được cập nhật thành công!\n";
    // }

    ifstream file("books.txt");
    string line;
    int cnt = 0;

    while (getline(file, line)) {
        ++cnt;
    }

    file.close();

    vector<vector<string>> bookInfor(4);

    for (int i = 0; i < 4; ++i) {
        bookInfor[i] = getInformationFromFile("books.txt", i);
    }

    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << "[" << bookInfor[j][i] << "] ";
        }
        cout << endl;
    } 
    return 0;
}
