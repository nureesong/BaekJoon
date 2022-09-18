/***************************************************/
// [13549] 숨바꼭질 3 (골드5)
// -1, +1 걸어서 이동 1초, *2 로 순간이동할 때는 0초 소요!!
// 경우의 수마다 가중치가 다르므로 chk 배열에 최고 경험을 저장하고 이를 기반으로 상태 발전
// 최악의 경우: N = 100,000, K = 0 => 수빈이는 계속 -1씩밖 움직여야 하므로 최대 10만초 소요
/**************************************************/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, K;             // N: 수빈이 위치, K: 동생 위치
int chk[100000 + 10]; // chk[i] : N -> i 이동 최단시간
queue<int> q;

int BFS() {
    fill(chk, chk + 100001, 100001);
    
    q.push(N);
    chk[N] = 0;

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        int dx[3] = {-1, 1, cur}; // 수빈이는 3가지 경우의 수로 이동가능
        static int dt[3] = {1, 1, 0};    // 걸으면 1초, 순간이동 0초 소요
        for (int i = 0; i < 3; i++) {
            int next = cur + dx[i];
            
            if (next < 0 || next > 100000) continue;
            if (chk[cur] + dt[i] >= chk[next]) continue;
            
            chk[next] = chk[cur] + dt[i];
            q.push(next);
        }
    }
    return chk[K];
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    cout << BFS() << "\n";
}
