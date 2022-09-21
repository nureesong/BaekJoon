/***********************************/
// [15681] 트리와 쿼리 (골드5)
/***********************************/
// 트리중 한 노드의 subtree로부터 정보를 얻어야할 때가 있다.
// 하위노드의 정보를 종합해서 상위노드를 만드는 경우!
// Postorder 방식 사용: 모든 자식노드 순회 후 상위노드에 정보 합산
#if 0
#include <iostream>
#include <vector>
using namespace std;

int N, R, Q;
vector<int> adj[100000 + 10]; // 1번 노드부터 시작
int D[100000 + 10];           // 노드의 차수(degree)

void Input() {
	cin >> N >> R >> Q;
	
	int u, v;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

// Postorder인 이유: 모든 자식노드 순회 후 루트노드에 정보 합산
int DFS(int r) {
	D[r] = 1;

	for (int nbd : adj[r]) {
		if (D[nbd]) continue; // 차수에 값이 있으면 이미 방문한 노드
		
		// nbd : 노드 r의 모든 자식 노드
		// 다시 nbd를 루트로 하는 subtree의 정점 개수 탐색
		D[r] += DFS(nbd);  // 하위노드 정보를 루트 노드에 합산
	}
	return D[r];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	
	DFS(R);

	int q;
	for (int i = 0; i < Q; i++) {
		cin >> q;
		cout << D[q] << "\n";
	}
}
#endif
