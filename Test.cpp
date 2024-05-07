#include <bits/stdc++.h>

using namespace std;

vector<string> getInformationFromFile(string filename, int n) {
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
            tokens.push_back(line);
        }
        if (tokens.size() >= 3) {
            info.push_back(tokens[n]);
        }
    }
    file.close();
    return info;
}

int main() {
    vector<string> name = getInformationFromFile("people.txt", 1);
    vector<string> sex = getInformationFromFile("people.txt", 3);
    for (string s : sex) {
        cout << s << endl;
    }
    return 0;
}