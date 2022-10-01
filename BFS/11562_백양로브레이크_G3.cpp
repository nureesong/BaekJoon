/*************************************/
// [11562] 백양로 브레이크 (골드3)
// FloodFill - 40ms, 2944KB
// 15:35 ~ 16:30 (55분 소요)
// 각 노드에서 나가는 방향과 들어오는 방향의 간선에 대해 각각 인접 리스트를 만들었다.
// 1. 현재 노드에서 나가는 엣지로 연결된 노드는 양방향으로 안 바꿔도 갈 수 있다.
// 2. 현재 노드로 들어오는 엣지로 연결된 노드는 "양방향 길로 바꿔야" 갈 수 있다.
// *틀린 이유* 같은 노드에 나중에 재방문하더라도 개수가 더 적으면 상태발전!!
/*************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
// 인접리스트
vector<int> out[250 + 1]; // i번 노드에서 나가는 엣지
vector<int> in[250 + 1];  // i번 노드로 들어오는 엣지

// i->j 갈 때 일방통행에서 양방향으로 바꿔야 하는 최소 개수 기록
int chk[250 + 1][250 + 1]; 
struct STATUS {
    int n, cnt;
};
queue<STATUS> q;

void Input() {
    cin >> N >> M;
    int u,v,b;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> b;
        out[u].push_back(v);
        in[v].push_back(u);
        if (b) {
            out[v].push_back(u);
            in[u].push_back(v);
        }
    }
}

void BFS(int s) {
    q.push({s, 0});
    chk[s][s] = 0;

    while (!q.empty()) {
        STATUS cur = q.front(); q.pop();

        // 1. 현재 노드에서 나가는 엣지로 연결된 노드는 양방향으로 안 바꿔도 갈 수 있다.
        for (int nbd : out[cur.n]) {
            if (cur.cnt >= chk[s][nbd]) continue;

            q.push({nbd, cur.cnt});
            chk[s][nbd] = cur.cnt;
        }

        // 2. 현재 노드로 들어오는 엣지로 연결된 노드는 양방향으로 바꿔야 갈 수 있다.
        for (int nbd : in[cur.n]) {
            int ncnt = cur.cnt + 1;
            if (ncnt >= chk[s][nbd]) continue;

            q.push({nbd, ncnt});
            chk[s][nbd] = ncnt;
        }
    }
}

void FloodFill() {
    fill(&chk[1][1], &chk[N][N+1], 0x7fffffff);
    for (int s = 1; s <= N; s++) {
        BFS(s);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    FloodFill();

    int K, s, e;
    cin >> K;
    while (K--) {
        cin >> s >> e;
        cout << chk[s][e] << "\n";
    }
}
