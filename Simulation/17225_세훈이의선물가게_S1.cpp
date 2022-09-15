/********************************/
// [17225] 세훈이의 선물가게 (실버1)
// Priority Queue 활용
/********************************/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct STATUS {
	int t;  // 포장 시작시간
	char c; // 색깔 (B: 상민, R: 지수)
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		if (a.t == b.t) a.c > b.c; // B가 R보다 우선순위 높다.
		return a.t > b.t; // 시작시간이 작을수록 우선순위 높다.
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void Solve() {
	vector<int> B; // 상민
	vector<int> R; // 지수
	int id = 1;    // 선물 번호
	
	while (!pq.empty()) {
		if (pq.top().c == 'B') B.push_back(id);
		else R.push_back(id);
		id++;
		pq.pop();
	}

	cout << B.size() << "\n";
	for (auto a : B) {
		cout << a << " ";
	}
	cout << "\n";

	cout << R.size() << "\n";
	for (auto a : R) {
		cout << a << " ";
	}
	cout << "\n";
}

void Input() {
	int t, m; char c;
	int A, B, N;
	cin >> A >> B >> N;

	for (int i = 0; i < N; i++) {
		cin >> t >> c >> m;

		for (int j = 0; j < m; j++) {
			pq.push({t, c});
			t = (c == 'B') ? t + A : t + B;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
}
