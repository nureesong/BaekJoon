#include <iostream>
#include <algorithm>
using namespace std;

int N;
struct Time {
	int s, e;
};
Time T[100000 + 10];

bool comp(const Time& a, const Time& b) {
	if (a.e == b.e) return a.s < b.s;
	return a.e < b.e;
}

int Solve() {
	// 회의 종료시간 오름차순, 시작시간 오름차순 정렬
	sort(T, T + N, comp);
	
	int cnt = 1;
	int end = T[0].e;

	for (int i = 1; i < N; i++) {
		if (T[i].s >= end) {
			cnt++;
			end = T[i].e;
		}
	}
	return cnt;
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> T[i].s >> T[i].e;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	cout << Solve() << "\n";
}
