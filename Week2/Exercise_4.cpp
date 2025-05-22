#include <iostream>
using namespace std;

#define input cin
#define output cout

bool isIncreasing(int * a, int n, int pos) {
    if (pos >= n - 1) return true;
    if (a[pos] >= a[pos + 1]) return false;
    return isIncreasing(a, n, pos + 1);
}

int main() {
    int n, *a;
    input >> n;
    a = new int[n];

    for (int i = 0;i < n;i++) {
        input >> a[i];
    }

    if (isIncreasing(a, n, 0)) {
        output << "Yes";
    } else {
        output << "No";
    }

    return 0;
}