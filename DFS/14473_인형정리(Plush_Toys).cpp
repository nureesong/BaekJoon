/*****************************************/
// [14473] 인형 정리 (플래티넘5에서 M 줄임)
// 백준 풀려면 M = 20이라서 DP 써야함
// DFS - 순열
/****************************************/

#include <iostream>
using namespace std;

int N, M;
// 인형, 선반 모두 1 부터 시작
// i번 인형의 j번 위치까지 누적개수
int psum[10 + 1][100000 + 1];

int flag[10 + 1]; // 어떤 인형 정리완료했는지(순열)
int sol; // 최소 이동횟수

void Input() {
	cin >> N >> M;
	int doll;
	for (int n = 1; n <= N; n++) {
		cin >> doll;
		psum[doll][n] = 1;
		for (int m = 1; m <= M; m++) {
			psum[m][n] += psum[m][n - 1];
		}
	}
}

// s번 선반부터 인형 놓기(s-1번 선반까지는 정리 완료된 상태)
void DFS(int s, int total_move) {
	// 가지치기
	if (total_move >= sol) return;

	if (s > N) { // 종료조건
		sol = (total_move < sol) ? total_move : sol;
		return;
	}

	// s번 선반에 어떤 인형 놓을지 선택
	for (int m = 1; m <= M; m++) {
		if (flag[m]) continue; // 이미 정리 완료된 인형 제외

		// 선반 구간의 끝 = s + m번 인형의 개수 - 1
		int e = s + psum[m][N] - 1;

		// 이동 횟수 = [s,e] 구간 내 m번이 아닌 인형 개수
		//          = 전체 m번 인형 수(구간길이) - 구간 내 m번 인형 개수
		int move = psum[m][N] - (psum[m][e] - psum[m][s - 1]);
		
		flag[m] = 1;
		DFS(e + 1, total_move + move);
		flag[m] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	sol = 0x7fffffff;
	DFS(1, 0);
	cout << sol << "\n";
}
