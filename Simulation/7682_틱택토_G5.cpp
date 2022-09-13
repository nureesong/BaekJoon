/********************************/
// [7682] 틱택토 (골드5)
// DFS로 푸는 방법은 모르겠다..
// 그냥 룰베이스로 해결
/********************************/
#include <iostream>
#include <string>
using namespace std;

string board;
int cntX, cntO;

void CountXO() {
	cntX = 0; cntO = 0; // Init 까먹지마!!

	for (int i = 0; i < 9; i++) {
		if (board[i] == 'X') cntX++;
		else if (board[i] == 'O') cntO++;
	}
}

int IsBingo(char c) {
	// 가로 빙고 (0~2번째  3~5번째  6~8번째가 같은지 확인)
	for (int i = 0; i < 9; i += 3) {
		if (board[i] == c && board[i + 1] == c && board[i + 2] == c) return 1;
	}

	// 세로 빙고 (0,3,6번째  1,4,7번째  2,5,8번째가 같은지 확인)
	for (int i = 0; i < 3; i++) {
		if (board[i] == c && board[i + 3] == c && board[i + 6] == c) return 1;
	}

	// 대각선 빙고
	if (board[0] == c && board[4] == c && board[8] == c) return 1;
	if (board[2] == c && board[4] == c && board[6] == c) return 1;

	return 0;
}

int Solve() {
	CountXO();  // XO 개수 세기
	if ((cntO > cntX) || (cntX - cntO > 1)) return 0;
	if (cntX < 3) return 0;

	int bX = IsBingo('X');
	int bO = IsBingo('O');

	if (!bX && !bO) {                      // 둘 다 빙고가 아니면
		return ((cntX == 5) && (cntO == 4)); // 게임판 가득 찼을 때만 valid
	}
	else if (bX && !bO) {   // X만 빙고
		return cntX - cntO;   // X가 O보다 한 개 많아야 valid
	}
	else if (!bX && bO){    // O만 빙고
		return cntX == cntO;  // X와 O의 개수가 같아야 valid
	}
	return 0; // 둘 다 빙고면 invalid
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while (1) {
		cin >> board;
		if (board == "end") break;

		if (Solve()) cout << "valid\n";
		else cout << "invalid\n";
	}
}
