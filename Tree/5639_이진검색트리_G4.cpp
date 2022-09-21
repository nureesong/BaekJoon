/***************************************************************/
// [5639] 이진 검색 트리 BST (골드4)
// 전위순회로 입력되므로, 루트 - {왼쪽 subtree} - {오른쪽 subtree}
// 루트 노드보다 작은 값들은 전부 왼쪽 subtree에 속하고,
// 큰 값이 나오면 그때부터 오른쪽 subtree 시작!
/***************************************************************/
// [시간초과] 전위순회로 입력되는 정보로 BST 완성 후 후위순회로 출력
// 매 입력노드마다 루트노드부터 계속 비교하다보니,
// 만약에 1 2 3 4 ... 계속 증가하는 순서로 입력되면
// 루트노드의 오른쪽 자식노드만 계속 추가되면서 거의 O(N^2)이다.
#if 0
#include <iostream>
#include <unordered_map>
using namespace std;

struct CHILD {
	int l, r;  // 0은 빈 노드
};
unordered_map<int, CHILD> bst;
int root;


// [] 연산자 대신 iter로 바꿔도 시간초과...
void Add_Node(int n) {
	int cur = root;
	auto iter = bst.find(root);

	while (1) {
		if (n < cur) {
			if (!(iter->second.l)) {
				iter->second.l = n;
				bst.insert({ n, {0,0} });
				return;
			}
			cur = iter->second.l;
			iter = bst.find(cur);
		}
		else {
			if (!iter->second.r) {
				iter->second.r = n;
				bst.insert({ n, {0,0} });
				return;
			}
			cur = iter->second.r;
			iter = bst.find(cur);
		}
	}
}

void Input() {
	cin >> root;  // 전위순회니까 첫 입력값은 트리 전체의 루트노드
	bst.insert({ root, {0,0} });
	
	// 몇 개 입력받는지 모를 때!!
	int n;
	while (cin >> n) {
		Add_Node(n);
	}
}

void Postorder(int n) {
	auto iter = bst.find(n);

	if (iter->second.l) Postorder(iter->second.l);
	if (iter->second.r) Postorder(iter->second.r);
	cout << n << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Postorder(root);
}
#endif


// [솔루션] 전위순회를 재귀적으로 해석하며 트리 생성 (24ms)
//   왼쪽 subtree 맨앞(루트) < 루트노드
// 오른쪽 subtree 맨앞(루트) > 루트노드
#if 0
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct NODE {
	int l, r;
};
unordered_map<int, NODE> bst;
vector<int> v;
int root;

void Input() {
	int n;
	while (cin >> n) v.push_back(n);
}

// cur 노드를 루트로 하는 subtree 구성 (s~e번째 요소 내에서)
void Subtree(int cur, int s, int e) {
	if (s > e) return;

	// 왼,오 subtree 경계선 찾기
	int m;
	for (m = s; m <= e; m++) {
		if (v[m] > cur) break;
	}
	// v[s] ~ v[m-1] : cur의 왼쪽 subtree를 구성한다.
	// v[s] = 왼쪽 subtree의 루트 노드 = cur의 왼쪽 자식노드
	// 만약, v[s]~v[e]가 전부 cur보다 크면, m = s으로 for문 중단
	// 즉, cur는 왼쪽 자식노드가 존재하지 않는다.
	if (m > s) {
		bst[cur].l = v[s];
		bst.insert({ v[s], { 0,0 } }); // 키 생성
		Subtree(v[s], s + 1, m - 1);
	}

	// v[m] ~ v[e] : cur의 오른쪽 subtree를 구성한다.
	// v[m] = 오른쪽 subtree의 루트 노드 = cur의 오른쪽 자식노드
	// 만약, v[s]~v[e]가 전부 cur보다 작으면, m = e+1로 for문 종료
	// 즉, cur는 오른쪽 자식노드가 존재하지 않는다.
	if (m <= e) {
		bst[cur].r = v[m];
		bst.insert({ v[m], { 0,0 } }); // 키 생성
		Subtree(v[m], m + 1, e);
	}
}

void Postorder(int cur) {
	if (bst[cur].l) Postorder(bst[cur].l);
	if (bst[cur].r) Postorder(bst[cur].r);
	cout << cur << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	root = v[0];
	bst.insert({ root, {0,0} });

	Subtree(root, 1, v.size()-1);

	Postorder(root);
}
#endif


// [솔루션] 트리 해석과 동시에 후위순회로 출력 (32ms)
#if 0
#include <iostream>
#include <vector>
using namespace std;

struct NODE {
	int l, r;
};
vector<int> v;

// s~e번째 요소에 대해 subtree 해석 및 출력
void Subtree(int s, int e) {
	if (s > e) return;

	// 왼,오 subtree 경계선 찾기
	int cur = v[s]; // 현재 root
	int m;
	for (m = s+1; m <= e; m++) {
		if (v[m] > cur) break;
	}
	
	// Postorder Traversal
	Subtree(s + 1, m - 1); // 왼쪽 subtree
	Subtree(m, e);         // 오른쪽 subtree
	cout << cur << "\n";   // 현재 root
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	while (cin >> n) v.push_back(n);

	Subtree(0, v.size() - 1);
}
#endif
