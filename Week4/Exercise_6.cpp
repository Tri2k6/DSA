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

#define ll long long
#define input cin
#define output cout
#define vi vector<int>
#define bit(u,i) (u >> i) & 1

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

void printArr(int n,int * a);
long long Rand(long long L, long long R);
void swap(int & a, int & b);
void ResetArr(int n, int * a, int *b);
double Counting_Time(void (*operation)(int, int*),int n, int * a);
void Merge(int * a, int l,int mid, int r);
void Merge_Sort(int * a, int l,int r);
void MergeSort(int n,int * a);
void CountingSort(int n, int * a);
void RadixSort(int n,int * a);
void FlashSort(int n,int * a);
bool isTangDan(int n,int * a);

int main() {

    int n, *a , *b;
    
    n = Rand(5e4, 2e6);

    a = new int[n];
    b = new int[n];

    for (int i = 0;i < n;i++) {
        a[i] = Rand(0, 1e6);
    }

    double Merge_Time, Count_Time, Radix_Time, Flash_Time;

    ResetArr(n, a, b);
    //printArr(n, b);
    output << "Merge Sort Time: ";
    Merge_Time = Counting_Time(MergeSort, n, b);
    output << fixed << setprecision(3) << Merge_Time << " seconds\n";
    //printArr(n, b);
    //output << isTangDan(n, b) << endl;

    ResetArr(n, a, b);
    //printArr(n, b);
    output << "Counting Sort Time: ";
    Count_Time = Counting_Time(CountingSort, n, b);
    output << fixed << setprecision(3) << Count_Time << " seconds\n";
    //printArr(n,b);
    //output << isTangDan(n, b) << endl;

    ResetArr(n, a, b);
    //printArr(n,b);
    output << "Radix Sort Time: ";
    Radix_Time = Counting_Time(RadixSort, n, b);
    output << fixed << setprecision(3) << Radix_Time << " seconds\n";
    //printArr(n,b);
    //output << isTangDan(n, b) << endl;

    ResetArr(n, a, b);
    // printArr(n,b);
    output << "Flash Sort Time: ";
    Flash_Time = Counting_Time(FlashSort, n, b);
    output << fixed << setprecision(3) << Flash_Time << " seconds\n";
    // printArr(n,b);
    // output << isTangDan(n, b) << endl;

    output << "The fastest algorithm: ";
    if (Merge_Time <= Count_Time && Merge_Time <= Radix_Time && Merge_Time <= Flash_Time) {
        output << "Merge_Sort\n";
    } else if (Merge_Time >= Count_Time && Count_Time <= Radix_Time && Count_Time <= Flash_Time) {
        output << "Counting_Sort\n";
    } else if (Radix_Time <= Count_Time && Merge_Time >= Radix_Time && Radix_Time <= Flash_Time) {
        output << "Radix Sort\n";
    } else output << "Flash Sort\n";

    output << "The lowest algorithm: ";
    if (Merge_Time >= Count_Time && Merge_Time >= Radix_Time && Merge_Time >= Flash_Time) {
        output << "Merge_Sort\n";
    } else if (Merge_Time <= Count_Time && Count_Time >= Radix_Time && Count_Time >= Flash_Time) {
        output << "Counting_Sort\n";
    } else if (Radix_Time >= Count_Time && Merge_Time <= Radix_Time && Radix_Time >= Flash_Time) {
        output << "Radix Sort\n";
    } else output << "Flash Sort\n";
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

void Merge(int * a,int l,int mid,int r) {
    vi x(a + l, a + mid + 1);
    vi y(a + mid + 1, a + r + 1);
    int i = 0, j = 0;
    while (i < x.size() && j < y.size()) {
        if (x[i] <= y[j]) {
            a[l] = x[i];
            ++l; ++i;
        } else {
            a[l] = y[j];
            ++l; ++j;
        }
    }

    while (i < x.size()) {
        a[l] = x[i];
        l++;i++;
    }

    while (j < y.size()) {
        a[l] = y[j];
        l++;j++;
    }
}

void Merge_Sort(int * a, int l,int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    Merge_Sort(a, l,mid);
    Merge_Sort(a, mid + 1,r);
    Merge(a, l, mid, r);
}

void MergeSort(int n,int * a) {
    Merge_Sort(a, 0,n - 1);
}

void CountingSort(int n,int * a) {
    int Max = INT_MIN, Min = INT_MAX;
    
    // Find Max and Min
    for (int i = 0;i < n;i++) {
        maximize(Max, a[i]);
        minimize(Min, a[i]);
    }

    int *F = new int[Max - Min + 1];
    int *b = new int[n];

    for (int i = 0;i <= Max - Min;i++) {
        F[i] = 0;
    }

    for (int i = 0;i < n;i++) {
        F[a[i] - Min]++;
    }
    
    for (int i = 1;i <= Max - Min;i++) {
        F[i] += F[i - 1];
    }

    for (int i = n - 1;i >= 0;i--) {
        b[F[a[i] - Min] - 1] = a[i];
        F[a[i] - Min]--;
    }

    for (int i = 0;i < n;i++) {
        a[i] = b[i];
    }

    delete[] F;
    delete[] b;
}

void RadixSort(int n,int * a) {
    vi tmp[2];
    for (int j = 0;j <= 31;j++) {
        tmp[0].clear();
        tmp[1].clear();
        for (int i = 0;i < n;i++) {
            tmp[bit(a[i], j)].push_back(a[i]);
        }   
        int pos = 0;
        for (int k = 0;k <= 1;k++) {
            for (auto x : tmp[k]) {
                a[pos++] = x;
            }
        }
    }
}

void InsertionSort(int * a, int l, int r) {
    for (int i = l + 1;i <= r;i++) {
        int val = a[i];
        int pos = i - 1;
        while (pos >= l && a[pos] > val) {
            a[pos + 1] = a[pos];
            pos--;
        }
        a[pos + 1] = val;
    }
}

void FlashSort(int n,int * a) {
    int Max = a[0], Min = a[0];
    for (int i = 0;i < n;i++) {
        minimize(Min, a[i]);
        maximize(Max, a[i]);
    }

    if (Max == Min) return;

    int m = int(0.43 * n);
    int * L = new int[m];
    for (int i = 0;i < m;i++) {
        L[i] = 0;
    }

    for (int i = 0;i < n;i++) {
        int k = 1ll * (m - 1) * (a[i] - Min) / (Max - Min);
        ++L[k];
    }

    for (int i = 1;i < m;i++) {
        L[i] += L[i - 1];
    }

    int move = 0, i = 0;
    while (move < n - 1) {
        int k = 1ll * (m - 1) * (a[i] - Min) / (Max - Min);

        while (i >= L[k]) {
            i++;
            if (i >= n) break;
            k = 1ll * (m - 1) * (a[i] - Min) / (Max - Min);
        }

        if (i >= n) break;

        int Flash = a[i];

        while (i != L[k]) {
            k = 1ll * (m - 1) * (Flash - Min) / (Max - Min);
            --L[k];
            swap(a[L[k]], Flash);
            move++; 
        }
    }

    for (int k = 0;k < m;k++) {
        int start = (k == 0) ? 0 : L[k - 1];
        int end = L[k] - 1;
        if (start < end) InsertionSort(a, start, end);
    }

    // InsertionSort(a, 0, n - 1);

    delete[] L;
}

void printArr(int n,int * a) {
    for (int i = 0;i < n;i++) {
        output << a[i] << ' ';
    }
    output << endl;
}

bool isTangDan(int n,int * a) {
    for (int i = 1;i < n;i++) {
        if (a[i - 1] > a[i]) return output << a[i - 1] << ' ' << a[i], false;
    }
    return true;
}