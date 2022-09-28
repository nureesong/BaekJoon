/*******************************************/
// [2805] 나무 자르기 (실버2)
// Parametric Search
// O(N * log2_10억) = O(N * 30)
// 배열 인덱스가 아닌 숫자의 범위로 이진 탐색 (Linear 패턴인 경우)
// 잘린 나무의 합을 구해서 M과 비교할거면 long long으로 선언!!
// 나무 잘릴 때마다 M에서 뺄 거면 int로도 가능
/*******************************************/

#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int tree[1000000 + 10];
int maxH = 0;

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> tree[i];
		if (tree[i] > maxH) maxH = tree[i];
	}
}

int isPossible(int m) { // 잘린 나무 길이를 M에서 차감하는 방식
	int sum = M;
	for (int i = 0; i < N; i++) {
		if (tree[i] <= m) continue;
		
		sum -= (tree[i] - m);
		if (sum <= 0) return 1;
	}
	return 0;
}

int BS(int s, int e) {
	int ub = -1;
	
	while (s <= e) {
		int m = (s + e) / 2;
		if (isPossible(m)) {
			ub = m;
			s = m + 1;
		}
		else e = m - 1;
	}
	return ub;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	cout << BS(0, maxH);
}
