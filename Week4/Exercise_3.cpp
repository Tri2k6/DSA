#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

#define inputFile "employee.txt"
#define outputFile "sortedemponage.txt"

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


struct Person {
    string name, id;
    int age;
    Person() {}
    Person(string i, string n, int y) {
        name = n;
        id = i;
        age = y;
    }
    void Copy(Person a) {
        name = a.name;
        id = a.id;
        age = a.age;
    }
};


int GetCurrentYear();
bool Read_Data(int & n, vector<Person> & a);
int CerrTable();
// Tra ve true neu a dung truoc b, false neu a dung sau b
bool cmp(Person a, Person b);
void swap(Person & a, Person & b);
void Print(vector<Person> a);
void interChangeSort(int n, vector<Person> & a);
void InsertionSort(int n, vector<Person> & a);
void SelectionSort(int n, vector<Person> & a);

int main() {

    int n;
    vector<Person> a;
    if (Read_Data(n, a)) {
        int t = CerrTable();
        if (t == 1) InsertionSort(n, a);
        if (t == 2) SelectionSort(n,a);
        if (t == 3) interChangeSort(n,a);
        Print(a);
    } else {
        cerr << "Can not access " << inputFile;
    }
    return 0;
}

int GetCurrentYear() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    struct tm *tm = std::localtime(&current_time);

    int current_year = tm->tm_year + 1900; 
    return current_year;
}

bool Read_Data(int & n, vector<Person> & a) {
    ifstream input(inputFile);
    if (!input.is_open()) return false;

    string str;
    
    while (getline(input,str)) {
        stringstream ss(str);
        string id, name, year;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, year);

        int age = 1900;
        if (year.size() > 4) {
            int tmp = (year[year.length() - 2] - '0') * 10 + (year[year.length() - 1] - '0');
            age = 1900 + tmp;
        } else age = stoi(year);

        if (id[0] != 'i') a.push_back(Person(id, name, age));
    }

    n = a.size();

    return true;
}

int CerrTable() {
    int choice;
    cerr << "Choose a sorting algorithm:\n";
    cerr << "1. Insertion Sort\n";
    cerr << "2. Selection Sort\n" ;
    cerr << "3. Interchange Sort\n";
    cerr << "Enter your choice: ";
    cin >> choice;
    return choice;
}

bool cmp(Person a, Person b) {
    if (a.age != b.age) return a.age < b.age;
    return a.name < b.name;
}

void swap(Person & a, Person & b) {
    Person tmp;
    tmp.Copy(a);
    a.Copy(b);
    b.Copy(tmp);
}

void interChangeSort(int n, vector<Person> & a) {
    for (int i = 0;i < n;i++) {
        for (int j = i + 1;j < n;j++) {
            if(!cmp(a[i], a[j])) {
                swap(a[i], a[j]);
            }
        }
    }
}

void Print(vector<Person> a) {
    ofstream output(outputFile);
    for (auto x : a) {
        output << x.id << ' ' << x.name << ' ' << x.age << endl;
    }
}

void SelectionSort(int n, vector<Person> & a) {
    for (int i = 0;i < n;i++) {
        int idx = i;
        for (int j = i + 1;j < n;j++) {
            if (!cmp(a[idx], a[j])) idx = j;
        }   
        swap(a[i], a[idx]);
    }
}

void InsertionSort(int n, vector<Person> & a) {
    for (int i = 1;i < n;i++) {
        int j = i - 1;
        Person val;
        val.Copy(a[i]);
        while (j >= 0 && !cmp(a[j], val)) {
            a[j + 1].Copy(a[j]);
            j--;
        }
        a[j + 1].Copy(val);
    }
}