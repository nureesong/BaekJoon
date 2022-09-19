/********************************/
// [5917] Roadblock (G2)
// 양방향 = 무방향 그래프!!
// BFS + PQ
/********************************/

// 솔루션 - 인접리스트 사용
// 노드 간 가중치가 저장된 인접리스트의 위치를 보조 matrix에 저장
// list의 반복자(iterator)를 사용
// 다른 컨테이너(vector 등)에서는 iterator 사용금지!!!
#if 1
#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

struct STATUS {
	int v, sumdist;
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		return a.sumdist > b.sumdist;
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;

struct EDGE {
	int node, d;
};
list<EDGE> A[100 + 10]; // Adjacency list
list<EDGE>::iterator mat[100 + 10][100 + 10]; 
// mat[i][j]: i->j 간선 존재 시 해당 간선정보가 저장된 list node의 iterator
// mat[i][j]가 가리키는 곳에는 EDGE 구조체 {j, d_ij}가 있다.

int N, M;
int chk[100 + 10];
int path[100 + 10];


int BFS() {
	fill(chk, chk + 110, 0x7fffffff);
	pq = {}; // 초기화
	
	pq.push({ 1,0 });
	chk[1] = 0;

	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();
		if (cur.v == N) return chk[N];

		for (EDGE nbd : A[cur.v]) {
			if (cur.sumdist + nbd.d >= chk[nbd.node]) continue;

			chk[nbd.node] = cur.sumdist + nbd.d;
			pq.push({ nbd.node, chk[nbd.node] });
			path[nbd.node] = cur.v;
		}
	}
	return -1;
}

int Solve() {
	int min_original = BFS();
	int max = min_original;

	// 최단경로 역추적하면서 경로 하나만 2배로 바꿔서 BFS 다시 수행
	int dst = N;
	while (dst != 1) {
		int src = path[dst];

		mat[src][dst]->d *= 2;
		mat[dst][src]->d *= 2;
		int ret = BFS();
		if (ret > max) max = ret;
		
		mat[src][dst]->d /= 2; // 복원
		mat[dst][src]->d /= 2;

		dst = src;
	}

	return max - min_original;
}

void Input() {
	int u, v, w;

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> w;
		// insert(iterator, element) : iterator가 가리키는 부분의 앞에 원소 추가
		mat[u][v] = A[u].insert(A[u].begin(), { v,w });
		mat[v][u] = A[v].insert(A[v].begin(), { u,w }); // Undirected!!
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


// 인접행렬 사용
#if 0
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct STATUS {
	int node, d;
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		return a.d > b.d;
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;

int A[100 + 10][100 + 10];
int N, M;
int chk[100 + 10];
int path[100 + 10];


int BFS() {
	fill(chk, chk + 110, 0x7fffffff);
	pq = {};
	pq.push({ 1, 0 });
	chk[1] = 0;

	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();
		
		if (cur.node == N) return chk[N];

		for (int nbd = 1; nbd <= N; nbd++) {
			if (A[cur.node][nbd] == 0) continue;
			if (cur.d + A[cur.node][nbd] >= chk[nbd]) continue;
			
			chk[nbd] = cur.d + A[cur.node][nbd];
			pq.push({ nbd, chk[nbd] });
			path[nbd] = cur.node;
		}
	}
	return -1;
}

int Solve() {
	int min_original = BFS();
	int maxdist = min_original;

	// 최단경로 역추적하면서 한 경로만 2배로 바꿔서 BFS 다시 수행
	int dst = N;
	while (dst != 1) {
		int src = path[dst];

		A[src][dst] *= 2;
		A[dst][src] *= 2;
		int ret = BFS();
		if (ret > maxdist) maxdist = ret;

		A[src][dst] /= 2; // 복원
		A[dst][src] /= 2;

		dst = src;
	}

	return maxdist - min_original;
}

void Input() {
	int a, b, l;

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> l;
		A[a][b] = l;
		A[b][a] = l; // Undirected!!!
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
#endif
