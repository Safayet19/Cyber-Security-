#include <bits/stdc++.h>
using namespace std;

int main() {
    string text;
    int key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    // key = ((key % 26) + 26) % 26;

    for (int i = 0; i < text.length(); i++) 
    {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = char((text[i] - 'a' + key) % 26 + 'a');
        } 
        else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = char((text[i] - 'A' + key) % 26 + 'A');
        }
      
    }

    cout << "Result: " << text ;

}