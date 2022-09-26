/*********************************************************/
// [13325] 이진트리 (골드3)
//
// 루트에서 리프까지 쭉 내려간 후, 
// 백트래킹할 때 좌우 통일한 값을 상위노드에 전달하며
// 트리 전체 가중치 합을 누적한다.
//
// 포화이진트리의 노드번호
// n번 노드의 왼쪽자식 = 2*n, 오른쪽 자식 = 2*n + 1
//         1
//     2       3
//   4   5   6    7
//
// 노드 200만개가 넘으므로 인접리스트로 표현 불가
// 주어진 엣지를 2개씩 묶어서 보면 노드1의 왼오, 노드2의 왼오, ...
/*********************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_K (20)
#define MAX_N (1 << (MAX_K + 1)) // 2^21 = 약 200만

int K;      // 포화이진트리 높이
int leaf_s; // 리프노드 중 제일 왼쪽 노드번호(포화이진트리니까 2^K)
int N;      // 트리 전체 노드 개수 + 1  = 2^(K+1)
long long weightsum; // 트리 전체 가중치 총합

struct NODE {
	int w_l, w_r; // 좌우 가중치
}node[MAX_N];


void Input() {
	cin >> K;
	
	leaf_s = (1 << K);  // 2^K
	N = (1 << (K + 1)); // 2^(K+1)

	// 자식노드가 존재하는 노드 번호: 1 ~ 2^K-1
	for (int n = 1; n < leaf_s; n++) {
		cin >> node[n].w_l >> node[n].w_r;
	}
}


// 리프 ~ n번 노드까지 좌우 통일한 후 거리 리턴
int DFS(int n) {
	// 마지막 레벨(리프노드) 도달
	if (n >= leaf_s) return 0;

	int left = DFS(2 * n) + node[n].w_l;      // 왼쪽자식
	int right = DFS(2 * n + 1) + node[n].w_r; // 오른쪽자식

	// 좌우 중 큰 값으로 통일하므로 max(l,r)을 리턴하고
	// 트리 전체 가중치에 해당 노드의 좌우 간선 + 증가량 누적한다.
	weightsum += node[n].w_l + node[n].w_r + abs(left - right);
	return max(left, right); 
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	DFS(1);
	cout << weightsum << "\n";
}
