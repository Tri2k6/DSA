#include <iostream>
using namespace std;

#define input cin
#define output cout

void insertion_sort(int n,int* a) {
    for (int i = 1;i < n;i++) {
        int val = a[i];
        int pos = i - 1;
        while (pos >= 0 && a[pos] > val) {
            a[pos + 1] = a[pos];
            pos--;
        }
        a[pos + 1] = val;
    }
}

int main() {
    int n,m, **a, *b;

    input >> n >> m;

    a = new int *[n];
    b = new int [n * m];

    for (int i = 0;i < n;i++) {
        a[i] = new int [m];
        for (int j = 0;j < m;j++) {
            input >> a[i][j];
            b[i * m + j] = a[i][j];
        }
    }

    insertion_sort(n * m, b);
    
    int u = 0, v = n - 1, x = 0, y = m - 1;
    int idx = 0;

    while (u <= v && x <= y) {
        for (int i = x;i <= y;i++) {
            a[u][i] = b[idx++];
        }
        u++;

        for (int i = u;i <= v;i++) {
            a[i][y] = b[idx++];
        }
        y--;

        if (u <= v) {
            for (int i = y;i >= x;i--) {
                a[v][i] = b[idx++];
            }
            v--;
        }

        if (x <= y) {
            for (int i = v;i >= u;i--) {
                a[i][x] = b[idx++];
            }
            x++;
        }
    }

    for (int i = 0;i < n;i++) {
        for (int j = 0;j < m;j++) {
            output << a[i][j] << ' ';
        }
        output << endl;
    }

    return 0;
}