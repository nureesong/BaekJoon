/*******************************************/
// [3190] 뱀 (골드4)
// deque을 큐처럼 사용
// q.front() = 뱀의 꼬리
// 뱀의 머리가 과일을 먹으면 q.push(머리 위치)
/******************************************/

#include <iostream>
#include <deque>
using namespace std;

int N, K, L;
int map[100 + 10][100 + 10]; // (1, 1)부터 시작
int dir[10000 + 200];  // 방향: 0 = 그대로, +1: 90도 회전, -1: -90도 회전

struct Point {
	int r, c;
};

void Input() {
	int r, c, X;
	char C;

	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> r >> c;
		map[r][c] = -1; // 과일 표시
	}

	// 벽과 뱀은 2, 1로 체크
	map[1][1] = 1;
	for (int i = 0; i <= N + 1; i++) {
		map[0][i] = 2;
		map[N + 1][i] = 2;
		map[i][0] = 2;
		map[i][N + 1] = 2;
	}

	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> X >> C;
		if (C == 'L') dir[X] = -1;
		else dir[X] = 1;
	}
}

int Solve() {
	int dr[] = { 0,1,0,-1 };
	int dc[] = { 1,0,-1,0 };
	int t = 0;
	int d = 0, nr, nc;
	deque<Point> deq;

	deq.push_front({ 1,1 });

	while (!deq.empty()) {
		t++;
		nr = deq.front().r + dr[d];
		nc = deq.front().c + dc[d];

		deq.push_front({ nr, nc }); // new head
		if (map[nr][nc] > 0) return t;
		if (map[nr][nc] == 0) {  // no fruit
			map[deq.back().r][deq.back().c] = 0;  // move tail
			deq.pop_back();
		}
		
		map[nr][nc] = 1;  // new head
		d = (d + dir[t] + 4) % 4;  // direction check
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
