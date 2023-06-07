#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FAST                     \
    ios::sync_with_stdio(false); \
    cin.tie(NULL);               \
    cout.tie(NULL);

// Permutation Tables and S-Boxes
vector<int> PermutationP10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
vector<int> PermutationP8 = {6, 3, 7, 4, 8, 5, 10, 9};
vector<int> Initial_Permutation_IP = {2, 6, 3, 1, 4, 8, 5, 7};
vector<int> Expanded_Permutation_EP = {4, 1, 2, 3, 2, 3, 4, 1};
vector<int> PermutationP4 = {2, 4, 3, 1};
vector<int> Inverse_of_Inital_Permuation_IP_inv = {4, 1, 3, 5, 7, 2, 8, 6};
vector<vector<int>> S_Box_0 = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
vector<vector<int>> S_Box_1 = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

// Variables to store generated 8-bit keys
vector<int> key1_8bits(8), key2_8bits(8);

// Function to convert a decimal value to a binary string
string Binary__(int value)
{
    if (value == 0)
    {
        return "00";
    }
    else if (value == 1)
    {
        return "01";
    }
    else if (value == 2)
    {
        return "10";
    }
    else
    {
        return "11";
    }
}

// Function to swap the bits of a given array
vector<int> swap_bits(vector<int> arr, int sizes)
{
    vector<int> left(sizes), right(sizes);

    for (int i = 0; i < sizes; i++)
    {
        left[i] = arr[i];
        right[i] = arr[i + sizes];
    }

    vector<int> output(2 * sizes);

    for (int i = 0; i < sizes; i++)
    {
        output[i] = right[i];
        output[i + sizes] = left[i];
    }

    return output;
}

// Function to convert a binary vector to decimal
int BinaryToDecimal(vector<int> vec)
{
    int base = 1, decimal_value = 0;
    for (int i = vec.size() - 1; i >= 0; i--)
    {
        decimal_value += vec[i] * base;
        base = base * 2;
    }

    return decimal_value;
}

// Function implementing the round function
vector<int> function_(vector<int> tmpp, vector<int> key__)
{
    vector<int> left_4bits(4), right_4bits(4);

    for (int i = 0; i < 4; i++)
    {
        left_4bits[i] = tmpp[i];
        right_4bits[i] = tmpp[i + 4];
    }

    vector<int> ep(8);

    // Expand and permute the right 4 bits
    for (int i = 0; i < 8; i++)
    {
        ep[i] = right_4bits[Expanded_Permutation_EP[i] - 1];
    }

    // XOR the expanded and permuted bits with the key
    for (int i = 0; i < 8; i++)
    {
        tmpp[i] = key__[i] ^ ep[i];
    }

    vector<int> left_4bits_1(4), right_4bits_1(4);

    for (int i = 0; i < 4; i++)
    {
        left_4bits_1[i] = tmpp[i];
        right_4bits_1[i] = tmpp[i + 4];
    }

    int row, column, value;

    // using 1 and 4 bit of left_4bits_1 we find row
    vector<int> vec = {left_4bits_1[0], left_4bits_1[3]};
    row = BinaryToDecimal(vec);

    // using 2 and 3 bit of left_4bits_1 we find column
    vec = {left_4bits_1[1], left_4bits_1[2]};
    column = BinaryToDecimal(vec);

    // Find the value at the row and column of S-Box 0
    value = S_Box_0[row][column];
    string str_left = Binary__(value);

    // using 1 and 4 bit of left_4bits_1 we find row
    vec = {right_4bits_1[0], right_4bits_1[3]};
    row = BinaryToDecimal(vec);

    // using 2 and 3 bit of left_4bits_1 we find column
    vec = {right_4bits_1[1], right_4bits_1[2]};
    column = BinaryToDecimal(vec);

    // Find the value at the row and column of S-Box 1
    value = S_Box_1[row][column];
    string str_right = Binary__(value);

    vector<int> r_(4);
    for (int i = 0; i < 2; i++)
    {
        r_[i] = str_left[i] - '0';
        r_[i + 2] = str_right[i] - '0';
    }

    vector<int> r_p4(4);

    // Perform permutation P4 on the obtained 4 bits
    for (int i = 0; i < 4; i++)
    {
        r_p4[i] = r_[PermutationP4[i] - 1];
    }

    // XOR the left 4 bits with the permuted 4 bits
    for (int i = 0; i < 4; i++)
    {
        left_4bits[i] = left_4bits[i] ^ r_p4[i];
    }

    vector<int> output_8bits(8);

    // Combine the left 4 bits and right 4 bits to get the output
    for (int i = 0; i < 4; i++)
    {
        output_8bits[i] = left_4bits[i];
        output_8bits[i + 4] = right_4bits[i];
    }

    return output_8bits;
}

// Function for the decryption of the ciphertext
vector<int> DecryptionOfCipherText(vector<int> CipherTextBinary)
{
    vector<int> tmp(8);

    // Perform initial permutation on the ciphertext
    for (int i = 0; i < 8; i++)
    {
        tmp[i] = CipherTextBinary[Initial_Permutation_IP[i] - 1];
    }

    // Perform the round function with key2
    vector<int> arr1 = function_(tmp, key2_8bits);

    // Swap the left and right 4 bits
    vector<int> after_swap = swap_bits(arr1, arr1.size() / 2);

    // Perform the round function with key1
    vector<int> arr2 = function_(after_swap, key1_8bits);

    vector<int> decrypted(8);

    // Perform the inverse initial permutation
    for (int i = 0; i < 8; i++)
    {
        decrypted[i] = arr2[Inverse_of_Inital_Permuation_IP_inv[i] - 1];
    }

    return decrypted;
}

// Function for the encryption of the plaintext
vector<int> EncryptionOfPlainText(vector<int> PlainTextBinary)
{
    vector<int> tmp(8);

    // Perform initial permutation on the plaintext
    for (int i = 0; i < PlainTextBinary.size(); i++)
    {
        tmp[i] = PlainTextBinary[Initial_Permutation_IP[i] - 1];
    }

    // Perform the round function with key1
    vector<int> arr1 = function_(tmp, key1_8bits);

    // Swap the left and right 4 bits
    vector<int> after_swap = swap_bits(arr1, arr1.size() / 2);

    // Perform the round function with key2
    vector<int> arr2 = function_(after_swap, key2_8bits);

    vector<int> cipherText_8bits(8);

    // Perform the inverse initial permutation
    for (int i = 0; i < 8; i++)
    {
        cipherText_8bits[i] = arr2[Inverse_of_Inital_Permuation_IP_inv[i] - 1];
    }

    return cipherText_8bits;
}

// Function to convert a decimal number to binary
vector<int> DecimalToBinary(int Decimal)
{
    vector<int> binaryNum(8, 0);
    ll i = 0;
    while (Decimal > 0)
    {
        binaryNum[i] = Decimal % 2;
        Decimal = Decimal / 2;
        i++;
    }

    reverse(binaryNum.begin(), binaryNum.end());

    return binaryNum;
}

// Function to perform left circular shift on a binary vector
vector<int> shift(vector<int> binary, int n)
{
    while (n > 0)
    {
        int temp = binary[0];
        for (int i = 0; i < binary.size() - 1; i++)
        {
            binary[i] = binary[i + 1];
        }

        binary[binary.size() - 1] = temp;
        n--;
    }
    return binary;
}

// Function for key generation
void key_geneartion(vector<int> key_10bit)
{
    vector<int> key_(10);

    // Perform initial permutation on the 10-bit key
    for (int i = 0; i < 10; i++)
    {
        key_[i] = key_10bit[PermutationP10[i] - 1];
    }

    vector<int> left_side(5), right_side(5);

    for (int i = 0; i < 5; i++)
    {
        left_side[i] = key_[i];
        right_side[i] = key_[i + 5];
    }

    vector<int> left_shift1 = shift(left_side, 1);
    vector<int> right_shift1 = shift(right_side, 1);

    for (int i = 0; i < 5; i++)
    {
        key_[i] = left_shift1[i];
        key_[i + 5] = right_shift1[i];
    }

    for (int i = 0; i < 8; i++)
    {
        key1_8bits[i] = key_[PermutationP8[i] - 1];
    }

    vector<int> left_shift2 = shift(left_side, 2);
    vector<int> right_shift2 = shift(right_side, 2);

    for (int i = 0; i < 5; i++)
    {
        key_[i] = left_shift2[i];
        key_[i + 5] = right_shift2[i];
    }

    for (int i = 0; i < 8; i++)
    {
        key2_8bits[i] = key_[PermutationP8[i] - 1];
    }

    cout << "Generated 8-Bit Key1 (K1) : ";
    for (auto itr : key1_8bits)
    {
        cout << itr;
    }
    cout << endl;
    cout << "Generated 8-Bit Key2 (K2) : ";
    for (auto itr : key2_8bits)
    {
        cout << itr;
    }
    cout<<endl;

}

vector<int> generateRandomKey(int sizeOfKey)
{
    vector<int> binaryValues = {0, 1}, tmp(sizeOfKey);

    srand(time(NULL));
    for (int i = 0; i < sizeOfKey; i++)
    {
        tmp[i] = binaryValues[rand() % binaryValues.size()];
    }

    return tmp;
}

void solve()
{
    // This Will Generate the Random 10 Bit Key of '1' & '0'
    vector<int> key_10bit = generateRandomKey(10);

    cout << "Generated 10-Bit Key : ";
    for (auto itr : key_10bit)
    {
        cout << itr;
    }
    cout << endl;

    // Will Generate two keys K1 and K2 of 8 Bits for Two Rounds
    key_geneartion(key_10bit);

    // Enter Your Message for Encryption
    cout <<"Enter Message: "<<endl;
    string plaintext;
    getline(cin, plaintext);

    // This Will Encrypt the Message to Cipher Text
    vector<int> CipherText;
    for (int i = 0; i < plaintext.length(); i++)
    {
        vector<int> BinaryOfPlainText = DecimalToBinary(plaintext[i] - 0);
        vector<int> CipherText_8Bits = EncryptionOfPlainText(BinaryOfPlainText);
        int ct = BinaryToDecimal(CipherText_8Bits);
        CipherText.push_back(ct);
    }

    cout << "The Cipher Text Generated For Plain Text Is : ";
    for (auto itr : CipherText)
    {
        cout << char(itr % 128);
    }
    cout << endl;

    // This Will Decrypt the Cipher Text to Message
    string pt_;
    for (int i = 0; i < CipherText.size(); i++)
    {
        vector<int> CipherText_8Bits = DecimalToBinary(CipherText[i]);
        vector<int> Decrypted_8Bits = DecryptionOfCipherText(CipherText_8Bits);
        pt_.push_back(BinaryToDecimal(Decrypted_8Bits));
    }

    cout << "The Decrpted PlainText Is : ";
    cout << pt_ << endl;
}

int main()
{
    FAST
    // #ifndef ONLINE_JUDGE
    //         freopen("input", "r", stdin);
    //     freopen("output", "w", stdout);
    // #endif

    solve();

    return 0;
}
