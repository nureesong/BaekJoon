/***********************************/
// [18808] 스티커 붙이기 (골드3)
// 4ms, 2028KB (1h 30min)
/************************************/

#include <iostream>
using namespace std;

int N, M, K;
int sol; // 스티커 붙은 칸 수
int note[40][40]; // 노트북

struct STICKER {
	int R;            // 행 크기
	int C;            // 열 크기
	int arr[10][10];  // 스티커 모양
}S[4]; // 회전 횟수별 스티커 1개에 대한 정보


void Input() {
	cin >> S[0].R >> S[0].C;
	for (int r = 0; r < S[0].R; r++) {
		for (int c = 0; c < S[0].C; c++) {
			cin >> S[0].arr[r][c];
		}
	}
}

// rot = 1 ~ 3만 입력된다.
void Rotate(int rot) {
	int R = S[rot-1].R;
	int C = S[rot-1].C;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			S[rot].arr[j][R-1 - i] = S[rot-1].arr[i][j];
		}
	}
	S[rot].R = C;
	S[rot].C = R;
}

// 노트의 (i,j)에 rot번 회전한 스티커 놓을 수 있는지 확인
int PutSticker(int i, int j, int rot) {
	int R = S[rot].R, C = S[rot].C;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			// 스티커가 있는 칸에 노트에도 이미 스티커가 있으면 불가능
			if (S[rot].arr[r][c] && note[i + r][j + c]) return 0;
		}
	}
	return 1;
}

int FindPosition(int rot) {
	int R = S[rot].R, C = S[rot].C;
	
	for (int i = 0; i <= N - R; i++) {
		for (int j = 0; j <= M - C; j++) {
			if (!PutSticker(i, j, rot)) continue;
			
			// 놓을 수 있으면 스티커 붙이기
			for (int r = 0; r < R; r++) {
				for (int c = 0; c < C; c++) {
					if (S[rot].arr[r][c]) {
						note[i + r][j + c] = 1;
						sol++;
					}
				}
			}
			return 1;
		}
	}
	return 0;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);

	cin >> N >> M >> K;
	for (int k = 0; k < K; k++) {
		Input();

		// 스티커를 rot번 회전했을 때 붙일 수 있는 위치 찾기
		for (int rot = 0; rot < 4; rot++) {
			if (rot) Rotate(rot);
			if (FindPosition(rot)) break;
		}
	}
	
	cout << sol << "\n";
}
