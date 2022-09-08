/**********************************/
// [10819] 차이를 최대로 - 실버2
// 순열
// ABCD 순서 선택 => |A - B| + |B - C|+ |C - D| 
// ABDC 순서 선택 => |A - B| + |B - D| +|D - C|
// |A - B|는 똑같고 뒷부분만 바뀐다.
/**********************************/
#if 0
#include <iostream>
#include <cmath>
using namespace std;

int N, S;
int arr[8 + 5];
int pick[8 + 5];
bool vis[8 + 5];
int maxsum;

void DFS(int cnt, int sumdiff) {
	if (cnt == N) {
		if (sumdiff > maxsum) maxsum = sumdiff;
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (vis[i]) continue;

		pick[cnt] = arr[i];
		vis[i] = true;

		int diff = (cnt > 0) ? abs(pick[cnt - 1] - pick[cnt]) : 0;
		DFS(cnt + 1, sumdiff + diff);
		vis[i] = false;
	}
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	DFS(0, 0);
	cout << maxsum << "\n";
}
#endif
