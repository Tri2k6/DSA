#include <iostream>
using namespace std;

#define input cin
#define output cout
#define ll long long

int sumDigit(int n) {
    if (n == 0) return 0;
    return n % 10 + sumDigit(n / 10);
}

int main() {
    int n;
    input >> n;
    output << sumDigit(n);

    return 0;
}