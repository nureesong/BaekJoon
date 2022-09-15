/***********************************/
// [17225] 세훈이의 선물가게 (실버1)
// Priority Queue 활용
// 주문시각 대신 "포장시작" 시간을 큐에 넣어줘야 한다!!
// 주문이 밀리면 주문받은 시각에 바로 포장을 시작할 수 없다.
// 포장 도중에 주문이 들어오고, 두 사람이 동시에 포장을 완료하면 
// 상민이가 먼저 가져가야 하므로 포장완료 시간 미리 계산해두기!!
/**********************************/
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
		if (a.t == b.t) return a.c > b.c; // B가 R보다 우선순위 높다.
		return a.t > b.t;                 // 시작시간이 작을수록 우선순위 높다.
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
		
		int B_end = 0, R_end = 0; 
		if (c == 'B') {
			for (int j = 0; j < m; j++) {
				pq.push({ max(B_end, t + A*j), c });
				B_end = max(B_end, t + A*j) + A;
			}
		}
		else {
			for (int j = 0; j < m; j++) {
				pq.push({ max(R_end, t + B*j), c });
				R_end = max(R_end, t + B*j) + B;
			}
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
