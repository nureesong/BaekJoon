/***********************************/
// [11725] 트리의 부모 찾기 (실버2)
/***********************************/
// DFS: 48ms
#if 0
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> adjlist[100000 + 10];
int parent[100000 + 10]; // i번 노드의 부모노드 기록

void DFS(int n) {
	for (int nbd : adjlist[n]) {
		if (parent[nbd]) continue;

		parent[nbd] = n;
		DFS(nbd);
	}
}

void Input() {
	int a, b;
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		adjlist[a].push_back(b);
		adjlist[b].push_back(a);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	
	// 1번은 루트 노드라서 부모가 없지만 vis에 -1을 기록하여 방문처리
	parent[1] = -1; 
	DFS(1);
	
	for (int i = 2; i <= N; i++) {
		cout << parent[i] << "\n";
	}

}
#endif


// BFS: 44ms
#if 0
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
vector<int> adjlist[100000 + 10];
int parent[100000 + 10]; // i번 노드의 부모노드 기록
queue<int> q;

void BFS() {
	q.push(1);

	while (!q.empty()) {
		int cur = q.front(); q.pop();

		for (int nbd : adjlist[cur]) {
			if (parent[nbd]) continue;
			q.push(nbd);
			parent[nbd] = cur;
		}
	}
}

void Input() {
	int a, b;
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		adjlist[a].push_back(b);
		adjlist[b].push_back(a);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	BFS();

	for (int i = 2; i <= N; i++) {
		cout << parent[i] << "\n";
	}
}
#endif
