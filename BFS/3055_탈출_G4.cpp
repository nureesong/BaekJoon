/**************************************************************/
// [B1] SLIKAR (3055. 탈출 - 골드4)
// BFS, FloodFill
// 홍수, 화가가 방문한 곳을 모두 바위(X)로 바꿔도 된다.
// 화가가 지나간 이후에 홍수가 방문해봤자 화가 이동에 영향을 안 준다.
// 홍수가 방문한 곳에는 화가가 이동할 수 없으므로 바위랑 똑같은 셈.
// 
// [다른 방법]
// 홍수의 각 위치별 최단 도착시간을 먼저 맵 전체에 구해놓고 (초기값 0x7f -> 홍수가 방문하지 않은 곳)
// 이후에 화가를 이동시키는데, 홍수 도착시간보다 더 빠르면 이동시킨다.
/**************************************************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int R, C;
char arr[50 + 2][50 + 2]; // .:빈칸, X: 바위, *: 홍수, D: 도착
int vis[50 + 2][50 + 2];  // 화가 방문한 곳 표시

struct STATUS {
	int f; // 홍수 1, 화가 0
	int r, c;
	int t;
};
queue<STATUS> q;
STATUS S; // 출발지점

void Input() {
	q = {};  // 큐도 초기화해야지.......
	
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 'S') {
				S = { 0,i,j,0 };
				arr[i][j] = '.';
			}
			else if (arr[i][j] == '*') q.push({ 1,i,j,0 });
		}
	}
}

int BFS() {
	fill(&vis[0][0], &vis[R - 1][C], 0);
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	if (arr[S.r][S.c] == 'D') return 0;

	q.push(S);
	vis[S.r][S.c] = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		int nt = cur.t + 1;

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
			if (arr[nr][nc] == 'X') continue;
			
			if (cur.f) {
				if (arr[nr][nc] == '.') {
					q.push({ 1,nr,nc,nt });
					arr[nr][nc] = '*';
				}
			}
			else {
				if (arr[nr][nc] == 'D') return nt;
				if (vis[nr][nc] || arr[nr][nc] != '.') continue;
				q.push({ 0,nr,nc,nt });
				vis[nr][nc] = 1;
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		Input();
		int ret = BFS();
		if (ret == -1) cout << "KAKTUS\n";
		else cout << ret << "\n";
	}
}
