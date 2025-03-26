#include <iostream>
#include <fstream>

using namespace std;

void nhap(char *InputFileName, char *OutputFileName, int &n, int *&a)
{
    ifstream input(InputFileName);
    input >> n;
    a = new int[n + 1];
    for (int i = 0; i < n; i++)
    {
        input >> a[i];
    }
}

// Algorithms 1

int LinerSearch(int n, int *a, int val)
{
    int i = 0;
    while (i < n)
    {
        if (a[i] == val)
            return i;
        i++;
    }
    return -1;
}

// End Algorithms 1

// Algorithms 2

int LinerSearch2(int n, int *a, int val)
{
    a[n] = val;
    int i = 0;
    while (a[i] != val)
        i++;
    if (i == n)
        return -1;
    return i;
}
// End Algorithms 2

// Algorithms 3
int BinarySearch(int n, int *a, int val)
{
    int l = 0;
    int r = n - 1;
    int ans = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (val == a[mid])
        {
            ans = mid;
            r = mid - 1;
        }
        else if (val < a[mid])
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans;
}
// End Algorithms 3

// Algorithms 4
int Interpolation_Search(int n, int *a, int val)
{
    int l = 0;
    int r = n - 1;
    int ans = -1;
    while (l <= r && val >= a[l] && val <= a[r])
    {
        if (l == r) {
            if (a[l] == val) return l;
            return -1;
        }
        int pivot = l + ((val - a[l]) * (r - l)) / (a[r] - a[l]);
        if (val == a[pivot])
        {
            ans = pivot;
            r = pivot - 1;
        }
        else if (val < a[pivot])
        {
            r = pivot - 1;
        }
        else
        {
            l = pivot + 1;
        }
    }
    return ans;
}
// End Algorithms 4

void Solve(char *OutputFileName, char *mode, int n, int *a, int val)
{
    ofstream output(OutputFileName);
    if (mode[0] == '1')
    {
        // output << "Mode1" << endl;
        output << LinerSearch(n, a, val);
    }
    else if (mode[0] == '2')
    {
        // output << "Mode2" << endl;
        output << LinerSearch2(n, a, val);
    }
    else if (mode[0] == '3')
    {
        // output << "Mode3" << endl;
        output << BinarySearch(n, a, val);
    }
    else
    {
        // output << "Mode4" << endl;
        output << Interpolation_Search(n, a, val);
    }
}

int main(int argc, char *argv[])
{

    // ofstream output("TASK.out");

    // for (int i = 0; i < argc; i++)
    // {
    //     output << argv[i] << endl;
    // }

    int n;
    int *a;

    nhap(argv[3], argv[4], n, a);

    int val = stoi(argv[2]);

    Solve(argv[4], argv[1], n, a, val);

    delete a;

    return 0;
}