/********************************/
// [9663] N QUEEN (골드4)
// DFS(순열) - 가지치기, 최적화 필수
// 각 행, 열별로 퀸은 한 개만 놓을 수 있다.
// 행을 고정하고 열 선택 => O(N!) => 최대 14! = 약 868억
// 
// 같은 대각선상에 퀸이 존재하는지 확인할 때
// 현재까지 놓인 퀸들과 loop 돌려서 비교하면 오래 걸림
// 좌,우측 대각선 flag 배열 만들어서 확인한다!!
/********************************/
#include <iostream>
#include <cmath>
using namespace std;

int N;
int flag_col[14 + 2];    // 열 번호 선택 여부 (N개)
int flag_diagL[27 + 2];  // 좌측 대각선상 퀸 존재여부 (2N-1개)
int flag_diagR[27 + 2];  // 우측 대각선상 퀸 존재여부 (2N-1개)
int ans;

//struct Point {
//	int r, c;
//}Q[13 + 2];

//int IsQueenDiag(int r, int c) {
//	for (int i = 0; i < r; i++) {
//		if (r - Q[i].r == abs(c - Q[i].c)) return 1;
//	}
//	return 0;
//}

// r번째 행 중 몇 번째 열에 퀸을 놓을지 선택
void DFS(int r) {
	if (r >= N) {
		ans++;
		return;
	}

	for (int c = 0; c < N; c++) {
		// 같은 열에 퀸이 있으면 pass
		if (flag_col[c]) continue;

		// 같은 대각선 상에 다른 퀸이 있으면 pass
		//if (IsQueenDiag(r, c)) continue; // 현재까지 놓인 퀸과 비교 (440ms)
		if (flag_diagR[r + c]) continue;
		if (flag_diagL[r - c + (N - 1)]) continue;

		flag_col[c] = 1;
		flag_diagR[r + c] = 1;
		flag_diagL[r - c + (N - 1)] = 1;
		
		//Q[r] = { r, c };
		DFS(r + 1);

		flag_col[c] = 0;
		flag_diagR[r + c] = 0;
		flag_diagL[r - c + (N - 1)] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	DFS(0);
	cout << ans << "\n";
}
