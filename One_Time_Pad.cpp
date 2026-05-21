#include <bits/stdc++.h>
using namespace std;

int main() {
    string text, key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    getline(cin, key);

    if (key.length() < text.length()) {
        cout << "Key must be same length or bigger than text";
        return 0;
    }

    for (int i = 0; i < text.length(); i++) 
    {
        if (text[i] >= 'a' && text[i] <= 'z') {
            int shift = key[i] - 'a';
            text[i] = char((text[i] - 'a' + shift) % 26 + 'a');
        } 
        else if (text[i] >= 'A' && text[i] <= 'Z') {
            int shift = key[i] - 'A';
            text[i] = char((text[i] - 'A' + shift) % 26 + 'A');
        }
    }

    cout << "Encrypted Text: " << text;

    return 0;
}

/*================================Input & Output=============================

SAFAYET@SAFAYET MINGW64 /e/4th year/Cryptography/output
$ ./"One_Time_Pad.exe"
Enter text: HELLO
Enter key: XMCKL
Encrypted Text: EQNVZ

==========================================================================*/