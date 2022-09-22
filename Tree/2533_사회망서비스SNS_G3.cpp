/**********************************/
// [2533] 사회망 서비스(SNS) (골드3)
/**********************************/
// 1) 입력되는 간선 정보는 부모-자식 순서가 아니다.
// 2) 부모-자식을 알 수 없는 양방향 간선이기 때문에 루트노드를 구할 수 없다.
// 3) 임의의 노드에서 출발하여 탐색하는 DFS를 만들자!
#if 0
#include <iostream>
#include <vector>
#include <algorithm> // min() 사용
using namespace std;

int N;
vector<int> adj[1000000 + 2];

int cnt[1000000 + 2][2];
// 노드 i를 루트로 하는 subtree에 대해 
// cnt[i][0] : 노드 i가 일반인일 때 필요한 최소 얼리어답터 수
// cnt[i][1] : 노드 i가 얼리어답터일 때 필요한 최소 얼리어답터 수

void Input() {
	cin >> N;
	int u, v;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

// 후위순회 형태
void DFS(int cur) {
	cnt[cur][1] = 1; // 초기화

	for (int c : adj[cur]) {
		// c가 cur의 부모노드이면 올라가는 방향이니까 탐색하면 안됨.
		if (cnt[c][1]) continue; 
		
		DFS(c); // 자식노드로 탐색

		// cur = 얼리 => 자식노드들은 얼리/일반 상관없음. 최솟값 선택
		cnt[cur][1] += min(cnt[c][0], cnt[c][1]);

		// cur = 일반 => 자식노드들은 반드시 얼리!!
		cnt[cur][0] += cnt[c][1];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	int root = 1; // 루트는 아무나 선택해도 된다.
	DFS(root);

	cout << min(cnt[root][0], cnt[root][1]) << "\n";
}
#endif
