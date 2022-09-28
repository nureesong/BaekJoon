/************************************/
// [10755] 컴퓨터실 (서브태스크1)
// Priority Queue
/************************************/

#include <iostream>
#include <queue>
using namespace std;

int M, N, Q;       // 컴퓨터, 학생번호: 1 ~ M
int A[300000 + 1]; // i번 학생의 위치
int B[100000];     // i번 친구의 입장 순서 -> 정렬 안 되어 있음
int maxB;          // 정환이의 친구 중 마지막 번호

// 비어있는 컴퓨터 구간 저장
struct STATUS {
	int s, e; 
	int l; // 구간 길이
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		if (a.l == b.l) return a.s > b.s;
		return a.l < b.l;
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void Input() {
	cin >> M >> N >> Q;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];

		// 아..A[i]는 오름차순으로 입력되는구나...
		// A[i]가 입력되면 그 전까지의 빈 구간 하나가 결정됨
		// 단, 두 학생 위치 차가 1보다 커야 빈 구간이 존재한다.
		// 빈 구간: A[i-1]+1 ~ A[i]-1
		if (A[i] - A[i-1] > 1) pq.push({ A[i-1]+1, A[i]-1, A[i] - A[i-1] -1 });
	}
	if (A[N] != M) pq.push({ A[N] + 1, M, M - A[N] });
	

	for (int i = 0; i < Q; i++) {
		cin >> B[i];
		maxB = (B[i] > maxB) ? B[i] : maxB;
	}
}


void Solve() {
	// N+1번 학생부터 마지막 순서 친구까지 순서대로 앉히기
	for (int i = N + 1; i <= maxB; i++) {
		STATUS pick = pq.top(); pq.pop();
		int s = pick.s;
		int e = pick.e;

		int m = (s + e) / 2;
		A[i] = m;

		// 그룹 쪼개서 다시 넣기
		if (s <= m - 1) pq.push({ s, m - 1, m - s });
		if (m + 1 <= e) pq.push({ m + 1, e, e - m });
	}

	// 쿼리 답 출력
	for (int i = 0; i < Q; i++) {
		cout << A[B[i]] << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
}
