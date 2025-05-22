#include <iostream>
#include <string>
using namespace std;

#define input cin
#define output cout
#define ll long long

const int cs = 10 + 1;

int n;
int a[cs];

void PrintArray() { 
    for (int i = 1;i <= n;i++) {
        output << a[i];
    }
    output << endl;
}   

void BackTrack(int pos) {
    for (int i = 0;i <= 1;i++) {
        a[pos] = i;
        if (pos == n) PrintArray();
        else BackTrack(pos + 1);
    }
}

int main() {

    input >> n;

    BackTrack(1);

    return 0;
}