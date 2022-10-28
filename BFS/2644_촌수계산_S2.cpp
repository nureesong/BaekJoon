/****************************/
// [2644] 촌수계산 (실버2)
/****************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, A, B;
vector<int> adj[100 + 1]; // Undirected

int vis[100 + 1];
struct STATUS {
    int n, cnt;
};
queue<STATUS> q;


void Input() {
    cin >> N >> A >> B >> M;
    int p, c;
    for (int i = 0; i < M; i++) {
        cin >> p >> c;
        adj[p].push_back(c);
        adj[c].push_back(p);
    }
}

int BFS() {
    q.push({A, 0});
    vis[A] = 1;

    while (!q.empty()) {
        STATUS cur = q.front(); q.pop();

        for (int nbd : adj[cur.n]) {
            if (vis[nbd]) continue;
            if (nbd == B) return cur.cnt + 1;

            q.push({nbd, cur.cnt + 1});
            vis[nbd] = 1;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << BFS() << "\n";
}
