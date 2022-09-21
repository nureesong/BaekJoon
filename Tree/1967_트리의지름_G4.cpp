/************************************************************/
// [1967] 트리의 지름 (골드4)
// *주의* 이진 트리 아님!!
// 트리의 지름 = 두 리프노드 사이의 거리 중 최대값
//
// [Bottom-up 방식]
// 리프노드 -> 리프노드 모든 경로 체크: O(|V|^2) -> 비효율
//
// [Top-down 방식]
// 루트노드 -> 각각의 리프노드 까지의 거리합 계산: O(|V|+|E|)
// 자식노드 2개 이상이면, 현재노드가 두 리프노드의 공통부모이므로
// 두 리프노드 간 경로길이 중 최대 2개를 선택하여 트리의 지름 갱신
// 그리고 자식노드 중 거리합의 최댓값을 상위노드에 리턴한다.
/************************************************************/
// 루트~자식노드 거리를 벡터에 저장 후 partial_sort로 최대 2개 추출 (4ms)
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct EDGE {
	int n, w; // 자식노드, 가중치(1~100)
};
vector<EDGE> adj[10000 + 10]; // 노드번호 1~N (루트 = 1)

int sol;  // 두 노드 사이 최대 경로길이

void Input() {
	int N;
	cin >> N;

	int p, c, w;
	for (int i = 0; i < N - 1; i++) {
		cin >> p >> c >> w;
		adj[p].push_back({ c,w });
	}
}

// sumdist: 1번 노드 ~ r번 노드까지 거리 총합
int DFS(int r, int sumdist) {
	vector<int> dist = { sumdist };

	for (EDGE child : adj[r]) {
		dist.push_back(DFS(child.n, sumdist + child.w));
	}

	int tmp;
	if (dist.size() >= 2) {
		partial_sort(dist.begin(), dist.begin() + 2, dist.end(), greater<int>());
		tmp = dist[0] + dist[1] - 2 * sumdist;
		sol = (tmp > sol) ? tmp : sol;
	}
	
	return dist[0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	DFS(1, 0);
	cout << sol << "\n";
}
#endif


// 최댓값 2개만 배열에 저장 (4ms)
#if 0
#include <iostream>
#include <vector>
using namespace std;

struct EDGE {
	int n, w;
};
vector<EDGE> adj[10000 + 2];

int sol; // 트리의 지름

void Input() {
	int N;
	cin >> N;

	int p, c, w;
	for (int i = 0; i < N - 1; i++) {
		cin >> p >> c >> w;
		adj[p].push_back({ c,w });
	}
}

// sumdist = 1번~cur 노드까지 거리 총합
// cur 노드를 공통부모로 갖는 두 리프노드 간 거리 최댓값을 갱신 후
// 1번~cur의 자식노드들 까지의 거리 중 최댓값을 상위노드에 리턴
int DFS(int cur, int sumdist) {
	int max[2] = { sumdist, 0 }; // 자식노드들 중 최댓값 2개 저장
	// cur = 리프노드 이면 sumdist를 그대로 리턴하기 위해 0번째에 미리 입력

	for (EDGE child : adj[cur]) {
		int ret = DFS(child.n, sumdist + child.w);

		if (ret > max[1]) {
			if (ret > max[0]) {
				max[1] = max[0]; // 1위였던 값 2위로 밀려남
				max[0] = ret;
			}
			else max[1] = ret; // 2위에 안착
		}
	}

	// 최댓값 2개를 기반으로 리프노드1~cur~리프노드2 거리를 계산한다.
	// cur~리프노드 거리 = 1~리프노드 거리 - 1~cur까지 거리(sumdist)
	int tmp = max[0] + max[1] - 2 * sumdist;
	sol = (tmp > sol) ? tmp : sol;

	return max[0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	DFS(1, 0);
	cout << sol << "\n";
	return 0;
}
#endif
