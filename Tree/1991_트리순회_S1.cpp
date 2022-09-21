/***********************************************/
// [1991] 트리 순회 (실버1)
// 루트 = 부모, 왼쪽/오른쪽 자식을 중심으로 한 subtree 탐색
// 전위 순회(preorder traversal) : 루 - 왼 - 오
// 중위 순회(inorder traversal)  : 왼 - 루 - 오
// 후위 순회(postorder traversal): 왼 - 오 - 루
/***********************************************/
// 왼오 자식노드 구조체 배열에 저장
// 배열 인덱스로 접근하는 게 map에서 해시키로 접근하는 것보다 빠르다.
#if 0
#include <iostream>
using namespace std;

struct CHILD {
	int l, r;
}Tree[26 + 2]; // 'A' = 0번 노드로 인덱싱


void Preorder(int root) {
	if (root < 0) return;
	
	cout << (char)(root + 'A');
	Preorder(Tree[root].l);
	Preorder(Tree[root].r);
}

void Inorder(int root) {
	if (root < 0) return;
	
	Inorder(Tree[root].l);
	cout << (char)(root + 'A');
	Inorder(Tree[root].r);
}

void Postorder(int root) {
	if (root < 0) return;

	Postorder(Tree[root].l);
	Postorder(Tree[root].r);
	cout << (char)(root + 'A');
}

void Input() {
	int N;
	char root, left, right;
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> root >> left >> right;
		root -= 'A';
		Tree[root].l = (left == '.') ? -1 : left - 'A';
		Tree[root].r = (right == '.') ? -1 : right - 'A';
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	Preorder(0); // 루트 노드 = A(0번)
	cout << "\n";

	Inorder(0);
	cout << "\n";
	
	Postorder(0);
	cout << "\n";
}
#endif


// 왼,오 자식노드 map에 저장
#if 0
#include <iostream>
#include <unordered_map>
using namespace std;

struct CHILD {
	char l, r;
};
unordered_map<char, CHILD> ht; // key: 루트, value: 왼오 자식

void Preorder(char root) {
	cout << root;
	if (ht[root].l != '.') Preorder(ht[root].l);
	if (ht[root].r != '.') Preorder(ht[root].r);
}

void Inorder(char root) {
	if (ht[root].l != '.') Inorder(ht[root].l);
	cout << root;
	if (ht[root].r != '.') Inorder(ht[root].r);
}

void Postorder(char root) {
	if (ht[root].l != '.') Postorder(ht[root].l);
	if (ht[root].r != '.') Postorder(ht[root].r);
	cout << root;
}

void Input() {
	int N;
	char root, left, right;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> root >> left >> right;
		ht.insert({ root, {left, right} });
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	Preorder('A'); // 루트 노드 = A(0번)
	cout << "\n";

	Inorder('A');
	cout << "\n";

	Postorder('A');
	cout << "\n";
}
#endif
