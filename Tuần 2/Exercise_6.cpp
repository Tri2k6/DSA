#include <iostream>
#include <string>
using namespace std;

#define input cin
#define output cout
#define ll long long

bool isPalindrome(string str, int l,int r) {
    if (l >= r) return true;
    if (str[l] != str[r]) return false;
    return isPalindrome(str, l + 1, r - 1);
}

int main() {

    string str;
    getline(input,str);

    if (isPalindrome(str, 0 , str.length() - 1)) {
        output << "Yes";
    } else {
        output << "No";
    }

    return 0;
}