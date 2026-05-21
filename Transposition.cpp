#include <bits/stdc++.h>
using namespace std;

int main() {
    string text, key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    int col = key.length();

    // add X until text length is divisible by column size
    while(text.length() % col != 0) {
        text += 'X';
    }

    string cipher = "";

    // read columns by key order
    for(char k = '1'; k <= '9'; k++) 
    {
        int colIndex = key.find(k);

        if(colIndex != -1) 
        {
            for(int i = colIndex; i < text.length(); i += col) 
            {
                cipher += text[i];
            }
        }
    }

    cout << "Encrypted Text: " << cipher;

    return 0;
}

/*================================Input & Output=============================

SAFAYET@SAFAYET MINGW64 /e/4th year/Cryptography/output
$ ./"Transposition.exe"
Enter text: SOUTHEASTUNIVERSITYBANGLADESH
Enter key: 573642
Encrypted Text: EITLXUTRAEHNIGHSAVYATUSNSOSEBD

==========================================================================*/