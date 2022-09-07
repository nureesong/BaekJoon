/**********************************/
// [14226] 이모티콘 - 골드4
/**********************************/
#if 0
#include <iostream>
#include <queue>
using namespace std;

int N;
int vis[1000 + 10][1000 + 10];
struct STATUS {
	int s, c; // 화면, 클립보드에 있는 이모티콘 개수
	int t;
};

int BFS() {
	queue<STATUS> q; 
	if (N == 1) return 0;

	q.push({ 1, 0, 0 });
	vis[1][0] = 1;

	while (!q.empty()) {
		STATUS cur = q.front();
		q.pop();

		// 3가지 연산 수행
		int op[3][2] = { {0, cur.s-cur.c},{cur.c, 0},{-1, 0} };

		for (int i = 0; i < 3; i++) {
			int ns = cur.s + op[i][0];
			int nc = cur.c + op[i][1];
			int nt = cur.t + 1;

			if (ns == N) return nt;
			
			if (ns < 0 || ns > 1000) continue;
			if (vis[ns][nc]) continue;

			q.push({ ns, nc, nt });
			vis[ns][nc] = 1;
		}

	}
	return -1;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	cout << BFS() << "\n";
}
#endif
