/***********************************/
// [13913] 숨바꼭질 4 (골드4)
// 12ms
// 걸어서 이동하든 순간이동을 하든 둘다 1초 소요
// 경로를 출력해야 하므로 이동할 때마다 "path[도착] = 출발" 을 저장한다.
// 메모리 초과: 좌표에 0이 포함되어 있으므로 path를 -1로 초기화해야 함!!!
// 가지치기: 수빈 > 동생 => -1 만 선택 (시간 차이 없음)
/***********************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, K;
int chk[100000 + 10]; // N -> i 이동하는 최단시간 기록
int path[100000 + 10];
queue<int> q;

int BFS() {
    int nx, nt;
    fill(chk, chk + 100001, 100001);
    fill(path, path + 100001, -1);

    if (N == K) return 0;

    q.push(N);
    chk[N] = 0;

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        int dx[3] = {-1, 1, cur};
        for (int i = 0; i < 3; i++) {
            // 가지치기 - 시간 차이 없음..
            if (cur > K && i != 0) continue; // 수빈이 > 동생 => -1 이동만 선택

            int nx = cur + dx[i];
            int nt = chk[cur] + 1;

            if (nx == K) {
                path[K] = cur;
                return nt;
            }
            if (nx < 0 || nx > 100000) continue;
            if (nt >= chk[nx]) continue;

            q.push(nx);
            chk[nx] = nt;
            path[nx] = cur;
        }
    }
    return -1;
}

void Print_Path(int n) {
    if (n == -1) return;
    Print_Path(path[n]);
    cout << n << " ";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    cout << BFS() << "\n";
    Print_Path(K);
    cout << "\n";
}
