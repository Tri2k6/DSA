#include <iostream>
#include<fstream>
#include <string>
using namespace std;

#define input cin
// #define output cout
#define pii pair<string,string>
#define Dictonary_FileName "English-Vietnamese Dictionary.txt"


const int n = 124585;

bool Read_Dictionary(pii *&a);
pii Divide_Word(string str);
void Chuan_Hoa_string(string & str);
void MainSolve(int argc, char * argv[], pii * a) ;
int Binary_Search(pii *a, string val);

int main(int argc, char * argv[]) {

    pii * a;

    if (Read_Dictionary(a)) {
        MainSolve(argc, argv, a);
    } else {
        cerr << "Cann't access to the dictionary";
        return 0;
    }

    delete a;

    return 0;
}

void Chuan_Hoa_string(string & str) {
    while (isspace(str.back())) {
        str.pop_back();
    }
    while (isspace(str[0])) {
        str.erase(0,1);
    }
}

pii Divide_Word(string str) {
    bool isOk = false;

    string Word = "";
    string Meaning = "";

    for (int i = 0;i < str.length();i++) {
        if (str[i] == ':') {
            isOk = true;
            continue;
        }
        
        if (!isOk) {
            Word += str[i]; 
        } else {
            Meaning += str[i];
        }
    }
    //Chuan_Hoa_string(Word);
    //Chuan_Hoa_string(Meaning);
    return make_pair(Word, Meaning);
}

bool Read_Dictionary(pii *& a) {
    if (fopen(Dictonary_FileName, "r")) {
        freopen(Dictonary_FileName, "r", stdin);
    } else return false;

    a = new pii[n];
    
    for (int i = 0;i < n;i++) {
        string str;
        getline(input,str);
        a[i] = Divide_Word(str);
    }

    // for (int i = 0;i < n;i++) {
    //     output << a[i].first << endl << a[i].second << endl;
    // }
    return true;

}

int Binary_Search(pii * a, string val) {
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (val == a[mid].first) {
            return mid;
        } else if (val < a[mid].first) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

void MainSolve(int argc, char * argv[], pii * a) {

    ofstream output(argv[argc - 1]);

    for (int i = 1;i < argc - 1;i++) {
        int idx = Binary_Search(a, argv[i]);
        output << a[idx].first << ":" << a[idx].second << endl; 
    }
} 