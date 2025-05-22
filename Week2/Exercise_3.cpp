#include <iostream>
using namespace std;

#define input cin
#define output cout
#define ll long long

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int a,b;
    input >> a >> b;
    output << gcd(a,b);
    return 0;
}