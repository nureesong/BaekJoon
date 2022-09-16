/********************************/
// [10835] 카드게임 (골드5)
// 힌트: DFS + 가지치기 잘하기
// N <= 25 까지 성공
/********************************/
#include <iostream>
using namespace std;

int N;
int L[25 + 5]; // 1부터 시작
int R[25 + 5];
int psum[25 + 5]; // prefix sum for R
int maxscore = 0;

void DFS(int Ltop, int Rtop, int score) {
	// 종료조건
	if (Ltop > N || Rtop > N) {
		if (score > maxscore) maxscore = score;
		return;
	}

	// 가지치기
	if (score + psum[N] - psum[Rtop-1] < maxscore) return;

	// 3가지 경우의 수로 상태 발전
	if (L[Ltop] > R[Rtop]) DFS(Ltop, Rtop + 1, score + R[Rtop]);
	else { // L <= R일 때 L을 버려야 하므로 점수를 얻을 가능성이 생기므로 일종의 가지치기!!!
		DFS(Ltop + 1, Rtop, score);
		DFS(Ltop + 1, Rtop + 1, score);
	}
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> L[i];
	}
	for (int i = 1; i <= N; i++) {
		cin >> R[i];
		psum[i] = psum[i - 1] + R[i];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();

	DFS(1, 1, 0);
	cout << maxscore << "\n";
}
