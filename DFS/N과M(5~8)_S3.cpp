/**********************************/
// [15654] N과 M(5) - 실버3
// N개의 자연수 중 중복없이 M개 선택 => 순열
// 단, 사전식 오름차순으로 출력하기
/**********************************/
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[8 + 2];
int pick[8 + 2];
bool vis[8 + 2];

void DFS(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << pick[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 0; i < N; i++) {
		if (vis[i]) continue;

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


/**********************************/
// [15655] N과 M(6) - 실버3
// N개의 자연수 중 중복없이 M개 선택, 오름차순 => 조합
// 단, 사전식 오름차순으로 출력하기
/**********************************/
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[8 + 2]; // 0번째부터 시작
int pick[8 + 2];

void DFS(int s, int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << pick[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = s; i < N; i++) {
		pick[cnt] = arr[i];
		DFS(i + 1, cnt + 1);
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
	DFS(0, 0);
}
#endif


/**********************************/
// [15656] N과 M(7) - 실버3
// N개의 자연수 중 M개 선택, 중복허용 => 중복순열
// 단, 사전식 오름차순으로 출력하기
/**********************************/
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[8 + 2]; // 0번째부터 시작
int pick[8 + 2];

void DFS(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << pick[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 0; i < N; i++) {
		pick[cnt] = arr[i];
		DFS(cnt + 1);
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


/**********************************/
// [15657] N과 M(8) - 실버3
// N개의 자연수 중 M개 선택, 중복허용, 비내림차순 => 중복조합
// 단, 사전식 오름차순으로 출력하기
/**********************************/
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[8 + 2]; // 0번째부터 시작
int pick[8 + 2];

void DFS(int cnt, int s) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << pick[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = s; i < N; i++) {
		pick[cnt] = arr[i];
		DFS(cnt + 1, i);
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
	DFS(0, 0);
}
#endif
