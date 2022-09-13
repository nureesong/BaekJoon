/********************************/
// [A2] 페그 솔리테어 (백준 9207 - 골드4)
// 게임판 크기: 5 X 9로 고정
// 점프 횟수 = 핀 제거 개수 이므로
// 핀의 개수가 동일하면 이동횟수도 동일할 수밖에 없다!!
/********************************/

#include <iostream>
using namespace std;

int cnt;  // 핀 개수
int arr[5 + 2][9 + 2]; // 0: 빈칸, 1: 벽, 2: 핀
int min_pin;

// n_pin: 게임판에 남아있는 핀 개수
void DFS(int n_pin) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	if (n_pin < min_pin) min_pin = n_pin;

	// 게임판에 존재하는 모든 핀을 대상으로 4방향 이동 탐색
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 9; c++) {
			if (arr[r][c] != 2) continue;

			for (int i = 0; i < 4; i++) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr < 0 || nr >= 5 || nc < 0 || nc >= 9) continue;
				if (arr[nr][nc] != 2) continue; // 빈칸/벽이면 이동 불가

				// 인접영역에 핀이 존재하면 다음 칸이 비어있는지 확인
				int nnr = nr + dr[i];
				int nnc = nc + dc[i];
				if (nnr < 0 || nnr >= 5 || nnc < 0 || nnc >= 9) continue;
				if (arr[nnr][nnc] != 0) continue;

				arr[nnr][nnc] = 2; // 점프
				arr[r][c] = 0;	   // 현위치 빈칸으로 변경
				arr[nr][nc] = 0;   // 인접한 핀 제거

				DFS(n_pin - 1);

				arr[nnr][nnc] = 0; // 점프 취소
				arr[r][c] = 2;	   // 이동 전 위치로 복원
				arr[nr][nc] = 2;   // 인접한 핀 복원
			}
		}
	}
	// 모든 핀을 다 훑어도 이동할 곳이 없으면 
	// 여기서 함수가 종료되고 호출한 곳으로 돌아가므로 리턴 필요없음.
}

void Input() {
	cnt = 0;
	char c;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> c;
			if (c == '.') arr[i][j] = 0; // 다음 테케를 위해 빈칸도 반드시 마킹하기!!
			else if (c == '#') arr[i][j] = 1;
			else if (c == 'o') {
				arr[i][j] = 2; cnt++;
			}
		}
	}
	min_pin = cnt; // Init
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		Input();
		DFS(cnt);
		cout << min_pin << " " << cnt - min_pin << "\n";
	}
}
