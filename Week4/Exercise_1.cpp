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

long long Rand(long long L, long long R) {
    assert(L <= R);
    return L + rd() % (R - L + 1);
}
    

void swap(int & a, int & b) {
    int tmp = a;
    a = b;
    b = tmp;
}

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

void selection_sort(int n, int* a) {
    for (int i = 0;i < n;i++) {
        int val = a[i];
        int pos = i;
        for (int j = i + 1;j < n;j++) {
            if (minimize(val, a[j])) pos = j;
        }
        swap(a[i], a[pos]);
    }
}

void interchange_Sort(int n,int* a) {
    for (int i = 0;i < n;i++) {
        for (int j = i + 1;j < n;j++) {
            if (a[i] > a[j]) swap(a[i], a[j]);
        }
    }
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

int main() {
    int n, *a , *b;
    
    n = Rand(1e4, 5e4);

    a = new int[n];
    b = new int[n];

    for (int i = 0;i < n;i++) {
        a[i] = Rand(1, 1e9);
    }

    double ins_time, sel_time, inter_time;

    ResetArr(n, a, b);
    output << "Insertion Sort Time: ";
    ins_time =Counting_Time(insertion_sort, n, b);
    output << fixed << setprecision(3) << ins_time << " seconds\n";

    ResetArr(n, a, b);
    output << "Selection Sort Time: ";
    sel_time = Counting_Time(selection_sort, n, b);
    output << fixed << setprecision(3) << sel_time << " seconds\n";
 
    ResetArr(n, a, b);
    output << "Interation Sort Time: ";
    inter_time = Counting_Time(interchange_Sort, n, b);
    output << fixed << setprecision(3) << inter_time << " seconds\n";

    output << "The fastest algorithm: ";
    if (ins_time < sel_time && ins_time < inter_time) {
        output << "Insertion Sort\n";
    } else if (sel_time < ins_time && sel_time < inter_time) {
        output << "Selection Sort\n";
    } else {
        output << "Interchange Sort\n";
    }

    output << "The slowest algorithm: ";
    if (ins_time > sel_time && ins_time > inter_time) {
        output << "Insertion Sort\n";
    } else if (sel_time > ins_time && sel_time > inter_time) {
        output << "Selection Sort\n";
    } else {
        output << "Interchange Sort\n";
    }


    return 0;
}