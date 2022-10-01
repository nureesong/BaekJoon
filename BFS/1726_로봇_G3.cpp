/*************************************/
// [1726] 로봇 (골드3)
// 0ms, 2240KB
// 13:35 ~ 15:22 (1h 47분 소요)
// == 써야되는 부분에 =, && 쓰는 실수 안돼!!
/*************************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int R, C;
int arr[100 + 5][100 + 5]; // (1,1), 0: 빈칸, 1: 벽

// 입력받은 방향: 동서남북(1234) -> 상우하좌(0123)로 바꿔서 사용한다.
int dirmap[4+1] = {0,1,3,2,0}; 
// (i,j)에서 d 방향을 바라볼 때 최소 명령횟수
int chk[4][100 + 5][100 + 5]; 

struct STATUS {
    int d;   // 현재 바라보는 방향
    int r,c; // 현재 위치
    int cnt; // 현재까지 명령횟수
};
queue<STATUS> q;
STATUS S, E; // 출발, 도착지점 및 바라보는 방향

void Input() {
    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> arr[i][j];
        }
    }
    cin >> S.r >> S.c >> S.d;
    cin >> E.r >> E.c >> E.d;
    S.d = dirmap[S.d]; // 방향 인덱스 변경
    E.d = dirmap[E.d];
}

int BFS() {
    fill(&chk[0][1][1], &chk[3][R][C+1], 0x7fffffff);
    static int dr[] = {-1,0,1,0}; // 상우하좌
    static int dc[] = {0,1,0,-1};

    if (S.d == E.d && S.r == E.r && S.c == E.c) return 0;

    q.push(S);
    chk[S.d][S.r][S.c] = 0;

    while (!q.empty()) {
        STATUS cur = q.front(); q.pop();
        int ncnt = cur.cnt + 1;

        // 상태발전 경우의 수 총 5가지
        // 명령 1: 현재 방향으로 1,2,3칸 이동
        for (int k = 1; k <= 3; k++) {
            int nr = cur.r + k * dr[cur.d];
            int nc = cur.c + k * dc[cur.d];
            if (nr < 1 || nr > R || nc < 1 || nc > C) break;
            if (arr[nr][nc]) break;
            
            if (ncnt >= chk[cur.d][nr][nc]) continue;
            if (cur.d == E.d && nr == E.r && nc == E.c) return ncnt;

            q.push({cur.d, nr,nc, ncnt});
            chk[cur.d][nr][nc] = ncnt;
        }

        // 명령 2: 시계/반시계 방향 90도 회전
        int rot[] = {1, 3}; // 시계, 반시계(-1로 하면 음수되니까 +3으로 하자)
        for (int i = 0; i < 2; i++) {
            int nd = (cur.d + rot[i]) % 4;
            
            if (ncnt >= chk[nd][cur.r][cur.c]) continue;
            if (nd == E.d && cur.r == E.r && cur.c == E.c) return ncnt;

            q.push({nd,cur.r,cur.c,ncnt});
            chk[nd][cur.r][cur.c] = ncnt;
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
