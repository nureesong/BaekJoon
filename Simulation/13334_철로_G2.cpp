/********************************/
// [13334] 철로 (골드2)
// Greedy Algorithm + Priority Queue
// 구간 끝지점 기준 오름차순 정렬
// 구간 시작지점이 작을수록 우선순위 높다.
// ==== 솔루션 아이디어 ====
// i번 사람의 끝지점(e)을 기준으로 e-d ~ e 구간에 철로를 설치했을 때, 
// 해당영역에 포함되는 사람의 수를 계산해야 하는데, 
// PQ에 0~i까지를 담는 과정을 순서대로 진행한 상태에서 
// PQ에서 구간 시작지점이 철로 시작(e-d)보다 작은 것들을 모두 꺼내면 
// 결국 PQ에는 e-d ~ e 사이에 포함되는 구간들만 남는다.
/********************************/
#if 1
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, d;
struct STATUS {
	int s, e;
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		return a.s > b.s; // 시작지점이 작을수록 최우선
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;

STATUS arr[100000 + 10]; // 각 사람별 집, 사무실 위치

bool cmp(STATUS &a, STATUS &b) {
	return a.e < b.e;
}

int Solve() {
	sort(arr, arr + N, cmp); // 구간 끝 기준 오름차순 정렬

	int maxcnt = 0;
	for (int i = 0; i < N; i++) {
		// i번째 구간 끝부터 앞으로 d만큼 철로를 만들었을 때
		// 시작 구간이 포함되지 않는 요소들을 전부 pop한다.
		pq.push(arr[i]);
		while (!pq.empty() && pq.top().s < arr[i].e - d) {
			pq.pop();
		}

		if (pq.size() > maxcnt) maxcnt = pq.size();
	}
	return maxcnt;
}

void Input() {
	cin >> N;
	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		if (s > e) arr[i] = { e,s };
		else arr[i] = { s,e };
	}
	cin >> d;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	cout << Solve() << "\n";
}
#endif
