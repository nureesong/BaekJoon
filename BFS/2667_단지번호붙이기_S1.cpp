/********************************/
// [2667] 단지 번호붙이기
// 
// (1,1)부터 시작하도록 만들면 인덱스 범위 검사할 필요없다.
/********************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
char arr[25 + 5][25 + 5]; // 0:벽, 1:집. (1,1)부터 시작 (인덱스 범위 초과X)
int H[313 + 5];  // 단지별 집의 개수 (단지수 최대: N^2의 절반 정도)

struct STATUS {
	int r, c;
};
queue<STATUS> q;

int BFS(int i, int j) {
	static int dr[] = {-1,1,0,0};
	static int dc[] = {0,0,-1,1};
	
	q.push({ i,j });
	arr[i][j] = '0';
	int cnt = 1;

	while (!q.empty()) {
		STATUS cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (arr[nr][nc] != '1') continue; // arr[nr][nc] == '0' Error!! 바운더리에는 숫자 0이 들어있음.
			
			q.push({ nr,nc });
			arr[nr][nc] = '0';
			cnt++;
		}
	}
	return cnt;
}

int Solve() {
	int cnt_danji = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (arr[i][j] != '1') continue;
			H[cnt_danji++] = BFS(i, j); 
		}
	}

	sort(H, H + cnt_danji);
	return cnt_danji;
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> &arr[i][1];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	int cnt_danji = Solve();
	
	cout << cnt_danji << "\n";
	for (int i = 0; i < cnt_danji; i++) {
		cout << H[i] << "\n";
	}
}
