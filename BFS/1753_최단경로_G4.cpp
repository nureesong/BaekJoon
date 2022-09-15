/********************************/
// [1753] 최단경로 (골드4)
// Priority Queue 기반 BFS
/********************************/
#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

int V, E, S;
struct STATUS {
	int node, w;
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		return a.w > b.w;
	}
};
list<STATUS> A[20000 + 10]; // 인접리스트
priority_queue<STATUS, vector<STATUS>, COMP> pq;

int chk[20000 + 10]; // 시작노드부터 각 노드까지 최단거리 기록


void BFS() {
	pq.push({ S, 0 });
	chk[S] = 0;
	
	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();

		for (STATUS nbd : A[cur.node]) {
			if (cur.w + nbd.w >= chk[nbd.node]) continue;

			chk[nbd.node] = cur.w + nbd.w;
			pq.push({ nbd.node, chk[nbd.node] });
			//cout << "[Push] " << cur.node << " " << nbd.node << " " << chk[nbd.node] << "\n";
		}

	}
}


void Input() {
	int u, v, w;
	fill(chk + 1, chk + 20000 + 1, 0x7fffffff);
	
	cin >> V >> E >> S;
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> w;
		A[u].push_back({ v, w });
	}	
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	BFS();

	for (int i = 1; i <= V; i++) {
		if (chk[i] < 0x7fffffff) cout << chk[i] << "\n";
		else cout << "INF\n";
	}
}
