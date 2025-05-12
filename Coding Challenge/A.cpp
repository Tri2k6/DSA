#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

int distSq(Point a, Point b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

bool isSame(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

bool isSquare(Point p[]) {
    sort(p, p + 4, [](Point a, Point b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    int d0 = distSq(p[0], p[1]);
    int d1 = distSq(p[0], p[2]);
    int d2 = distSq(p[1], p[3]);
    int d3 = distSq(p[2], p[3]);
    int d_diag1 = distSq(p[0], p[3]);
    int d_diag2 = distSq(p[1], p[2]);

    return d0 > 0 && d0 == d1 && d1 == d2 && d2 == d3 && d_diag1 == d_diag2;
}

int main() {
    Point p[4];
    for (int i = 0; i < 4; i++) {
        cin >> p[i].x >> p[i].y;
    }

    if (isSquare(p)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}