#include <iostream>
#include <vector>
using namespace std;

#define input cin
#define output cout
#define vi vector<int>

void swap(int & a, int & b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void InsertOdd(int n,int* a, int i) {
    int val = a[i];
    int j = i - 1;
    int pre = i;

    for (;j >= 0;j--) {
        if (!(a[j] & 1)) continue;
        if (a[j] > val) break;
        a[pre] = a[j];
        pre = j;
    }
    a[pre] = val; 
}

void InsertEven(int n,int*a, int i) {
    int val = a[i];
    int j = i - 1;
    int pre = i;

    for (;j >= 0;j--) {
        if (a[j] & 1) continue;
        if (a[j] < val) break;
        a[pre] = a[j];
        pre = j;
    }
    a[pre] = val; 
}


void Solve(int n, int* a) {
    for (int i = 1;i < n;i++) {
        if (a[i] & 1) InsertOdd(n, a, i);
        else InsertEven(n, a, i);
    }
}

int main() {
    int n, *a;

    input >> n;

    a = new int[n];

    for (int i = 0;i < n;i++) {
        input >> a[i];
    }

    Solve(n, a);

    for (int i = 0;i < n;i++) {
        output << a[i] << ' ';
    }

    return 0;
}