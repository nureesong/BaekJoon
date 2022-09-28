/************************************/
// [11559] 뿌요뿌요 (골드4)
// FloodFill
/************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

char arr[12][6];
int vis[12][6];
struct STATUS {
	int r, c;
};
queue<STATUS> q;
vector<STATUS> rem[18]; // 터트릴 뿌요 그룹별 위치 저장 (72칸이므로 최대 18그룹)
queue<char> remain; // 하나의 열에서 터트리고 남은 뿌요들 순서대로 저장


void Input() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> arr[i][j];
		}
	}
}

int FloodFill(int r, int c, int group) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };
	
	q.push({ r,c });
	vis[r][c] = 1;
	rem[group].push_back({ r,c });
	char color = arr[r][c];
	
	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];
			if (nr < 0 || nr > 11 || nc < 0 || nc > 5) continue;
			if (vis[nr][nc] || arr[nr][nc] != color) continue;

			q.push({ nr,nc });
			vis[nr][nc] = 1;
			rem[group].push_back({ nr,nc });
		}
	}

	if (rem[group].size() < 4) {
		rem[group].clear();
		return 0;
	}
	return 1;
}

void Remove(int num_group) {
	for (int i = 0; i < num_group; i++) {
		for (auto e : rem[i]) {
			arr[e.r][e.c] = '.';
		}
		rem[i].clear();
	}

	// 각 열별로 터트리고 남은 뿌요들 순서대로 저장
	for (int c = 0; c < 6; c++) {
		remain = {};
		for (int r = 11; r >= 0; r--) {
			if (arr[r][c] != '.') remain.push(arr[r][c]);
		}
		
		// 바닥부터 순서대로 재배치
		int r = 11;
		while (!remain.empty()) {
			arr[r][c] = remain.front();
			remain.pop();
			r--;
		}
		// 그 위는 빈칸으로 세팅!!
		for (int i = r; i >= 0; i--) arr[i][c] = '.';
	}
}


// 맵 전체를 스캔하며 4개 이상 인접한 그룹을 모두 찾는다!!
int FindGroup() {
	fill(&vis[0][0], &vis[11][6], 0);
	int group = 0;

	for (int r = 11; r >= 0; r--) {
		for (int c = 0; c < 6; c++) {
			if (arr[r][c] == '.') continue;
			if (vis[r][c]) continue;

			if (FloodFill(r, c, group)) group++;
		}
	}
	return group;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
    Input();
    int cnt = 0;

    while (1) {
        int num_group = FindGroup();
        if (num_group == 0) break;

        Remove(num_group); // 4개이상 인접한 그룹 한번에 제거
        cnt++;
    }
    cout << cnt << "\n";
}
