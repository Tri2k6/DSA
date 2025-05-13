#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <limits.h>
#include <random>
#include <cassert>
#include <chrono>
#include <time.h>
#include <iomanip>
using namespace std;

#define inputFile "exam.txt"
#define vi vector<int>
#define pii pair<int,int>
#define output cout

const int INF = 1e9 + 7;

struct Person {
    string name;
    double kt1, kt2;
    vi NguyenVong;
    Person() {}
    Person(string n, double k1, double k2, vi nv) {
        name = n;
        kt1 = k1;
        kt2 = k2;
        NguyenVong.clear();
        for (auto x: nv) {
            NguyenVong.push_back(x);
        }
    }
    void Copy(Person a) {
        name = a.name;
        kt1 = a.kt1;
        kt2 = a.kt2;
        NguyenVong.clear();
        for (auto x: a.NguyenVong) {
            NguyenVong.push_back(x);
        }
    }
    friend void swapPerson(Person & a, Person & b) {
        Person tmp;
        tmp.Copy(a);
        a.Copy(b);
        b.Copy(tmp);
    }
    double GPA() {
        return 1.0 * (kt1 + kt2) / 2;
    }
    friend bool operator > (Person a, Person b) {
        if (a.GPA() != b.GPA()) return a.GPA() > b.GPA();
        if (a.kt1 != b.kt1) return a.kt1 > b.kt1;
        return a.kt2 > b.kt2;
    }
    friend bool operator < (Person a, Person b) {
        if (a.GPA() != b.GPA()) return a.GPA() < b.GPA();
        if (a.kt1 != b.kt1) return a.kt1 < b.kt1;
        return a.kt2 < b.kt2;
    }
};

// Read input information in exam.txt
bool Read_Input_Value(int & m, vector<pii> & Option, vector<Person> & Candidates,vector<vector<Person>> & Listed_Candidates);
// Sort danh sach Options
void Options_Sort(vector<pii>& Options);
// Tim vi tri cua option co ma so xxx
int FindOptions(int m, vector<pii> & Options, int val);
// Sort candidates 
void Candidates_Sort(vector<Person>& Candidates);
// Process cho 1 nguoi 
int Process_1Person(int m, Person a, vector<pii> & Options, vector<vector<Person>> & Listed_Candidates);
// Solve Candidates 
void Solve_List_Candidates(int m, vector<pii> & Options, vector<Person> & Candidates,vector<vector<Person>> & Listed_Candidates);

int main() {    
    int m, n;
    vector<pii> Options;
    vector<Person> Candidates;
    vector<vector<Person>> Listed_Candidates;

    if (!Read_Input_Value(m, Options, Candidates,Listed_Candidates)) return cerr << "Can not open " << inputFile, 0; 

    Options_Sort(Options);
    
    // for (int i = 0;i < Options.size();i++) {
    //     output << Options[i].first << ' ' << Options[i].second << endl;
    // }
    // output << endl;

    Candidates_Sort(Candidates);

    Solve_List_Candidates(m, Options, Candidates, Listed_Candidates);

    for (int i = 0;i < m;i++) {
        output << "Successful candidates for option " << Options[i].first << endl;
        int pos = 1;
        for (auto & x : Listed_Candidates[i]) {
            x.name.erase(0,1);
            x.name.pop_back();
            output << pos << ". " << x.name << ' ' << x.GPA() << endl;
            pos++;
        }
    }

    output << "Unsuccessful candidates" << endl;
    int pos = 1;
    for (auto & x : Listed_Candidates[m]) {
        x.name.erase(0,1);
        x.name.pop_back();
        output << pos << ". " << x.name << ' ' << x.GPA() << endl;
        pos++;
    }
    return 0;
}

bool Read_Input_Value(int & m, vector<pii> & Option, vector<Person> & Candidates, vector<vector<Person>> & Listed_Candidates) {
    ifstream input(inputFile);
    if (!input.is_open()) return false;

    input >> m;

    for (int i = 0;i < m;i++) {
        int x,y;
        input >> x >> y;
        Option.push_back({x,y});
    }

    input.ignore();

    string str;
    while (getline(input,str)) {
        stringstream ss(str);

        string name;
        double kt1,kt2;
        vi NguyenVong;

        getline(ss, name, ',');
        ss >> kt1;
        ss.ignore(1);
        ss >> kt2;
        // cout << kt1 << ' ' << kt2 << endl;
        int x;
        ss.ignore(1);
        while (ss >> x) {
            NguyenVong.push_back(x);
            ss.ignore(1);
        }

        Candidates.push_back(Person(name, kt1, kt2, NguyenVong));
    }

    Listed_Candidates.resize(m + 1);

    return true;
}

int Partition_Options(vector<pii> & Options, int l, int r) {
    pii pivot = Options[r];
    int i = l - 1;
    for (int j = l;j < r;j++) {
        if (Options[j] < pivot) {
            i++;
            swap(Options[i], Options[j]);
        }
    }
    ++i;
    swap(Options[i], Options[r]);
    return i;
}

void OptionSort(vector<pii>& Options,int l,int r) {
    if (l >= r) return;
    int pivot = Partition_Options(Options, l, r);
    OptionSort(Options, l, pivot - 1);
    OptionSort(Options, pivot + 1, r);
} 

void Options_Sort(vector<pii>& Options) {
    OptionSort(Options, 0, Options.size() - 1);
}

int FindOptions(int m, vector<pii> & Options, int val) {
    int l = 0;
    int r = m - 1;
    int ans = -1;

    // output << m << endl;

    while (l <= r) {
        int mid = l + r >> 1;
        // output << l << ' ' << r << endl;
        if (Options[mid].first >= val) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    return ans;
}

int Partition_Candidates(vector<Person> & Candidates, int l,int r) {
    Person Pivot;
    Pivot.Copy(Candidates[r]);
    int i = l - 1;
    for (int j = l;j < r;j++) {
        if (Candidates[j] > Pivot) {
            i++;
            swapPerson(Candidates[i], Candidates[j]);
        }
    }
    ++i;
    swapPerson(Candidates[i], Candidates[r]);
    return i;
}

void CandidateSort(vector<Person>& Candidates,int l,int r) {
    if (l >= r) return;
    int pivot = Partition_Candidates(Candidates, l, r);
    CandidateSort(Candidates, l, pivot - 1);
    CandidateSort(Candidates, pivot + 1, r);
}

void Candidates_Sort(vector<Person>& Candidates) {
    CandidateSort(Candidates, 0, Candidates.size() - 1);
}

int Process_1Person(int m, Person a, vector<pii> & Options,vector<vector<Person>> & Listed_Candidates) {
    for (auto x : a.NguyenVong) {
        int pos = FindOptions(m, Options, x);
        if (pos == -1 || (pos != -1 && Options[pos].second <= 0)) continue;
        Options[pos].second--;
        Listed_Candidates[pos].push_back(a);
        return 1;
    }
    Listed_Candidates[m].push_back(a);
    return -1;
}

void Solve_List_Candidates(int m, vector<pii> & Options, vector<Person> & Candidates,vector<vector<Person>> & Listed_Candidates) {
    for (auto x : Candidates) {
        Process_1Person(m, x, Options, Listed_Candidates);
    }
}