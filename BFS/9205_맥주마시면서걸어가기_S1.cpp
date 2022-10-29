/**********************************/
// [9205] 맥주 마시면서 걸어가기 (실버1)
// BFS - 거리 기반 상태발전 (0ms)
/**********************************/

#include <iostream>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;

int N;
struct POS {
    int x, y;
}P[102]; // 0: 상근이 집, 1~N: 편의점, N+1: 페스티벌
int D[102][102];

int vis[101];
queue<int> q;


void Input() {
    // Init;
    memset(D, 0, sizeof(D));
    memset(vis, 0, sizeof(vis));

    cin >> N;
    for (int i = 0; i < N+2; i++) {
        cin >> P[i].x >> P[i].y;
    }
}

int dist(POS A, POS B) {
    return abs(A.x - B.x) + abs(A.y - B.y);
}

void CalcDist() {
    for (int i = 0; i < N+1; i++) {
        for (int j = i+1; j < N+2; j++) {
            D[i][j] = D[j][i] = dist(P[i], P[j]);
        }
    }
}

bool BFS() {
    q = {};
    q.push(0);
    vis[0] = 1;

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        for (int i = 1; i < N+2; i++) {
            if (vis[i]) continue;
            if (D[cur][i] > 1000) continue;
            if (i == N+1) return true;

            q.push(i);
            vis[i] = 1;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        Input();
        CalcDist();
        cout << (BFS() ? "happy" : "sad") << "\n";
    }
}
