#include <iostream>
using namespace std;

int N;

struct Point {
    int x, y;
}C[100000 + 10];

int dist[100000 + 10];

void Input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> C[i].x >> C[i].y;
    }    
}

int Solve() {
    int total = 0;
    for (int i = 1; i < N; i++) {
        dist[i] = abs(C[i].x - C[i+1].x) + abs(C[i].y - C[i+1].y);
        total += dist[i];
    }

    // Sliding Windows
    int min = total;
    int tmp;
    for (int i = 2; i <= N-1; i++) {
        tmp = total - dist[i-1] - dist[i] + abs(C[i-1].x - C[i+1].x) + abs(C[i-1].y - C[i+1].y);
        if (tmp < min) min = tmp;
    }
    return min;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << Solve() << "\n";
}
