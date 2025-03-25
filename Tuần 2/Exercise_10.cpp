#include <iostream>
#include <string>
using namespace std;

#define input cin
#define output cout
#define ll long long

const int cs = 10 + 1;

int n;
int isCol[cs];
int isMainDiagonal[2 * cs + 2];
int isSubDiagonal[2 * cs + 2];
int x[cs];

void PrintResult() {    
    output << "[";
    for (int i = 1;i < n;i++) {
        output << x[i] << ", ";
    }
    output << x[n] << ']' << endl;
}

void BackTrack(int pos) {
    for (int i = 1;i <= n;i++) {
        if (!isCol[i] && !isMainDiagonal[pos + i] && !isSubDiagonal[pos - i + n + 1]) {
            isCol[i] = isMainDiagonal[pos + i] = isSubDiagonal[pos - i + n + 1] = 1;
            x[pos] = i;
            if (pos == n) PrintResult();
            else BackTrack(pos + 1);
            isCol[i] = isMainDiagonal[pos + i] = isSubDiagonal[pos - i + n + 1] = 0;
        }
    }
}

int main() {

    input >> n;

    // memset data
    for (int i = 1;i <= n;i++) {
        isCol[i] = 0;
    }

    for (int i = 1; i <= 2 * n + 1;i++) {
        isMainDiagonal[i] = isSubDiagonal[i] = 0;
    }

    BackTrack(1);

    return 0;
}