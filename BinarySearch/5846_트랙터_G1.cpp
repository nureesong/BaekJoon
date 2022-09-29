/***********************************************/
// [5846] 트랙터 (골드1)
// Parametric Search & FloodFill (200ms)
// O(logD * N^2)  
// D = 10^6 = 약 2^20 (최대 높이차) -> logD = 20
/**********************************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int tar;  // 목표 방문 칸수
int arr[500 + 2][500 + 2];
int minh, maxh;  // 최소, 최대 높이

struct STATUS {
	int r, c;
};
queue<STATUS> q;
int vis[500 + 2][500 + 2];


void Input() {
	cin >> N;
	tar = (N*N + 1) / 2; 

	minh = 0x7fffffff;
	maxh = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			minh = (arr[i][j] < minh) ? arr[i][j] : minh;
			maxh = (arr[i][j] > maxh) ? arr[i][j] : maxh;
		}
	}
}

int FloodFill(int r, int c, int d) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	q.push({ r,c });
	vis[r][c] = 1;
	int cnt = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (vis[nr][nc]) continue;
			if (abs(arr[nr][nc] - arr[cur.r][cur.c]) > d) continue;

			q.push({ nr,nc });
			vis[nr][nc] = 1;
			cnt++;
		}
	}
	return cnt;
}

int MoveHalf(int d) {
	fill(&vis[0][0], &vis[N - 1][N], 0);

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (vis[r][c]) continue;
			if (FloodFill(r, c, d) >= tar) return 1;
		}
	}
	return 0;
}

int BS(int s, int e) {
	int sol = -1;
	int m;

	while (s <= e) {
		m = (s + e) / 2;
		if (MoveHalf(m)) {
			sol = m;
			e = m - 1;
		}
		else s = m + 1;
	}
	return sol;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << BS(0, maxh - minh) << "\n";
}
