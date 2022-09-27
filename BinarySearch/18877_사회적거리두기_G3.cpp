/************************************/
// [18877] 사회적 거리두기 (골드3)
// Parametric Search: 44ms
// 사회적 거리두기 parameter D를 찾기 위해 Binary Search(minD, maxD) 탐색
// 즉, D 이하로는 사회적 거리두기 가능하고, D 초과로는 불가능한 기준값 찾기.
// 파라미터 D에 대한 이분탐색 -> O(log 10^18) = O(60)
// 고정된 파라미터에 대한 사회적 거리두기 가능 여부 판단 -> O(M + N)
// 최대 O(60 * 20만) = 1200만 
/************************************/
// 잔디구간 정렬하기!!

#include <iostream>
#include <algorithm>
using namespace std;

int N, M;  // 소 마리수, 잔디구간 수

struct INTERVAL {
	long long s, e;
}I[100000]; // 잔디 구간 정보
bool comp(INTERVAL &a, INTERVAL &b) {
	return a.s < b.s;
}


void Input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> I[i].s >> I[i].e;
	}
}

int SetCows(long long d) {
	// 첫번째 소는 첫 구간 시작점에 세우기
	long long prev_cow = I[0].s;
	int idx = 0; // 구간 번호

	// 이전 소와 d 이상의 간격을 유지하며, 세울 수 있는 구간 찾기
	for (int i = 1; i < N; i++) {
		prev_cow += d; // 직전 소의 위치 + d
		
		// 가능한 구간 찾기
		while (idx < M && prev_cow > I[idx].e) idx++;
		if (idx == M) return 0; // 모든 구간 불가능
		
		// while문 탈출하면, prev_cow <= I[idx].e 인 상태
		// 만약 prev_cow가 [ I[idx].s, I[idx].e ]에 속하지 않으면,
		// 이전 소와의 간격이 d보다 크게 배치할 수밖에 없다.
		if (prev_cow < I[idx].s) prev_cow = I[idx].s;
	}
	return 1; // 모든 소를 d 이상의 간격으로 배치 성공
}

long long Solve() {
	// 탐색범위 안에 솔루션이 반드시 포함되도록 s,e를 초기화하자!!
	sort(I, I + M, comp);  // 잔디구간 정렬
	long long s = 1;
	long long e = I[M-1].e - I[0].s;
	long long sol = -1;

	while (s <= e) {
		long long m = (s + e) / 2;
		if (SetCows(m)) {
			sol = m;
			s = m + 1;
		}
		else e = m - 1;
	}
	return sol;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
