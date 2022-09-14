/********************************/
// [2667] 단지 번호붙이기
// Flood Fill - DFS
// (1,1)부터 시작하면 인덱스 범위 검사할 필요없다.
/********************************/

#include <iostream>
#include <algorithm>
using namespace std;

int N;
char arr[25 + 5][25 + 5]; // 0:벽, 1:집. (1,1)부터 시작 (인덱스 범위 초과X)
int H[313 + 5];  // 단지별 집의 개수 (단지수 최대: N^2의 절반 정도)

// (r,c)가 속한 단지의 집의 개수를 리턴한다.
int Flood_Fill(int r, int c) {
	int cnt_ff = 1;   // 자기 자신
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };
	
	arr[r][c] = '0';  // 방문한 집은 0으로 바꾸기
	
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = r + dc[i];
		if (arr[nr][nc] != '0') continue;
		cnt_ff += Flood_Fill(nr, nc); // 다음 위치에서 확인한 집의 개수를 누적
	}
	return cnt_ff;
}

int Solve() {
	int cnt_danji = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (arr[i][j] != '1') continue;
			H[cnt_danji++] = Flood_Fill(i, j); // DFS 재귀
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
