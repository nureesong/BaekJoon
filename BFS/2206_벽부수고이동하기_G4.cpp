/**********************************/
// [2206] 벽 부수고 이동하기 (BFS)
// 벽 부수지 않고 이동, 벽 하나 선택해서 부수고 이동 -> 시간초과
// 3차원 배열: 0채널 폭탄 사용하지 않고 이동하는 최단거리 기록
//           1채널 폭탄 사용해서 벽 부쉈을 때 이동하는 최단거리 기록
// 큐 상태 정보에 이동거리 담기: 84ms
// chk 배열에 최단거리 기록  : 92ms
/**********************************/
// 큐에 이동거리 담기
#if 0
#include <iostream>
#include <queue>
using namespace std;

int N, M;

int arr[1000 + 10][1000 + 10];     // 0: 빈 칸, 1: 벽 -> (1,1)부터 시작
int vis[2][1000 + 10][1000 + 10];  // 채널 0: 폭탄 사용전, 채널 1: 폭탄 사용후
int dr[] = {-1,1,0,0}; 
int dc[] = {0,0,-1,1};
struct STATUS{
    int r, c;
    int used; // 폭탄 사용 여부
    int d;    // 이동거리 (시작, 끝나는 칸 포함해서 세기)
};
queue<STATUS> q;

int BFS() {
    if (N == 1 && M == 1) return 1;

    q.push({1, 1, 0, 1});
    vis[0][1][1] = 1;

    while (!q.empty()) {
        STATUS cur = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            if (nr < 1 || nr > N || nc < 1 || nc > M) continue;
            if (nr == N && nc == M) return cur.d + 1;
            
            // 빈칸/벽, 방문여부, 폭탄사용 여부에 따라 두 가지 상태 발전이 가능하다.
            // 1. 빈 칸이고 방문한 적 없으면 폭탄 사용여부에 관계없이 이동할 수 있다.
            if (!arr[nr][nc] && !vis[cur.used][nr][nc]) {
                q.push({nr, nc, cur.used, cur.d + 1});
                vis[cur.used][nr][nc] = 1;
            }
            // 2. 벽이면 한번도 방문한 적은 없고, 폭탄을 사용해야만 이동할 수 있다.
            else if (arr[nr][nc] && !cur.used) {
                q.push({nr, nc, 1, cur.d + 1});
                vis[1][nr][nc] = 1;
            }
        }
    }
    return -1;
}

void Input() {
    char c;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> c;
            arr[i][j] = c - '0';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << BFS() << "\n";
}
#endif


// 큐에 이동거리 정보 담지 않고 chk 배열에 최단거리 기록
// chk 배열에 최단거리를 기록할거면 큰 수로 초기화 해놓기!!!
#if 0
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;

int arr[1000 + 10][1000 + 10];     // 0: 빈 칸, 1: 벽 -> (1,1)부터 시작
int chk[2][1000 + 10][1000 + 10];  // 채널 0: 폭탄 사용전, 채널 1: 폭탄 사용후
                                   // (1,1)~(r,c)까지의 최단거리 기록
int dr[] = {-1,1,0,0}; 
int dc[] = {0,0,-1,1};
struct STATUS{
    int r, c;
    int used; // 폭탄 사용 여부
};
queue<STATUS> q;

int BFS() {
    if (N == 1 && M == 1) return 1;
    
    memset(chk, 0x7f, sizeof(chk));
    q.push({1, 1, 0});
    chk[0][1][1] = 1;

    while (!q.empty()) {
        STATUS cur = q.front();
        q.pop();
        
        if (cur.r == N && cur.c == M) break;

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 1 || nr > N || nc < 1 || nc > M) continue;
            
            // 빈칸/벽, 방문여부, 폭탄사용 여부에 따라 두 가지 상태 발전이 가능하다.
            // 1. 빈 칸이면 폭탄 사용여부에 관계없이 이동할 수 있다.
            if (!arr[nr][nc]) {
                // 단, 이동 시 최단거리가 아니면 상태 발전시킬 필요없음
                if (chk[cur.used][cur.r][cur.c] + 1 >= chk[cur.used][nr][nc]) continue;
                
                q.push({nr, nc, cur.used});
                chk[cur.used][nr][nc] = chk[cur.used][cur.r][cur.c] + 1;
            }
            // 2. 벽이면 한번도 방문한 적은 없고, 폭탄을 사용해야만 이동할 수 있다.
            else if (arr[nr][nc] && !cur.used) {
                if (chk[0][cur.r][cur.c] + 1 >= chk[1][nr][nc]) continue;

                q.push({nr, nc, 1});
                chk[1][nr][nc] = chk[0][cur.r][cur.c] + 1;
            }
        }
    }

    return (chk[0][N][M] < chk[1][N][M]) ? chk[0][N][M] : chk[1][N][M];
}

void Input() {
    char c;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> c;
            arr[i][j] = c - '0';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    int ret = BFS();
    if (ret == 0x7f7f7f7f) ret = -1;
    cout << ret << "\n";
}
#endif
