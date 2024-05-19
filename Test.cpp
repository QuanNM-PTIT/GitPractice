#include <iostream>
#include <string>

using namespace std;

int main() {
    string input;

    cout << "Please enter a line of text: ";
    cin >> input;

    if (input.empty()) {
        cout << "The input is an empty string." << endl;
    } else {
        cout << "You entered: \"" << input << "\"" << endl;
    }

    return 0;
}
