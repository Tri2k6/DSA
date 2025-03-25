#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define input cin
#define output cout

void nhap(string & str) {
    getline(cin, str, '\n');
}

void Normalize(string& str) {
    for (int i = 0;i < str.length();i++) {
        if (isspace(str[i])) str[i] = ' ';
    }

    stringstream ss(str);
    string tmp;

    string ans = "";

    while (ss >> tmp) {
        if (tmp.size() == 1 && ispunct(tmp[0])) ans += tmp;
        else ans = ans + ' ' + tmp;
    }
    str = ans;
    while (str[0] == ' ') str.erase(0,1);
}

int Word_Counting(string str) {
    stringstream ss(str);
    string tmp;

    int cnt = 0;

    while (ss >> tmp) {
        cnt++;
    }

    return cnt;
}

bool isAlpha(char c) {
    bool ok1 = 'a' <= c && c <= 'z';
    bool ok2 = 'A' <= c && c <= 'Z';
    return ok1 || ok2;
}

string FindLongest(string str) {
    string ans = "";
    string tmp = "";
    for (int i = 0;i < str.length();i++) {
        if (isAlpha(str[i])) {
            tmp += str[i];
            if (tmp.size() > ans.size()) {
                ans = tmp;
            }
        } else tmp = "";
    }
    return ans;
}

int main() {
    string str;
    nhap(str);

    output << "Normalized paragraph:"  << endl;
    Normalize(str);
    output << str << endl;
    output << "Word count: " << Word_Counting(str) << endl;
    output << "Longest word: " << FindLongest(str) << endl;
}