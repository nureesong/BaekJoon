/**************************************/
// [16571] 알파 틱택토 (골드3)
/**************************************/

#include <iostream>
#include <vector>
using namespace std;

struct POS {
	int r, c;
};

vector<POS> Empty; // 빈칸 위치 저장
int chk[9];        // i번째 빈칸에 말을 놓았는지 체크

// 각 플레이어 별 게임판에 놓인 본인 말 개수 (플레이어 번호 - 0: X, 1: O)
int cnt_row[2][3]; // 행
int cnt_col[2][3]; // 열
int cnt_l[2];      // 좌상향 대각선
int cnt_r[2];      // 우상향 대각선

int init_turn; // XO 개수 총합 -> 어떤 플레이어 차례인지 판단하는 데 사용

void Input(void) {
    int n;
	for (int r = 0; r < 3;r++) {
		for (int c = 0; c < 3;c++) {
			cin >> n;
			n--; // X = 0, O = 1에 매핑하기 위해 1을 빼준다.

            if (n == -1) Empty.push_back({r,c}); // 빈칸
            else {  // X,O
                init_turn++;
                cnt_row[n][r]++;
                cnt_col[n][c]++;
                if (r == c) cnt_l[n]++;
                if (r + c == 2) cnt_r[n]++;
            }
		}
	}
}

void Set(int xo, int i) {
	int r = Empty[i].r;
    int c = Empty[i].c;
	cnt_row[xo][r]++;
	cnt_col[xo][c]++;
	if (r == c) cnt_l[xo]++;
	if (r +  c == 2) cnt_r[xo]++;
	chk[i] = 1;
}

void Clear(int xo, int i) {
	int r = Empty[i].r;
    int c = Empty[i].c;
	cnt_row[xo][r]--;
	cnt_col[xo][c]--;
	if (r == c) cnt_l[xo]--;
	if (r + c == 2) cnt_r[xo]--;
	chk[i] = 0;
}

// 현재 플레이어가 i번째 빈칸에 말 놓으면 빙고가 되는지 확인
int Check_Win(int xo, int i) {
	int r = Empty[i].r;
    int c = Empty[i].c;
	return (cnt_row[xo][r] == 2) || (cnt_col[xo][c] == 2) || \
    (r == c && cnt_l[xo] == 2) || (r + c == 2 && cnt_r[xo] == 2);
}

// t턴의 플레이어의 최선의 결과 리턴 (0: W, 1: D, 2: L)
// t = 현재까지 놓은 말의 개수 -> 짝수개면 X 차례, 홀수개면 O 차례
int DFS(int t) {         
	if (t == 9) return 1; // 말 9개 놓았는데도 이긴 사람이 없음 -> 무승부

	int xo = t % 2; // 현재 플레이어 = 나
    int best = 3;   // 나의 입장에서 최고의 결과 (승:0, 무:1, 패:2)
	
    // 빈 칸 중 한 개 선택해서 말 놓기
	for (int i = 0; i < Empty.size(); i++) {
		if (chk[i]) continue;  // 이미 i번째 빈칸에 말 존재

        // 내가 i번째 빈칸에 말 놓으면 이기는 경우, 다른 빈칸 해볼 필요없음
		if (Check_Win(xo, i)) return 0;

        // 이기지 않는 경우, i번째 빈칸에 말 놓고 상대 턴 결과 받아보기
		Set(xo, i);								
		ret = 2 - DFS(t + 1);   // 상대방의 최고 결과를 내 입장으로 뒤집기
        best = (ret < best) ? ret : best; 
		
        // 복원!!! -> 이걸 best == 0일 때 리턴하는 부분 뒤에 놔서 틀린 거였어ㅠㅠ
        Clear(ox, i);	
        
        // 내가 i번째 빈칸에 말 놓을 때는 이길 수 있는 수가 없지만, 
        // 상대방이 다음 턴에 말 놨을 때 지는 경우가 존재하기 때문에 
        // 나의 최고 결과(best)가 0(승리)인 경우 다른 빈칸에 말 놓을 필요 없음!
		if (best == 0) return 0;
	}

	return best; // 내가 어떤 빈칸에 말을 놔도 비기거나 지는 경우만 여기서 리턴
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Input();

	// 현재 말 놓은 차례인 플레이어의 최고 게임 결과 출력
    char res_char[] = { 'W','D','L' };
	cout << res_char[DFS(init_turn)] << '\n';

	return 0;
}
