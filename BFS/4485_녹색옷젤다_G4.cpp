/**********************************/
// [4485] 녹색 옷 입은 사람 젤다 - 골드4
/**********************************/
#if 0
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int arr[125 + 10][125 + 10];
int chk[125 + 10][125 + 10];

struct STATUS {
	int r, c;
};

int BFS() {
	int dr[] = { -1,1,0,0 };
	int dc[] = { 0,0,-1,1 };
	queue<STATUS> q;
	
	q.push({ 0,0 });
	chk[0][0] = arr[0][0];

	while (!q.empty()) {
		STATUS cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			
			int nd = chk[cur.r][cur.c] + arr[nr][nc];
			if (nd >= chk[nr][nc]) continue;

			q.push({ nr,nc });
			chk[nr][nc] = nd;
		}
	}
	return chk[N - 1][N - 1];
}

void Input() {
	for (int i = 0; i < N; i++) {
		//2차원 배열 초기화 : 각 행별로 1차원 배열 초기화!!!
		fill(chk[i], chk[i] + N, 0x7fffffff);
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	
	int p = 0;
	while (1) {
		cin >> N;
		if (N == 0) break;

		p++;
		Input();
		cout << "Problem " << p << ": " << BFS() << "\n";
	}	
}
#endif
