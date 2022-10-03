/***********************************/
// [14475] 첩보원 나약한 (플래티넘3)
// Best FS - PQ: 36ms, 42552KB
/***********************************/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, X;
int T[10000 + 1]; // 각 방의 온도(0:춥, 1:쾌적, 2:덥)
struct EDGE {
    int n, d; // 이웃노드, 이동시간(가중치)
};
vector<EDGE> adj[10000 + 2];

// 마지막으로 경험한 온도가 t이고 
// i번 방에 회복시간 x분 남은 상태로 도착했을 때, 최소 누적 이동시간 기록
int chk[10000 + 2][200 + 2][3 + 2]; 

struct STATUS {
    int n;    // 방 번호 (1 ~ N번)
    int rem;  // 남은 회복시간 (0 ~ X분)
    int t;    // 마지막으로 경험한 온도 (0,1,2)
    int sumd; // 누적 이동시간
};
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        return a.sumd > b.sumd; // 누적이동시간 작을수록 최우선
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


int BFS() {
    fill(&chk[1][0][0], &chk[N][X][2+1], 0x7fffffff);
    pq.push({1,X,0,0});
    chk[1][X][0] = 0; // 1번 방은 항상 춥다.

    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();

        for (EDGE nbd : adj[cur.n]) {
            STATUS next;
            next.n = nbd.n;
            next.sumd = cur.sumd + nbd.d;
            
            // [덥->춥, 춥->덥] 현재 남은 회복시간 > 이동시간 이면 이동불가
            if (abs(cur.t - T[next.n]) == 2 && cur.rem > nbd.d) continue;

            // [쾌춥덥 -> 쾌] 쾌적한 방은 항상 이동가능
            // - 회복시간에서 복도 이동하는 시간 차감 (음수는 0으로)
            // - 이동 후 회복시간 남았으면, 마지막 온도 유지.
            //   다 지났으면, 마지막 경험 온도를 쾌적으로 바꾸기 (자유의 몸!)
            if (T[next.n] == 1) {
                next.rem = max(cur.rem - nbd.d, 0);
                next.t = (next.rem) ? cur.t : 1;
            }
            // [쾌->춥/덥, 춥->춥, 덥->덥] -> 항상 이동가능
            // [춥->덥, 덥->춥] 현제 남은 회복시간 <= 이동시간 이면 이동가능
            // - 남은 회복시간 X로 리셋. 마지막 경험 온도 = 덥/춥
            else {
                next.rem = X;
                next.t = T[next.n];
            }

            // 가지치기
            if (next.sumd >= chk[next.n][next.rem][next.t]) continue;
            // 목적지 도착
            if (next.n == N) return next.sumd;

            pq.push(next);
            chk[next.n][next.rem][next.t] = next.sumd;
        }
    }
    return -1;
}


void Input() {
    cin >> N >> M >> X;
    for (int i = 1; i <= N; i++) {
        cin >> T[i];
    }
    int a, b, d;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> d;
        adj[a].push_back({b,d});
        adj[b].push_back({a,d});
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << BFS() << "\n";
}
