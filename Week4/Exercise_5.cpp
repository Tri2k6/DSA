#include <iostream>
#include <vector>
#include <limits.h>
#include <random>
#include <cassert>
#include <chrono>
#include <time.h>
#include <iomanip>
using namespace std;
using namespace std::chrono;

#define input cin
#define output cout

template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        if (x > y) {
            x = y;
            return true;
        } else return false;
    }

template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y) {
            x = y;
            return true;
        } else return false;
    }

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

long long Rand(long long L, long long R);
void swap(int & a, int & b);
void ResetArr(int n, int * a, int *b);
double Counting_Time(void (*operation)(int, int*),int n, int * a);
void Heapify(int n,int * a,int idx);
void HeapSort(int n,int * a);
void Partition(int * a, int l,int r);
void Quick_Sort(int * a, int l, int r);
void QuickSort(int n, int * a);

int main() {

    int n, *a , *b;
    
    n = Rand(1e5, 1e6);

    a = new int[n];
    b = new int[n];

    for (int i = 0;i < n;i++) {
        a[i] = Rand(1, 1e9);
    
    }

    double Heap, Quick;
    ResetArr(n, a, b);
    // for (int i = 0;i < n;i++) {
    //     output << b[i] << ' ';
    // }
    // output << endl;
    output << "Heap Sort: ";
    Heap = Counting_Time(HeapSort, n, b);
    output << fixed << setprecision(3) << Heap << " seconds\n";

    // for (int i = 0;i < n;i++) {
    //     output << b[i] << ' ';
    // }
    // output << endl;

    ResetArr(n,a,b);

    // for (int i = 0;i < n;i++) {
    //     output << b[i] << ' ';
    // }
    // output << endl;

    output << "Quick Sort: ";
    Quick = Counting_Time(QuickSort, n, b);
    output << fixed << setprecision(3) << Quick << " seconds\n";

    // for (int i = 0;i < n;i++) {
    //     output << b[i] << ' ';
    // }

    if (Quick <= Heap) {
        output << "The fastest algorithm: Quick Sort\nThe slowest algorithm: Heap Sort";
    } else {
        output << "The fastest algorithm: Heap Sort\nThe slowest algorithm: Quick Sort";
    }

    return 0;
}


long long Rand(long long L, long long R) {
    assert(L <= R);
    return L + rd() % (R - L + 1);
}
    

void swap(int & a, int & b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void ResetArr(int n, int * a, int *b) {
    for (int i = 0;i < n;i++) {
        b[i] = a[i];
    }
}

double Counting_Time(void (*operation)(int, int*),int n, int * a) {
    auto start = high_resolution_clock::now();

    operation(n,a);

    auto stop = high_resolution_clock::now();
 
    auto duration = duration_cast<microseconds>(stop - start);


    return 1.00 * duration.count() / 1000000.0;
}

void Heapify(int n,int * a,int idx) {
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;
    int Max = idx;
    if (l < n && a[l] > a[Max]) Max = l;
    if (r < n && a[r] > a[Max]) Max = r;
    if (Max != idx) {
        swap(a[idx], a[Max]);
        Heapify(n, a, Max);
    }
}

void HeapSort(int n,int * a) {
    for (int i = n / 2 - 1;i >= 0;i--) {
        Heapify(n, a, i);
    }
    for (int i = n - 1;i >= 0;i--) {
        swap(a[i], a[0]);
        Heapify(i, a, 0);
    }
}

int partition(int * a, int l,int r) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l;j < r;j++) {
        if (a[j] < pivot) {
            ++i;
            swap(a[i], a[j]);
        }
    }
    // dua chot ve giua
    ++i;
    swap(a[i], a[r]);
    return i;
}

void Quick_Sort(int * a, int l, int r) {
    if (l >= r) return;
    int pivot = partition(a, l, r);
    Quick_Sort(a, l, pivot - 1);
    Quick_Sort(a, pivot + 1, r);
}

void QuickSort(int n, int * a) {
    Quick_Sort(a, 0, n - 1);
}