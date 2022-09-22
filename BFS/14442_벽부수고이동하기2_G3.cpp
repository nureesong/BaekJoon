// bool vis 388ms, 20252KB
#if 1
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, M, K;
int arr[1000 + 5][1000 + 5]; // (1,1) 시작. 0: 빈칸, 1:벽
bool vis[10 + 2][1000 + 5][1000 + 5]; // 부순 벽 개수별 방문여부

struct STATUS {
	int k; // 부순 벽의 개수 (0~K)
	int r, c;
	int d; // (1,1)부터 (r,c)까지 최단거리
};
queue<STATUS> q;

void Input() {
	cin >> N >> M >> K;

	char c;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> c;
			arr[i][j] = c - '0';
		}
	}
}

int BFS() {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	if (N == 1 && M == 1) return 1;

	q.push({ 0,1,1,1 });
	vis[0][1][1] = true;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nk; // 벽 부술지 말지에 따라 달라짐
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			int nd = cur.d + 1;

			if (nr < 1 || nr > N || nc < 1 || nc > M) continue;
			
			// 빈 칸이면, 벽 안 부수고 이동(같은 채널)
			// 벽이고 K개 미만 부쉈으면, 하나 더 부수기(다음 채널)
			// 이미 K개 벽 다 부쉈으면 벽으로 이동불가
			if (arr[nr][nc] == 0) nk = cur.k;  
			else if (cur.k < K) nk = cur.k + 1; 
			else continue; 

			if (vis[nk][nr][nc]) continue;

			// 목적지에 가장 먼저 도착하면 끝 (거리 가중치 동일)
			if (nr == N && nc == M) return nd;

			q.push({ nk,nr,nc,nd });
			vis[nk][nr][nc] = true;
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
	return 0;
}
#endif


// int chk 548ms, 55164KB
#if 0
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, M, K;
int arr[1000 + 5][1000 + 5]; // (1,1) 시작. 0: 빈칸, 1:벽
// 채널: 부순 벽 개수별 (1,1)부터의 최단거리 저장
int chk[10 + 2][1000 + 5][1000 + 5];

struct STATUS {
	int k; // 부순 벽의 개수 (0~K)
	int r, c;
};
queue<STATUS> q;

void Input() {
	cin >> N >> M >> K;
	char c;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> c;
			arr[i][j] = c - '0';
		}
	}
}

int BFS() {
	fill(&chk[0][1][1], &chk[K][1000][1000 + 1], 0x7fffffff);
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	if (N == 1 && M == 1) return 1;

	q.push({ 0,1,1 });
	chk[0][1][1] = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nk; // 벽 부술지 말지에 따라 달라짐
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			int curdist = chk[cur.k][cur.r][cur.c];

			if (nr < 1 || nr > N || nc < 1 || nc > M) continue;

			if (arr[nr][nc] == 0) {
				nk = cur.k;  // 빈 칸이면 벽 안 부수고 이동(같은 채널)
			}
			else if (cur.k < K) {
				nk = cur.k + 1; // 벽이고, K개 미만 부쉈으면 하나 더 부수기(다음 채널)
			}
			else continue; // 이미 K개 벽 다 부쉈으면 벽으로 이동불가

			// 가지치기 (부수고 이동하는 게 최단인지 확인)
			if (curdist + 1 >= chk[nk][nr][nc]) continue;
			
			q.push({ nk,nr,nc });
			chk[nk][nr][nc] = curdist + 1;

			// 목적지에 가장 먼저 도착하면 끝 (거리 가중치 동일)
			if (nr == N && nc == M) return chk[nk][N][M];
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
	return 0;
}
#endif
