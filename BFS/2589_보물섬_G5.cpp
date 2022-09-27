/************************************/
// [2589] 보물섬 (골드5)
// Flood Fill - 육지영역 중 최대길이
// 최적화: 상하/좌우 둘다 육지인 곳은 절대 육지의 끄트머리가 될 수 없다.
// 80ms -> 12ms (최적화 적용시)
/************************************/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
int arr[50 + 2][50 + 2]; // (1,1) 시작, 0:물, 1:육지
int cop[50 + 2][50 + 2]; // 원본arr를 복사해서 사용

struct STATUS {
	int r, c;
	int d;
};
queue<STATUS> q;


void Input() {
	char c;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> c;
			if (c == 'L') arr[i][j] = 1;
		}
	}
}

int BFS(int r, int c) {
	copy(&arr[1][1], &arr[N][M + 1], &cop[1][1]);
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	q.push({ r,c,0 });
	cop[r][c] = 0; // 방문한 육지는 0으로 바꾸기

	STATUS cur;
	while (!q.empty()) {
		cur = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (!cop[nr][nc]) continue;

			q.push({ nr,nc,cur.d + 1 });
			cop[nr][nc] = 0;
		}
	}

	return cur.d;
}

int FloodFill() {
	int maxdist = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (arr[i][j] == 0) continue;

			// 최적화 - 상하/좌우 둘다 육지인 곳은 끄트머리X
			if (arr[i - 1][j] && arr[i + 1][j]) continue;
			if (arr[i][j - 1] && arr[i][j + 1]) continue;

			int ret = BFS(i, j);
			maxdist = (ret > maxdist) ? ret : maxdist;
		}
	}
	return maxdist;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << FloodFill() << "\n";
}
