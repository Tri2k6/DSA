#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int> &arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        int j = i - 1;
        bool isEven = (arr[i] % 2 == 0);
        int key = arr[i];
        int pre = i;
        for (; j >= 0; j--)
        {
            if ((arr[j] % 2 == 0) != isEven)
                continue;
            if ((isEven && (arr[j] < key)) || (!isEven && (arr[j] > key)))
            {
                break;
            }
            arr[pre] = arr[j];
            pre = j;
        }
        arr[pre] = key;
    }
}

int main()
{
    vector<int> arr;
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        arr.push_back(x);
    }
    insertionSort(arr);
    for (int i : arr)
    {
        cout << i << " ";
    }
    return 0;
}