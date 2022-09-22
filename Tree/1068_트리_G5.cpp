/*****************************/
// [1068] 트리 (골드5)
/*****************************/
// **반례 주의!!**
// 처음엔 leaf가 아니었지만 노드를 제거하면서 leaf가 되는 경우도 세야함!!
// 제거할 노드가 2번의 유일한 자식이므로 4번 제거시 2번이 새로운 leaf가 된다!
// 9
// -1 0 0 5 2 4 4 6 6
// 4
// => 정답: 2

// [솔루션1] DFS 함수에서 자식노드들의 leaf 개수 총합을 상위노드에 리턴
// 제거할 노드이면 0 리턴
// leaf 노드, rem이 유일한 자식노드면 1 리턴
#if 0
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> adj[50 + 2];
int rem; // 제거할 노드
int root;

void Input() {
	cin >> N;

	int par;
	for (int i = 0; i < N; i++) {
		cin >> par;
		if (par == -1) root = i;
		else adj[par].push_back(i);
	}
	cin >> rem;
}

// leaf 노드 개수 반환
int DFS(int cur) {
	if (cur == rem) return 0;       // 제거할 노드면 0 리턴
	if (!adj[cur].size()) return 1; // leaf 노드면 1 리턴
	
	int cnt_leaf = 0;
	for (int child : adj[cur]) {
		cnt_leaf += DFS(child);
	}

	return (cnt_leaf == 0) ? 1 : cnt_leaf;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << DFS(root) << "\n";
}

#endif

// [솔루션2] 인접리스트를 set으로 만들기 (노드 제거 편리)
// 부모->rem 으로 향하는 엣지를 사전에 제거하고 DFS를 돌리면,
// rem이 유일한 자식 노드였는지 고려할 필요없이 leaf만 세면 된다.
#if 0
#include <iostream>
#include <set>
using namespace std;

int N, root;
set<int> adj[50 + 2];
int rem;        // 제거할 노드

void Input() {
	int parent[50 + 2] = { 0, }; // 노드 i의 부모노드 기록

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> parent[i];
		if (parent[i] == -1) root = i;
		else adj[parent[i]].insert(i);
	}
	cin >> rem;

	// 제거할 노드가 루트노드가 아니면, 부모노드->rem 엣지를 제거
	if (parent[rem] != -1) adj[parent[rem]].erase(rem);
}

// 현재 노드를 루트로 하는 subtree에서 leaf 노드 개수 반환
int DFS(int cur) {
	if (cur == rem) return 0;       // 제거할 노드면 0 리턴
	if (!adj[cur].size()) return 1; // leaf 노드면 1 리턴

	int cnt_leaf = 0;
	for (int child : adj[cur]) {
		cnt_leaf += DFS(child);
	}
	return cnt_leaf;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << DFS(root) << "\n";
}

#endif

// [내 코드3] 초기 트리에서 leaf 노드 수를 구해놓고,
// 제거할 노드를 루트로 하는 subtree를 DFS로 탐색하면서 leaf 발견시 차감
// 단점 - 루트노드가 제거할 노드로 주어지면,
//        초기 leaf 계산 O(N) + DFS 탐색 O(N + N) => O(3N)
#if 0
#include <iostream>
#include <set>
using namespace std;

int N;
set<int> adj[50 + 2];
int parent[50 + 2];
int cnt_leaf;
int rem;

void Input() {
	cin >> N;

	int par;
	for (int i = 0; i < N; i++) {
		cin >> par;
		parent[i] = par;
		if (par != -1) adj[par].insert(i);
	}
	cin >> rem;

	if (parent[rem] != -1) adj[parent[rem]].erase(rem);
	// rem = root면 제거된 엣지는 없지만
	// DFS(rem)로 찾은 leaf 노드수 = 전체 leaf 노드수라서 다 차감되고 0이 남는다.

	cnt_leaf = N;
	for (int i = 0; i < N; i++) {
		if (adj[i].size()) cnt_leaf--;
	}
}

void DFS(int p) {
	if (!adj[p].size()) {
		cnt_leaf--;
		return;
	}

	for (int c : adj[p]) {
		DFS(c);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	DFS(rem);
	cout << cnt_leaf << "\n";
}

#endif

// [내 코드4] BFS 탐색 
// rem을 루트로 하는 subtree의 모든 노드들을 큐에 담으면서
// adjlist에서 아예 연결 관계를 제거한다. 최종적으로 남아있는 노드 중 
// 자식노드 0개이거나 rem가 유일한 자식노드인 경우에 leaf 노드 카운트
#if 0
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
vector<int> adj[50 + 2];
int rem;
queue<int> q;
int vis[50 + 2];

void Input() {
	cin >> N;

	int par;
	for (int i = 0; i < N; i++) {
		cin >> par;
		if (par != -1) adj[par].push_back(i);
	}
	cin >> rem;
}

int BFS() {
	q.push(rem);
	vis[rem] = 1;

	while (!q.empty()) {
		int cur = q.front(); q.pop();

		for (int child : adj[cur]) {
			q.push(child);
			vis[child] = 1;
		}
		adj[cur].clear();
	}

	int cnt_leaf = 0;
	for (int i = 0; i < N; i++) {
		if (vis[i]) continue;

		int sz = adj[i].size();
		if ((!sz) || (sz == 1 && adj[i][0] == rem)) cnt_leaf++;
	}

	return cnt_leaf;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << BFS() << "\n";
}

#endif


// [솔루션5] Bottom-up 방식, 배열 이용
// leaf부터 위로 올라가는 방향 순서대로 큐에 담기
#if 0
#include <iostream>
#include <queue>
using namespace std;

int N;
int parent[50 + 2];
int out[50 + 2];  // i번 노드에서 나가는 간선의 개수(자식노드 개수)
int rem; // 제거할 노드
int root;
int cnt_leaf[50 + 2]; // i번 노드
queue<int> q;

void Input() {
	cin >> N;
	int par;
	for (int i = 0; i < N; i++) {
		cin >> parent[i];
		if (parent[i] == -1) root = i;
		else {
			out[parent[i]]++; // i노드의 부모에서 i로 나가는 간선이 생긴 것!
		}
	}
	cin >> rem;
}

void Init_Leaf() {
	for (int i = 0; i < N; i++) {
		if (!out[i]) {
			q.push(i);
			cnt_leaf[i] = 1;
		}
	}
}

// 특정 순서로 노드를 처리하는 작업을 진행
// 큐에는 이미 결과(leaf개수)가 완성된 노드만 담는다.
// cnt_leaf[root] 가 최종 리턴
int Solve() {
	Init_Leaf(); // 초기 큐에는 leaf 노드를 전부 담기

	while (!q.empty()) {
		int cur = q.front(); q.pop();

		if (cur == rem) {
			cnt_leaf[cur] = 0;
			if (cur != root) {
				out[parent[cur]]--;
				if (out[parent[cur]] == 0) q.push(parent[cur]);
			}
			continue;
		}

		// 원래는 leaf 아닌데 rem 제거되면서 leaf 되는 경우
		if (cnt_leaf[cur] == 0) cnt_leaf[cur] = 1;

		// root는 영향을 줄 부모가 없다.
		if (cur == root) continue;

		// 부모에게 leaf 노드 수 전달
		cnt_leaf[parent[cur]] += cnt_leaf[cur];
		out[parent[cur]]--;  // 전달 완료한 자식 체크

		// 모든 자식에게 전달받았으면 0이므로 leaf 정보 완성
		if (out[parent[cur]] == 0) q.push(parent[cur]); 
	}

	return cnt_leaf[root];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}

#endif
