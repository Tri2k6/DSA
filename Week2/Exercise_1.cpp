#include <iostream>
using namespace std;

#define input cin
#define output cout
#define ll long long

ll Factorial(int n) {
    if (n == 0) return 1;
    return 1ll * n * Factorial(n - 1);
}

int main() {
    int n;
    input >> n;
    output << Factorial(n);
}