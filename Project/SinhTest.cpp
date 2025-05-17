#include <iostream>
#include <vector>
#include <limits.h>
#include <random>
#include <cassert>
#include <chrono>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <filesystem>
using namespace std;
using namespace std::chrono;

#define ll long long

const int Ntest = 100;
const string TaskName = "Task_";
const string Folder = "Testcase";

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

long long Rand(long long L, long long R) {
    assert(L <= R);
    return L + rd() % (R - L + 1);
}

void SinhTest(string FileName) {
    ofstream output(FileName);
    int NumQuery = Rand(1,1e6);
    while (NumQuery--) {
        int t = Rand(0,8);
        output << t << ' ';
        // if (t == 0) return;
        if (t == 2 || t == 3 || t == 5 || t == 7 || t == 8) output << endl;
        if (t == 1) {
            int n = Rand(1,1e5);
            output << n << endl;
            for (int i = 0;i < n;i++) {
                output << Rand(1,1e6) << ' ';
            }
            output << endl;
        } 
        if (t == 4) output << Rand(1,1e6) << endl;
        if (t == 6) output << Rand(1,1e6) << endl;
    }
    output << 0;
}

int main() {
    
    filesystem::create_directories(Folder);
    filesystem::create_directories("Answer");

    for (int i = 1;i <= Ntest;i++) {
        string Cur_TaskName = Folder + "/" + TaskName + to_string(i) + ".inp";
        // cout << Cur_TaskName << endl;
        SinhTest(Cur_TaskName);

        system("Task.exe");

        

    }
    return 0;
}