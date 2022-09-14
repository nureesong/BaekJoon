/********************************/
// [2636] 치즈 (Flood Fill - BFS)
// 공기와 맞닿은 부분을 제거해야 하므로 바깥쪽 영역을 BFS로 탐색
// 맨 처음에는 무조건 빈 칸인 (0,0)에서 시작하고 
// 그 다음부터는 치즈가 제거된 위치에서 시작하려고 했는데 포기..
// 매시간 vis를 초기화하고 (0,0)에서 탐색 시작
/********************************/

#include <iostream>
#include <queue>
using namespace std;

int N, M;
int arr[100 + 10][100 + 10]; // 1:치즈, 0:공기
int vis[100 + 10][100 + 10];
struct STATUS {
	int r, c;
};
queue<STATUS> q;
int cheese; // 치즈 개수

// 항상 공기인 (0, 0)부터 탐색 시작
// 치즈를 만나면 테두리라는 뜻이므로 제거하고 0으로 바꾸기
int BFS() {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	q.push({0, 0});
	vis[0][0] = 1;
	int cnt = 0; // 제거한 치즈 개수

	while (!q.empty()) {
		STATUS cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr < 0 || nr > N || nc < 0 || nc > M) continue;
			if (vis[nr][nc]) continue;
			
			// 인접영역이 공기면 큐에 넣고 치즈면 제거한다.
			if (arr[nr][nc] == 0) q.push({ nr,nc });
			else {
				arr[nr][nc] = 0; // 치즈 테두리 제거
				cnt++;
			}
			vis[nr][nc] = 1; // 제거한 치즈도 방문 처리해서 재방문 방지
		}
	}
	return cnt;
}

void Solve() {
	int t = 0;

	while (1) {
		fill(&vis[0][0], &vis[N-1][M], 0);

		int remove = BFS(0, 0);
		if (cheese > remove) {
			cheese -= remove;
			t++;
		}
		else {
			cout << t + 1 << "\n" << cheese << "\n";
			return;
		}
	}
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			cheese += arr[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
}
#endif
