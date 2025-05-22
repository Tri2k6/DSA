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

void swap(int & a, int & b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void insertion_sort(int n,int* & a) {
    for (int i = 1;i < n;i++) {
        int val = a[i];
        int pos = i - 1;
        while (pos >= 1 && a[pos] > val) {
            a[pos + 1] = a[pos];
            pos--;
        }
        a[pos + 1] = val;
    }
}

void selection_sort(int n, int* & a) {
    for (int i = 0;i < n;i++) {
        int val = a[i];
        int pos = i;
        for (int j = i + 1;j < n;j++) {
            if (minimize(val, a[j])) pos = j;
        }
        swap(a[i], a[pos]);
    }
}

void interchange_Sort(int n,int*& a) {
    for (int i = 0;i < n;i++) {
        for (int j = i + 1;j < n;j++) {
            if (a[i] > a[j]) swap(a[i], a[j]);
        }
    }
}