/**********************************/
// [1913] 달팽이 (실버3)
/*********************************/
#include <iostream>
using namespace std;

int N, M;
int arr[1000 + 10][1000 + 10]; // (1, 1)부터 시작
int x, y;

void Solve() {
	int dr[] = { 1, 0, -1, 0 };
	int dc[] = { 0, 1, 0, -1 };
	int i = N*N, d = 0, r = 0, c = 1;
	int nr, nc;

	while (i > 0) {
		nr = r + dr[d];
		nc = c + dc[d];

		if (nr < 1 || nr > N || nc < 1 || nc > N || arr[nr][nc]) {
			d++;
			if (d == 4) d = 0;

			nr = r + dr[d];
			nc = c + dc[d];
		}
		
		r = nr;
		c = nc;
		if (i == M) {
			x = r;
			y = c;
		}
		arr[r][c] = i--;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	cout << x << " " << y << "\n";
}

int main() {
	cin >> N >> M;
	Solve();
}
