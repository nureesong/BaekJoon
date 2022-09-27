/*******************************************************************/
// [11967] 불켜기 (골드2)
// 204ms - 새로 불 켜진 방 없을 때까지 (1,1)에서 출발하는 Flood Fill 실행
// 8ms - (1,1)에서 출발하는 Flood Fill 한 번만 실행
//       탐색 중에 인접한 방이지만 불이 꺼져있어 가지 못했던 곳을 set에 저장해두기
//       set에 있는 방에 불이 새로 켜지면 큐에 push -> 점프 이동하는 효과
/*******************************************************************/

// 8ms - Flood Fill 한 번만 실행 (솔루션)
#if 1
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

int N, M; // 맵 크기, 스위치 간선 개수
int flag[100 + 2][100 + 2]; // 스위치 ON/OFF 상태. (1,1) 시작
int vis[100 + 2][100 + 2];
int cnt;  // 불 켜진 방 개수

struct POS {
	int r, c;
};
vector<POS> adj[100 + 2][100 + 2]; // 각 방마다 스위치를 가진 방 정보
queue<POS> q;

// 현위치와 인접한 방이지만, 불이 꺼져있어서 못 간 방 번호 저장
// 나중에 이 방에 불 켜졌을 때, 점프해서 이동하면 매번 (1,1)부터 재탐색 필요X
// 방 번호 매핑: (r,c) -> r * 1000 + c
// (1,1) -> 1001, (100,100) -> 100100
unordered_set<int> dark; 


void Input() {
	cin >> N >> M;
	int x, y, a, b;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> a >> b;
		adj[x][y].push_back({ a,b });
	}
}

// 현재 방에서 스위치 가진 방 불 다 켜고 제거하기
void SwitchOn(int r, int c) {
	for (POS &nbd : adj[r][c]) {
		if (flag[nbd.r][nbd.c]) continue;
		flag[nbd.r][nbd.c] = 1;
		cnt++;

		// 새로 불 켜진 방이 이전에 불이 꺼져있어 못 간 방인지 확인
		int num = nbd.r * 1000 + nbd.c;
		auto it = dark.find(num);
		if (it != dark.end()) { // 이제 불 켜졌으니 점프이동!
			dark.erase(it);
			q.push(nbd);
			vis[nbd.r][nbd.c] = 1;
			SwitchOn(nbd.r, nbd.c);  // 불도 미리 켜둔다.
		}
	}
	adj[r][c].clear();
}

void FloodFill() {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };
	
	// 초기화: (1,1) 방은 항상 불 켜져있다.
	q.push({ 1,1 });
	flag[1][1] = 1; 
	vis[1][1] = 1;
	cnt = 1;
	SwitchOn(1, 1); // (1,1) 방에 있는 스위치 다 켜기

	while (!q.empty()) {
		POS cur = q.front(); q.pop();

		// 인접한 방 중 불켜진 곳으로 이동
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
			if (vis[nr][nc]) continue;
			
			// 인접한 방이지만 불 꺼져있어서 이동 못한 곳 저장
			if (!flag[nr][nc]) {
				dark.insert(nr * 1000 + nc);
				continue;
			}
			
			q.push({ nr,nc });
			vis[nr][nc] = 1;
			SwitchOn(nr, nc);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	FloodFill();
	cout << cnt << "\n";
}
#endif



// 204ms - 불 켜질 때마다 (1,1)에서 FF 실행
#if 0
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int N, M; // 맵 크기, 스위치 간선 개수
int flag[100 + 2][100 + 2]; // 스위치 ON/OFF 상태. (1,1) 시작
int vis[100 + 2][100 + 2];

struct POS {
	int r, c;
};
vector<POS> adj[100 + 2][100 + 2]; // 각 방마다 스위치를 가진 방번호 정보
queue<POS> q;


void Input() {
	cin >> N >> M;

	// Init
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			flag[i][j] = 0;
			adj[i][j].clear();
		}
	}

	int x, y, a, b;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> a >> b;
		adj[x][y].push_back({ a,b });
	}
}

int FloodFill(int cnt) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };
	fill(&vis[1][1], &vis[N][N+1], 0);
	vis[1][1] = 1;
	q.push({1,1});

	while (!q.empty()) {
		POS cur = q.front(); q.pop();

		// 현재 방에서 스위치 가진 방 불 다 켜고 제거하기
		if (!adj[cur.r][cur.c].empty()) {
			for (POS &nbd : adj[cur.r][cur.c]) {
				if (flag[nbd.r][nbd.c]) continue;
				flag[nbd.r][nbd.c] = 1;
				cnt++;
			}
			adj[cur.r][cur.c].clear();
		}

		// 인접한 방 중 불켜진 곳으로 이동
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
			if (!flag[nr][nc] || vis[nr][nc]) continue;

			q.push({nr,nc});
			vis[nr][nc] = 1;
		}
	}
	return cnt;
}

int Solve() {
	int sol = 1; // 불 켜진 방 개수

	while (1) {
		flag[1][1] = 1;     // (1,1) 방은 항상 불 켜져있다.
		int ret = FloodFill(sol); // 현재까지 불 켜진 방 개수 입력
		if (ret > sol) sol = ret;
		else break; // 불 켜진 방 개수가 증가하지 않으면 종료
	}
	return sol;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
#endif
