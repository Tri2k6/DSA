#include <iostream>
#include <string>
using namespace std;

#define input cin
#define output cout
#define ll long long

const int cs = 10 + 1;

int n;
int a[cs];
int visited[cs];
int x[cs];

void PrintArray() {
    for (int i = 1;i <= n;i++) {
        output << x[i] << ' ';
    }
    output << endl;
}

void BackTrack(int pos) {
    for (int i = 1;i <= n;i++) {
        if (!visited[i]) {
            x[pos] = a[i];
            visited[i] = 1;
            if (pos == n) PrintArray();
            else BackTrack(pos + 1);

            visited[i] = 0;
        } 

    }
}

int main() {

    input >> n;
    for (int i = 1;i <= n;i++) {
        input >> a[i];
        visited[i] = 0;
    }

    BackTrack(1);

    return 0;
}