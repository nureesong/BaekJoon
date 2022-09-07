/**********************************/
// [15649] N과 M(1) - 실버3
// 1 ~ N 중 중복없이 M개 선택 => 순열
/**********************************/
#if 0
#include <iostream>
using namespace std;

int N, M;
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

	for (int n = 1; n <= N; n++) {
		if (vis[n]) continue;

		pick[cnt] = n;
		vis[n] = true;
		DFS(cnt + 1);
		vis[n] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	DFS(0);
}
#endif


/**********************************/
// [15650] N과 M(2) - 실버3
// 1 ~ N 중 중복없이 M개 선택, 오름차순 => 조합
/**********************************/
#if 0
#include <iostream>
using namespace std;

int N, M;
int pick[8 + 2];

// s ~ N 중 선택
void DFS(int s, int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << pick[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = s; i <= N; i++) {
		pick[cnt] = i;
		DFS(i + 1, cnt + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	DFS(1, 0);
}
#endif


/**********************************/
// [15651] N과 M(3) - 실버3
// 1~N 중 M개 선택, 중복 허용 => 중복순열
/**********************************/
#if 0
#include <iostream>
using namespace std;

int N, M;
int pick[8 + 2];

void DFS(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << pick[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int n = 1; n <= N; n++) {
		pick[cnt] = n;
		DFS(cnt + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	DFS(0);
}
#endif


/**********************************/
// [15652] N과 M(4) - 실버3
// 1~N 중 M개 선택, 중복 허용, 비내림차순 => 중복조합
/**********************************/
#if 0
#include <iostream>
using namespace std;

int N, M;
int pick[8 + 2];

void DFS(int s, int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << pick[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = s; i <= N; i++) {
		pick[cnt] = i;
		DFS(i, cnt + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	DFS(1, 0);
}
#endif
