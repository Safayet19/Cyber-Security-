#include<bits/stdc++.h>
using namespace std;

// Initial Permutation table
int IP[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

// Expansion table, 32 bits to 48 bits
int E[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

// P permutation table
int P[32] = {
    16,7,20,21,
    29,12,28,17,
    1,15,23,26,
    5,18,31,10,
    2,8,24,14,
    32,27,3,9,
    19,13,30,6,
    22,11,4,25
};

// PC2 table, 56-bit key to 48-bit round key
int PC2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

// DES S-boxes
int S[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// Convert hex string to binary string
string hexToBin(string s)
{
    string ans = "";

    for(char c : s)
    {
        if(c == '0') ans += "0000";
        else if(c == '1') ans += "0001";
        else if(c == '2') ans += "0010";
        else if(c == '3') ans += "0011";
        else if(c == '4') ans += "0100";
        else if(c == '5') ans += "0101";
        else if(c == '6') ans += "0110";
        else if(c == '7') ans += "0111";
        else if(c == '8') ans += "1000";
        else if(c == '9') ans += "1001";
        else if(c == 'A' || c == 'a') ans += "1010";
        else if(c == 'B' || c == 'b') ans += "1011";
        else if(c == 'C' || c == 'c') ans += "1100";
        else if(c == 'D' || c == 'd') ans += "1101";
        else if(c == 'E' || c == 'e') ans += "1110";
        else if(c == 'F' || c == 'f') ans += "1111";
        else
        {
            cout << "Invalid hex character\n";
            exit(0);
        }
    }

    return ans;
}

// Convert binary string to hexadecimal string
string binToHex(string s)
{
    string ans = "";

    for(int i = 0; i < (int)s.size(); i += 4)
    {
        string part = s.substr(i, 4);

        if(part == "0000") ans += '0';
        else if(part == "0001") ans += '1';
        else if(part == "0010") ans += '2';
        else if(part == "0011") ans += '3';
        else if(part == "0100") ans += '4';
        else if(part == "0101") ans += '5';
        else if(part == "0110") ans += '6';
        else if(part == "0111") ans += '7';
        else if(part == "1000") ans += '8';
        else if(part == "1001") ans += '9';
        else if(part == "1010") ans += 'A';
        else if(part == "1011") ans += 'B';
        else if(part == "1100") ans += 'C';
        else if(part == "1101") ans += 'D';
        else if(part == "1110") ans += 'E';
        else if(part == "1111") ans += 'F';
    }

    return ans;
}

// Apply permutation table
string permute(string s, int table[], int n)
{
    string ans = "";

    for(int i = 0; i < n; i++)
    {
        ans += s[table[i] - 1];
    }

    return ans;
}

// Circular left shift
string leftShift(string s, int shift)
{
    while(shift--)
    {
        char first = s[0];
        s.erase(s.begin());
        s += first;
    }

    return s;
}

// XOR two binary strings
string xorString(string a, string b)
{
    string ans = "";

    for(int i = 0; i < (int)a.size(); i++)
    {
        if(a[i] == b[i]) ans += '0';
        else ans += '1';
    }

    return ans;
}

// Convert decimal 0 to 15 into 4-bit binary
string decimalToBinary(int x)
{
    string ans = "";

    for(int i = 3; i >= 0; i--)
    {
        if((x >> i) & 1) ans += '1';
        else ans += '0';
    }

    return ans;
}

// S-box substitution, 48 bits to 32 bits
string sBox(string s)
{
    string ans = "";

    for(int i = 0; i < 8; i++)
    {
        string block = s.substr(i * 6, 6);

        // First and last bit make row
        int row = (block[0] - '0') * 2 + (block[5] - '0');

        // Middle four bits make column
        int col = (block[1] - '0') * 8 +
                  (block[2] - '0') * 4 +
                  (block[3] - '0') * 2 +
                  (block[4] - '0');

        int val = S[i][row][col];

        ans += decimalToBinary(val);
    }

    return ans;
}

// DES f function
string fFunction(string right, string roundKey)
{
    // Expand right half from 32 bits to 48 bits
    string expanded = permute(right, E, 48);

    // XOR with round key
    string xored = xorString(expanded, roundKey);

    // Apply S-box
    string afterSBox = sBox(xored);

    // Apply P permutation
    string afterP = permute(afterSBox, P, 32);

    return afterP;
}

//=========================Main Function================================

int main()
{
    int round, shift;
    string plain_text, key;

    //take input of plain text , key and round
    cout<<"Enter 16 (64 bits) characters plain text (in hexadecimal):" ;
    cin>>plain_text;

    cout<<"Enter 14 (56 bits) characters key (in hexadecimal):" ;
    cin>>key;

    cout<<"Enter Round Number:" ;
    cin>>round;

    // input taking corner case handling
    if(plain_text.size() != 16)
    {
        cout << "Plain text must be 16 hex characters\n";
        return 0;
    }

    if(key.size() != 14)
    {
        cout << "Key must be 14 hex characters\n";
        return 0;
    }

    if(round < 1 || round > 16)
    {
        cout << "Round must be between 1 and 16\n";
        return 0;
    }

    // convert input into binary
    plain_text = hexToBin(plain_text);
    key = hexToBin(key);

    //========================Key Generation===========================

    // Split 56-bit key into two 28-bit parts
    string left_key = key.substr(0, 28);
    string right_key = key.substr(28, 28);

    // Store round keys
    vector<string> roundKey(17);

    for(int i = 1; i <= round; i++)
    {
        // 1, 2, 9, 16 hole 1 ghor shift hobe, else 2 ghor
        if(i == 1 || i == 2 || i == 9 || i == 16)
            shift = 1;
        else
            shift = 2;

        // Shift both key halves
        left_key = leftShift(left_key, shift);
        right_key = leftShift(right_key, shift);

        // Combine 28 + 28 = 56 bits
        string combined_key = left_key + right_key;

        // Compress 56 bits to 48 bits
        roundKey[i] = permute(combined_key, PC2, 48);
    }

    cout << "\nRound Key K" << round << ":\n";
    cout << roundKey[round] << "\n";

    //========================Initial Permutation===========================

    // Apply initial permutation
    string ip = permute(plain_text, IP, 64);

    // Split into L0 and R0
    string left = ip.substr(0, 32);
    string right = ip.substr(32, 32);

    cout << "\nAfter Initial Permutation:\n";
    cout << "L0: " << left << "\n";
    cout << "R0: " << right << "\n";

    //========================DES Round Encryption===========================

    for(int i = 1; i <= round; i++)
    {
        string old_left = left;
        string old_right = right;

        // f function using current round key
        string function_output = fFunction(old_right, roundKey[i]);

        // DES round formula
        left = old_right;
        right = xorString(old_left, function_output);
    }

    cout << "\nAfter Round " << round << ":\n";
    cout << "L" << round << ": " << left << "\n";
    cout << "R" << round << ": " << right << "\n";

    string binary_cipher = left + right;
    string hex_cipher = binToHex(binary_cipher);

    cout << "\nBinary Cipher Text After Round " << round << ":\n";
    cout << binary_cipher << "\n";

    cout << "\nHexadecimal Cipher Text After Round " << round << ":\n";
    cout << hex_cipher << "\n";

    return 0;
}

/*================================Input & Output=============================

SAFAYET@SAFAYET MINGW64 /e/4th year/Cryptography/output
$ ./"Single_Round_DES_Encryption.exe"
Enter 16 (64 bits) characters plain text (in hexadecimal):0123456789ABCDEF
Enter 14 (56 bits) characters key (in hexadecimal):133457799BBCDF    
Enter Round Number:2

Round Key K2:
000101000111001010100101111111101001101011011000

After Initial Permutation:
L0: 11001100000000001100110011111111
R0: 11110000101010101111000010101010

After Round 2:
L2: 00010101011111001110010011001100
R2: 11101111101110110100110110011011

Binary Cipher Text After Round 2:
0001010101111100111001001100110011101111101110110100110110011011

Hexadecimal Cipher Text After Round 2:
157CE4CCEFBB4D9B

===========================================================================*/