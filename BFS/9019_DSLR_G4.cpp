#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int T, A, B;
int vis[10000 + 10];  // 방문한 숫자 표시
struct DATA {
	int n;     // 레지스터에 저장하는 십진수
	string s;  // D, S, L, R이 나열된 명령어
};


int apply(int n, char c) {
	if (c == 'D') return (2 * n) % 10000;
	if (c == 'S') {
		if (n == 0) return 9999;
		return n - 1;
	}
	if (c == 'L') return (n % 1000) * 10 + n / 1000;
	if (c == 'R') return (n % 10) * 1000 + n / 10;
	return -1;
}


string BFS() {
	// Initialize
	queue<DATA> q;
	fill (vis, vis + 10000, 0);

	q.push({ A, "" });
	vis[A] = 1;

	while (!q.empty()) {
		DATA cur = q.front();
		q.pop();

		for (char c : "DSLR") {
			if (c == '\0') continue;  // 마지막 널문자까지 for문 돌지 않도록 주의!

			int next = apply(cur.n, c);
			string cmd = cur.s + c;  // 입력된 명령어를 현재 경로에 덧붙이기

			if (next == B) return cmd;
			if (vis[next]) continue;

			q.push({ next, cmd });
			vis[next] = 1;
		}
	}
	return "Err";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);

	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> A >> B;
		cout << BFS() << "\n";
	}
}
