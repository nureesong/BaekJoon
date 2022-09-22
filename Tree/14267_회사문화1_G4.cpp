/*****************************/
// [14267] 회사 문화1 (골드4)
// 반례 주의!! 한 사람이 여러 번 칭찬 받는 경우
/*****************************/
// DFS (36ms, 10404KB)
#if 0
#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> adj[100000 + 2]; // 상사-부하들 관계
int W[100000 + 2];   // i번 사원이 받는 칭찬 총점

void Input() {
	cin >> N >> M;
	
	int p;
	for (int i = 1; i <= N; i++) {
		cin >> p;
		if (p > 0) adj[p].push_back(i);
	}

	int n, w;
	for (int i = 0; i < M; i++) {
		cin >> n >> w;
		W[n] += w; // 한 사람이 여러번 칭찬받는 경우!!
	}
}

void DFS(int cur) {
	for (int child : adj[cur]) {
		W[child] += W[cur];
		DFS(child);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	
	DFS(1);

	for (int i = 1; i <= N; i++) {
		cout << W[i] << " ";
	}
	cout << "\n";
}
#endif


// 상사 번호 < 부하 번호를 이용하여 배열의 맨 앞부터 칭찬점수 누적
// 28ms, 2800KB
#if 1
#include <iostream>
using namespace std;

int N, M;
int par[100000 + 2]; // i번 사원의 부모노드(직속상사)
int W[100000 + 2];   // i번 사원이 받는 칭찬 총점

void Input() {
	cin >> N >> M;

	int p;
	for (int i = 1; i <= N; i++) {
		cin >> par[i];
	}

	int n, w;
	for (int i = 0; i < M; i++) {
		cin >> n >> w;
		W[n] += w;
	}
}

void Solve() {
	cout << W[1] << " ";
	for (int i = 2; i <= N; i++) {
		W[i] += W[par[i]];
		cout << W[i] << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
}
#endif
