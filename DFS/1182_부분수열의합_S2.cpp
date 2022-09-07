/**********************************/
// [1182] 부분수열의 합 - 실버2
/**********************************/

#include <iostream>
#include <algorithm>
using namespace std;

int N, S;
int arr[20 + 5];
int ans;

// sum의 초기값이 0이라서 S=0으로 주어지면 바로 리턴되는 걸 방지하기 위해 cnt 추가
void DFS(int s, int sum, int cnt) {
	if (cnt > 0 && sum == S) {
		ans++;
		//return; 여기서 리턴하면 안 된다!
		// 이미 S를 완성했어도 0인 요소가 있으면 0까지 더한 것도 
		// 새로운 경우의 수이므로 마지막 요소까지 탐색해야 함.
		// ex) 수열: [-2 -1 -1 0], S = -2
		// 경우의 수: {-2}, {-2, 0}, {-1, -1}, {-1, -1, 0}
	}

	if (s > N || cnt > N) return; // 종료조건
	
	for (int i = s; i <= N; i++) {
		DFS(i + 1, sum + arr[i], cnt + 1);
	}
}

void Input() {
	cin >> N >> S;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	sort(arr + 1, arr + N + 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	DFS(1, 0, 0);
	cout << ans << "\n";
}
