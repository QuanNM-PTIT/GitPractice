#include <bits/stdc++.h>

using namespace std;

void deleteBook(string idToRemove){
    const string& filename = "books.txt";
    ifstream inFile(filename); // File input stream
    ofstream outFile("temp_books.txt"); // Temporary file output stream

    if (!inFile.is_open()) {
        cerr << "Không thể mở file." << endl;
        return;
    }

    string line;
    bool found = false; // Flag to track if book with specified ID is found

    // Đọc từng dòng từ file gốc
    while (getline(inFile, line)) {
        size_t startPos = line.find("["); // Tìm vị trí của ký tự '['
        size_t endPos = line.find("]", startPos); // Tìm vị trí của ký tự ']' sau ký tự '['
        
        if (startPos != string::npos && endPos != string::npos) {
            string bookId = line.substr(startPos + 1, endPos - startPos - 1);

            if (bookId == idToRemove) {
                found = true; // Đánh dấu là đã tìm thấy cuốn sách cần xoá
                continue; // Bỏ qua việc ghi dòng này vào file tạm thời
            }
        }

        // Ghi lại dòng vào file tạm thời
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    if (found) {
        // Xoá file gốc
        if (remove(filename.c_str()) != 0) {
            cerr << "Không thể xoá file gốc." << endl;
            return;
        }

        // Đổi tên file tạm thời thành file gốc
        if (rename("temp_books.txt", filename.c_str()) != 0) {
            cerr << "Không thể đổi tên file tạm thời." << endl;
            return;
        }

        cout << "Đã xoá thông tin của cuốn sách có ID = " << idToRemove << " thành công." << endl;
    } 
    else {
        // Xoá file tạm thời nếu không tìm thấy cuốn sách cần xoá
        remove("temp_books.txt");
        cout << "Không tìm thấy cuốn sách có ID = " << idToRemove << " trong file." << endl;
    }
}

int main() {
    deleteBook("6");
    return 0;
}