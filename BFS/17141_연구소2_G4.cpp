/**************************************/
// [17141] 연구소2 (골드4)
// 1) DFS - 조합으로 M개의 바이러스 선택
//    선택되지 않은 바이러스들은 빈 칸으로 간주
// 2) BFS - 선택한 바이러스에서 전염시키며 시간 기록
/**************************************/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
int arr[50 + 5][50 + 5]; // 0:빈칸, 1:벽, 2:바이러스 후보
int vis[50 + 5][50 + 5]; // 바이러스(1)로부터 떨어진 거리 기록
int goal;
int mintime = 2500;

int cnt_virus;
int pick[10]; // 선택된 바이러스 M개 인덱스

struct STATUS {
	int r, c;
};
STATUS virus[10]; // 바이러스 위치 후보지 (arr값 = 2)
queue<STATUS> q;


int BFS() {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	// Init
	fill(&vis[0][0], &vis[N - 1][N], 0);
	int maxtime = 1;
  int n_virus = M; // 바이러스 퍼진 후 개수

	// 선택완료한 바이러스 위치를 초기 큐에 넣기
	for (int j = 0; j < M; j++) {
		q.push(virus[pick[j]]);
		vis[virus[pick[j]].r][virus[pick[j]].c] = 1;
	}

	// 바이러스 퍼뜨리면서 시간 기록  
	while (!q.empty()) {
		STATUS cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (vis[nr][nc] || arr[nr][nc] == 1) continue; // 방문했거나 벽은 패스

			q.push({ nr,nc });
			vis[nr][nc] = vis[cur.r][cur.c] + 1;
			n_virus++;
			if (vis[nr][nc] > maxtime) maxtime = vis[nr][nc];
		}
	}

	if (n_virus == goal) return maxtime - 1; // 모든 빈칸에 퍼졌을 때만 전염시간 리턴
	return -1; // 모든 빈칸에 퍼뜨릴 수 없다.
}

void comb(int s, int cnt) {
	if (cnt == M) {
		// 모든 빈칸에 퍼졌을 때만 최소 시간 갱신
		int t = BFS();
		if (t != -1 && t < mintime) mintime = t;
		return;
	}

	for (int i = s; i < cnt_virus; i++) {
		pick[cnt] = i;
		comb(i + 1, cnt + 1);
	}
}


void Input() {
	cin >> N >> M;

	goal = N * N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			
			if (arr[i][j] == 2) virus[cnt_virus++] = { i,j };
			else if (arr[i][j] == 1) goal--;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
  
	Input();
	comb(0, 0);

	if (mintime == 2500) cout << "-1\n";
	else cout << mintime << "\n";
}
#endif
