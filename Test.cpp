#include <bits/stdc++.h>

using namespace std;

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

template <class val>
bool isExist(const val infoNeedCheck, const string& filename, int dataPos) {
    vector<val> info = getInformationFromFile(filename, dataPos);
    for (auto s : info) {
        if (s == infoNeedCheck) {
            return true;
        }
    }
    return false;
}
int main() {
    string check = "Emily Davis";
    cout << isExist(check, "people.txt", 1);
    return 0;
}