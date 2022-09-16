/********************************/
// [6987] 월드컵 (골드5)
/********************************/
#include <iostream>
using namespace std;

struct GAME {
	int a, b; // 두 나라 번호(6개국 0~5번)
};
GAME game[15]; // 리그전 총 15경기(6C2)

int inp[4][6][3]; // 입력받은 경기결과 (0열:승, 1열:무, 2열:패)
int chk[4];       // 6개국 모두 승무패 합이 5인지 체크
int ans[4];       // 가능, 불가능 판단

// 총 15경기 대진표 만들기
void comb() {
	int id = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++) {
			game[id++] = { i, j };
		}
	}
}

// tc : 테케 번호 (0~3)
// id : 승무패 선택할 경기 번호 (0~14)
// cnt: 결과 테이블에서 제거해야 할 경기 수
bool DFS(int tc, int id, int cnt) {
	// 종료 조건
	if (id == 15 && cnt == 0) return true;
	if (id == 15 && cnt > 0) return false;
	
	int n1 = game[id].a;
	int n2 = game[id].b;
	
	// 경기결과 3가지 경우의 수. (n1, n2) 순서
	// i = 0: (승,패) = (0,2)
	// i = 1: (무,무) = (1,1)
	// i = 2: (패,승) = (2,0)
	for (int i = 0; i < 3; i++) {
		int s1 = i;
		int s2 = 2 - i;
		
		if (!inp[tc][n1][s1] || !inp[tc][n2][s2]) continue;

		inp[tc][n1][s1]--;
		inp[tc][n2][s2]--;
		if (DFS(tc, id + 1, cnt - 2)) return true;
		inp[tc][n1][s1]++;
		inp[tc][n2][s2]++;
	}
	return false;
}


void Input() {
	for (int i = 0; i < 4; i++) {
		for (int c = 0; c < 6; c++) {
			int sum = 0;
			for (int s = 0; s < 3; s++) {
				cin >> inp[i][c][s];
				sum += inp[i][c][s];
			}
			// 각 나라별 승무패 합이 5인지 확인
			chk[i] += (sum == 5);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	comb();

	for (int tc = 0; tc < 4; tc++) {
		// 6개국 모두 승무패 합이 5가 아니면 무조건 불가능
		if (chk[tc] < 6) continue;

		// 경기 결과 테이블의 총합이 30일 때만 DFS 탐색
		if (DFS(tc, 0, 30)) ans[tc] = 1;
	}
	
	for (int tc = 0; tc < 4; tc++) {
		cout << ans[tc] << " ";
	}
}
#endif
