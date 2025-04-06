#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define inputFile "exam.txt"
#define vi vector<int>
#define pii pair<int,int>

struct Person {
    double kt1, kt2;
    string name;
    vi NguyenVong;
    Person() {}
    Person(double ktt1, double ktt2, string n, vi NV) {
        kt1 = ktt1;
        kt2 = ktt2;
        name = n;
        NguyenVong.clear();
        for (int i = 0;i < NV.size();i++) {
            NguyenVong.push_back(NV[i]);
        }
    }
    void Copy(Person a) {
        kt1 = a.kt1;
        kt2 = a.kt2;
        name = a.name;
        NguyenVong.clear();
        for (int i = 0;i < a.NguyenVong.size();i++) {
            NguyenVong.push_back(a.NguyenVong[i]);
        }
    }
};

bool ReadInput(int & n,int & m,vi & ChiTieu, vector< Person> & a);


int main() {

    return 0;
}

bool ReadInput(int & n,int & m,vi & ChiTieu, vector<Person> & a) {
    ifstream input(inputFile);
    if (!input.is_open()) {
        return false;
    }

    input >> m;
    for (int i = 0;i < m;i++) {
        int x;
        input >> x;
        ChiTieu.push_back(x);
    }

    string str;
    while (getline(input,str)) {
        stringstream ss(str);
        string name;
        double kt1, kt2;
        vi NguyenVong;
        getline(ss, name, ',');
        input >> kt1 >> kt2;
        for (int i = 0;i < m;i++) {
            int x;
            input >> x;
            NguyenVong.push_back(x);
        }
        cout << kt1 << ' ' << kt2 << ' ' << name << endl;
        a.push_back(Person(kt1, kt2, name, NguyenVong));
    }

    n = a.size();

    return true;
}
