/*************************************/
// [2665] 미로만들기 (골드4)
// 0ms, 2172KB
// 12:57 ~ 13:14 (17분 소요)
/*************************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int arr[50 + 2][50 + 2]; // 0: 검은방, 1:흰방
int chk[50 + 2][50 + 2]; // (0,0) -> (i,j)에 오는동안 흰방으로 바꾼 개수
struct STATUS {
    int r,c;
    int cnt; // 현재까지 검은방에서 흰방으로 바꾼 개수
};
queue<STATUS> q;

void Input() {
    cin >> N;
    char c;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> c;
            arr[i][j] = c - '0';
        }
    }
}

int BFS() {
    fill(&chk[0][0], &chk[N-1][N], 0x7fffffff);
    static int dr[] = {-1,1,0,0};
    static int dc[] = {0,0,-1,1};

    q.push({0,0,0});
    chk[0][0] = 0;

    while (!q.empty()) {
        STATUS cur = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

            int ncnt = cur.cnt + 1 - arr[nr][nc];
            if (ncnt >= chk[nr][nc]) continue;

            q.push({nr,nc,ncnt});
            chk[nr][nc] = ncnt;
        }
    }

    return chk[N-1][N-1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << BFS() << "\n";
}
