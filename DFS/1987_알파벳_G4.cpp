/*********************************/
// [1987] 알파벳 (골드4)
// DFS - 372ms, 2024KB
/*********************************/

#include <iostream>
#include <unordered_set>
using namespace std;

int R, C;
char arr[20][20];
int vis[26];
unordered_set<char> s; // 입력받은 보드에 존재하는 서로다른 문자
int sz;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
int sol;


void Input() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> arr[i][j];
			s.insert(arr[i][j]);
		}
	}
	sz = s.size();
}

int DFS(int r, int c, int cnt) {
	if (cnt > sol) sol = cnt;

	if (sol == sz) return 1;

	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
		if (vis[arr[nr][nc] - 'A']) continue;

		vis[arr[nr][nc] - 'A'] = 1;
		if (DFS(nr, nc, cnt + 1)) return 1;
		vis[arr[nr][nc] - 'A'] = 0;
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	vis[arr[0][0] - 'A'] = 1;
	DFS(0, 0, 1);

	cout << sol << "\n";
}
