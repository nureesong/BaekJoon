/**********************************************/
// [5926] 암소 라인업 (골드3)
// 슬라이딩 윈도우 - O(2N)
// 품종 ID와 x좌표 최댓값이 10^9이므로 배열 사용X
// 소 품종별 마리수 카운트 -> unordered_map
/*********************************************/

#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int N;
struct DATA {
	int x;
	int id;
}C[50000 + 2]; // x 오름차순으로 정렬하기
bool comp(DATA &a, DATA &b) {
	return a.x < b.x;
}

// 소가 5만마리니까 ID는 최대 5만 가지
unordered_map<int, int> cnt_ID; // 품종ID - 마릿수


void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> C[i].x >> C[i].id;
		auto it = cnt_ID.find(C[i].id);
		if (it == cnt_ID.end()) cnt_ID.insert({ C[i].id, 0 });
	}
	sort(C, C + N, comp);
}

int Solve() {
	int n_uniq = cnt_ID.size();
	int minrange = C[N - 1].x - C[0].x;
	int cnt = 0;

	int e = 0;
	for (int s = 0; s < N; s++) {
		while (e < N && cnt < n_uniq) {
			cnt_ID[C[e].id]++;
			if (cnt_ID[C[e].id] == 1) cnt++;
			e++;
		}
		// e를 제일 끝까지 늘려봤지만 모든 품종을 포함하지 못한다.
		// s를 늘려봤자 소가 계속 제거되며 cnt도 감소하므로 의미X. 탐색 중단
		if (e == N && cnt < n_uniq) break;

		int cur = C[e - 1].x - C[s].x;
		minrange = (cur < minrange) ? cur : minrange;

		// s번 소부터 시작하는 구간은 다 구함
		// s+1번 소부터 시작하기 위해 s번 소를 제거
		cnt_ID[C[s].id]--;
		if (cnt_ID[C[s].id] == 0) cnt--;
	}
	return minrange;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
