/**********************************/
// [15663] N과 M(9) - 실버2
// N개의 자연수 중 M개 선택, 중복허용 => 중복순열
// 단, N개의 자연수에 중복값 존재 -> 중복되는 수열은 제외
// 솔루션 이해 안 감..ㅠㅠ
/**********************************/
#if 1
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, M;
int arr[8 + 2];
int pick[8 + 2];
bool vis[8 + 2];

void DFS(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) cout << pick[i] << " ";
		cout << "\n";
		return;
	}

	// prev_num에 직전에 골랐던 수를 저장합니다
	// 전역변수로 선언하지 않고 계속 초기화가 되도록 해주는 이유는 
	// 맨 처음에 고르는 수는 직전 값과 관계없이 고르기 위함입니다
	int prev_num = 0;

	for (int i = 0; i < N; i++) {
		if (vis[i]) continue;
		// 바로 직전에 만든 수열과 중복이므로 패스
		//if (pick[cnt] == arr[i]) continue; // 틀림...
		if (arr[i] == prev_num) continue;

		// 따로 저장해야 된대..왜??
		// 함수의 재귀 호출이 출력으로 인해 끝나게 되면
		// for문 안에서 다음 수를 고르게 되는데 그 때
		// prev_num에 저장된 수를 고르지 않기 위함입니다
		prev_num = arr[i];

		pick[cnt] = arr[i];
		vis[i] = true;
		DFS(cnt + 1);
		vis[i] = false;
	}
}

 
void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + N);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	DFS(0);
}
#endif
