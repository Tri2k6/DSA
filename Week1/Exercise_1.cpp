#include <iostream>
#include <limits.h>

using namespace std;

#define input cin
#define output cout
#define endl '\n'

void inputArray ( int * & arr , int n ) ;
void printArray ( int * arr , int n ) ;
int findMax ( int * arr , int n ) ;
int sumArray ( int * arr , int n ) ;
void concatArrays ( int * a , int na , int * b , int nb , int * & res , int & nres ) ;
void findLongestAscendingSubarray ( int * arr , int n , int * & res , int & nres ) ;

int main() {

    int na, nb, nc;
    int *a, *b, *c;


    output << "Enter the number of elements in array a: ";
    input >> na;
    output << "Enter the array a: ";
    inputArray(a, na);

    output << "Enter the number of elements in array b: ";
    input >> nb;
    output << "Enter the array b: ";
    inputArray(b, nb);

    concatArrays(a, na, b, nb, c, nc);

    // printArray(a, na);
    // printArray(b, nb);
    // printArray(c, nc);

    output << findMax(c, nc) << endl;
    output << sumArray(c, nc) << endl;

    int *d, nd;
    
    findLongestAscendingSubarray(c, nc, d, nd);

    for (int i = 0;i < nd;i++) {
        output << d[i] << ' ';
    }

    delete a,b,c,d;

    return 0;
}

void inputArray(int *& arr, int n) {
    arr = new int[n];
    for (int i = 0;i < n;i++) {
        input >> arr[i];
    }
}

void printArray(int * arr, int n) {
    for (int i = 0;i < n;i++) {
        output << arr[i] << ' ';
    }
    output << endl;
}

int findMax(int * arr, int n) {
    int ans = arr[0];
    for (int i = 1;i < n;i++) {
        if (ans < arr[i]) ans = arr[i];
    }
    return ans;
}

int sumArray(int * arr,int n) {
    int ans = 0;
    for (int i = 0;i < n;i++) {
        ans += arr[i];
    }
    return ans;
}

void concatArrays ( int * a , int na , int * b , int nb , int * & res , int & nres ) {
    nres = na + nb;
    res = new int[nres];
    for (int i = 0;i < na;i++) {
        res[i] = a[i];
    }
    for (int i = 0;i < nb;i++) {
        res[i + na] = b[i];
    }
}

void findLongestAscendingSubarray ( int * arr , int n , int * & res , int & nres ) {
    int Max = 1, curLen = 1, Idx = 0;
    for (int i = 1;i < n;i++) {
        if (arr[i] > arr[i - 1]) {
            curLen++;
        } else {
            if (Max < curLen) {
                Max = curLen;
                Idx = i - Max; 
            }

            curLen = 1;
        }
    }

    if (Max < curLen) {
        Max = curLen;
        Idx = n - Max;
    }

    res = new int [Max];
    for (int i = 0;i < Max;i++) {
        res[i] = arr[i + Idx];
    }

    nres = Max;
}
