/********************************/
// [2468] 안전 영역
// Flood Fill - BFS (20ms)
/********************************/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int arr[100 + 10][100 + 10]; // (1,1) 시작
int vis[100 + 10][100 + 10];
int maxh = 0;   // 모든 지역 중 최대 높이 (최대 강수량 = 최대높이 - 1)
int maxcnt = 1; // maxh = 1이면 maxcnt는 한번도 갱신되지 않으므로 0으로 초기화X

struct STATUS {
	int r, c;
};
queue<STATUS> q;

// (r,c) 지역에서 높이가 h보다 큰 인접영역 찾기
void BFS(int r, int c, int h) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	q.push({ r,c });
	vis[r][c] = 1;

	while (!q.empty()) {
		STATUS cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (vis[nr][nc]) continue;
			if (arr[nr][nc] <= h) continue;

			q.push({ nr,nc });
			vis[nr][nc] = 1;
		}
	}
}

void Solve() {
	int cnt;

	for (int h = 1; h < maxh; h++) {
		// Init
		fill(&vis[0][0], &vis[N][N + 1], 0);
		cnt = 0;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (arr[i][j] <= h) continue; // 높이가 h보다 커야 이동가능
				if (vis[i][j]) continue;      // h보다 높은 지역 중복방문
				BFS(i, j, h);
				cnt++;
			}
		}
		if (cnt > maxcnt) maxcnt = cnt;
	}
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] > maxh) maxh = arr[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
	cout << maxcnt << "\n";
}
