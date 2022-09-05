#include <iostream>
#include <queue>
using namespace std;

int N, K;
int vis[100000 + 10];
struct DATA {
	int x, t;
};

int move(int n, int i) {
	if (i == 0) return n + 1;
	if (i == 1) return n - 1;
	return 2 * n;
}

int BFS() {
	queue<DATA> q;
	
	if (N == K) return 0;
	q.push({ N, 0 });
	vis[N] = 1;

	while (!q.empty()) {
		DATA cur = q.front();
		q.pop();

		for (int i = 0; i < 3; i++) {
			int nx = move(cur.x, i);

			if (nx == K) return cur.t + 1;
			if (nx < 0 || nx > 100000 || vis[nx]) continue;
			
			q.push({ nx, cur.t + 1 });
			vis[nx] = 1;
		}
	}

	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> K;
	cout << BFS() << "\n";
}
