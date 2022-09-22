/**********************************/
// [2250] 트리의 높이와 너비 (골드2)
/**********************************/
// 4ms
// 이진트리를 중위순회로 읽은 순서가 곧 열 번호 오름차순이다.
// 중위순회 하면서 level도 같이 파라미터로 입력하여 행,열 번호를 한번에 얻는다.
#if 0
#include <iostream>
using namespace std;

int N, root;
struct NODE {
	int l, r;
};
NODE adj[10000 + 2];
int parent[10000 + 2]; // 루트노드 찾기 위해 i번 노드의 부모 기록

int col = 1; // 열번호 카운트
NODE Breadth[10000 + 2];  // 각 레벨별 제일 왼쪽, 오른쪽 열 번호 저장


void Input() {
	cin >> N;

	int p, l, r;
	for (int i = 0; i < N; i++) {
		cin >> p >> l >> r;
		parent[l] = p;
		parent[r] = p;
		adj[p] = { l,r };
	}

	// root 노드 탐색
	for (int i = 1; i <= N; i++) {
		if (parent[i] == 0) {
			root = i;
			return;
		}
	}
}


// 중위순회 방식 변형
// 현재 노드의 왼쪽 자식노드 개수의 열번호가 먼저 확정된다.
void Inorder(int cur, int level) {
	// Left subtree
	if (adj[cur].l > 0) Inorder(adj[cur].l, level + 1);
	
	// Current Root
	if (Breadth[level].l == 0) { // 해당 레벨에 아무 노드도 없는 상태
		Breadth[level] = { col, col }; // 노드 1개니까 좌우 열번호 모두 한 가지
	}
	else { // 해당 레벨에 노드 1개 이상 존재
		// 열번호 오름차순으로 노드가 탐색되므로 어차피 현재 col이 기존 r보다 크다.
		Breadth[level].r = col;
	}
	col++;
	
	// Right subtree
	if (adj[cur].r > 0) Inorder(adj[cur].r, level + 1);
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	Inorder(root, 1);

	// 최대 너비와 해당 레벨 찾기
	int width;
	int sol = 0, sol_level = -1;
	for (int l = 1; l <= N; l++) {
		// 현재 트리의 최대깊이를 넘어가면 Breadth에는 0,0이 기록되어 있다.
		if (Breadth[l].l == 0) break; 
		
		width = Breadth[l].r - Breadth[l].l + 1;
		if (width > sol) {
			sol = width;
			sol_level = l;
		}
	}

	cout << sol_level << " " << sol << "\n";
}

#endif
