#include <iostream>
using namespace std;

int N;
int map[100 + 10][100 + 10]; // (1, 1)부터 시작

int minr = 101, maxr = 0;
int minc = 101, maxc = 0;

bool is_rect(int x1, int y1, int x2, int y2) {
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			if (map[i][j] == 0) return false;
		}
	}
	return true;
}

int Solve() {
	int area, max = 100;

	for (int i = minr; i < maxr + 10; i++) {
		for (int j = minc; j <= maxc + 10; j++) {
			if (map[i][j] == 0) continue;
			
			for (int p = i; p < maxr + 10; p++) {
				for (int q = j; q < maxc + 10; q++) {
					if (is_rect(i, j, p, q)) {
						area = (p - i + 1) * (q - j + 1);
						if (area > max) max = area;
					}
				}
			}
			
		}
	}
	return max;
}

void Input() {
	int r, c;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> r >> c;
		if (r < minr) minr = r;
		if (r > maxr) maxr = r;
		if (c < minc) minc = c;
		if (c > maxc) maxc = c;

		for (int i = r; i < r + 10; i++) {
			for (int j = c; j < c + 10; j++) {
				map[i][j] = 1;
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
	cout << Solve();
}
