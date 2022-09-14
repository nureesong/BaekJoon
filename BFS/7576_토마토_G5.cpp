/********************************/
// [7576] 토마토 (골드5)
// BFS - 초기 큐에 익은 토마토 담기
/********************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int M, N;
int arr[1000 + 10][1000 + 10]; // 1:익은, 0:익지않은, -1:빈칸
int goal;        // 전체영역에서 빈 칸 제외
int cnt_tomato;  // 익은 토마토 개수

struct STATUS {
	int r, c, d;
};
queue<STATUS> q;


int BFS() {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };
	
	STATUS cur;
	while (!q.empty()) {
		cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
			if (arr[nr][nc] != 0) continue; // 안 익은 토마토로만 이동가능
			
			cnt_tomato++;
			if (cnt_tomato == goal) return cur.d + 1;

			q.push({ nr, nc, cur.d + 1 });
			arr[nr][nc] = 1; // 익은 토마토로 바꾸기
		}
	}

	if (cnt_tomato < goal) return -1;
	return cur.d;
}

void Input() {
	cin >> M >> N;
	
	goal = M * N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
      
			if (arr[i][j] == -1) goal--;
			else if (arr[i][j] == 1) {
				q.push({ i,j,0 }); // 초기 큐에 익은 토마토 담기
				cnt_tomato++;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << BFS() << "\n";
}
