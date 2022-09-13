#include <iostream>
using namespace std;

int N;
int S[9 + 2][9 + 2]; // 스도쿠 판, (1,1)부터 시작

struct Point {
	int r, c;
}E[81];  // 빈 칸 정보
int cnt; // 빈 칸 개수

int flagR[9 + 2][9 + 2]; // row (1~9행)
int flagC[9 + 2][9 + 2]; // column (1~9열)
int flagB[9 + 2][9 + 2]; // block (1~9번 정사각형)

// n번째 빈칸에 들어갈 숫자 탐색
int DFS(int n) {
	if (n >= cnt) return true;
	
	// n번째 빈 칸의 행, 열, 블록번호
	int r = E[n].r;
	int c = E[n].c;
	int b = ((r - 1)/3) * 3 + (c - 1)/3 + 1;

	for (int num = 1; num <= 9; num++) {
		if (flagR[r][num]) continue;
		if (flagC[c][num]) continue;
		if (flagB[b][num]) continue;

		flagR[r][num] = 1;
		flagC[c][num] = 1;
		flagB[b][num] = 1;
		S[r][c] = num;
		
		if (DFS(n + 1)) return true;

		flagR[r][num] = 0;
		flagC[c][num] = 0;
		flagB[b][num] = 0;
		S[r][c] = 0;
	}
	return false;
}

void Input() {
	int tmp, p, q, block;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> tmp;
			S[i][j] = tmp;
			
			if (tmp == 0) E[cnt++] = { i,j };
			else {
				flagR[i][tmp] = 1;
				flagC[j][tmp] = 1;

				p = (i - 1) / 3;
				q = (j - 1) / 3;
				block = p * 3 + q + 1;
				flagB[block][tmp] = 1;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	DFS(0);
	
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			cout << S[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
