#include <iostream>
#include <string>
using namespace std;

#define input cin
#define output cout
#define ll long long

void Swap(char& a, char& b) {
    char tmp = a;
    a = b;
    b = tmp;
}

void ReverseStr(string & str,int l, int r) {
    if (l >= r) return;
    Swap(str[l], str[r]);
    ReverseStr(str, l + 1, r - 1);
}

int main() {

    string str;
    getline(input,str);

    ReverseStr(str, 0, str.length() - 1);
    output << str;

    return 0;
}