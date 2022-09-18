/********************************/
// [10835] 카드게임 (골드5)
// DFS + 가지치기. 서브태스크2 까지 성공 (N <= 25)
// 87 ms: 현재 남아있는 오른쪽 카드를 모두 더해도 maxscore보다 작으면 가지치기
//  2 ms: BFS에서 많이 사용하던 특정 상태에 대한 최고경험을 바탕으로 한 가지치기 추가
/********************************/
#include <iostream>
using namespace std;

int N;
int L[25 + 5]; // 1부터 시작
int R[25 + 5];
//int psum[25 + 5]; // prefix sum for R
int maxscore = 0;

// chk[l]][r] : 왼쪽카드 l번째, 오른쪽카드 r번째까지 진행된 상황에서 최고 점수
int chk[25 + 5][25 + 5]; // -1로 초기화


void DFS(int Ltop, int Rtop, int score) 
	// 가지치기 (솔루션): 기존 최고점수보다 높지 않으면 굳이 발전시킬 필요없음
	if (score <= chk[Ltop][Rtop]) return;
        chk[Ltop][Rtop] = score;

	// 가지치기 (기존)
	//if (score + psum[N] - psum[Rtop-1] < maxscore) return;
	
	// 종료조건
	if (Ltop > N || Rtop > N) {
		if (score > maxscore) maxscore = score;
		return;
	}
	
	// 3가지 경우의 수로 상태 발전
	if (L[Ltop] > R[Rtop]) DFS(Ltop, Rtop + 1, score + R[Rtop]);
	else { // L <= R일 때 L의 카드를 버려야 점수를 얻을 가능성이 생긴다.
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
		//psum[i] = psum[i - 1] + R[i];
	}
	fill(&chk[1][1], &chk[25][25 + 1], -1);
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
