/**********************************/
// [1389] 케빈 베이컨의 6단계 법칙
// Undirected Graph
/**********************************/
#if 0
#include <iostream>
#include <queue>
#include <list>
#include <cstring>

using namespace std;

int N, M;
list<int> adjlist[100 + 10];
int cnt[100 + 10];
struct STATUS {
	int n, t;
};

int BFS(int s) {
	memset(cnt + 1, 0xff, sizeof(cnt[0])*N);
	queue<STATUS> q;

	q.push({ s, 0 });
	cnt[s] = 0;

	while (!q.empty()) {
		STATUS data = q.front();
		q.pop();

		for (auto nbd : adjlist[data.n]) {
			if (cnt[nbd] != -1) continue;

			q.push({ nbd, data.t + 1 });
			cnt[nbd] = data.t + 1;
		}
	}
	
	int sum = 0;
	for (int j = 1; j <= N; j++) {
		sum += cnt[j];
	}
	return sum;
}

int Solve() {
	int min = BFS(1), min_id = 1;

	for (int i = 2; i <= N; i++) {
		int tmp = BFS(i);

		if (tmp < min) {
			min = tmp;
			min_id = i;
		}
	}
	return min_id;
}

void Input() {
	int a, b;

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adjlist[a].push_back(b);
		adjlist[b].push_back(a);
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

#endif
