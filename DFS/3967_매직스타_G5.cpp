/*************************************************************/
// [3967] 매직 스타 (골드5)
// DFS
// 가지치기: for문 안에서 할지 DFS 들어오자마자 할지 잘 생각하자!
// DFS 호출 후 돌아왔을 때 무엇을 복원해야 하는지 주의!!
/************************************************************/

#include <iostream>
#include <vector>
using namespace std;


char arr[5 + 2][9 + 2];
struct POS {
	int r, c;
};
// 매직스타에 사용되는 칸 - 0~11번으로 인덱싱
POS B[12] = {
	{0,4},
	{1,1}, {1,3}, {1,5}, {1,7}, 
	{2,2}, {2,6}, 
	{3,1}, {3,3}, {3,5}, {3,7}, 
	{4,4}
};

vector<int> E; // 빈 칸 번호 저장
int cnt_empty;

// 모든 칸은 2개의 줄에 포함된다.
int LINE[12][2] = {
	{0,1}, 
	{2,3}, {2,0}, {2,1}, {2,4},
	{0,3}, {1,4},
	{0,5}, {3,5}, {4,5}, {1,5},
	{3,4}
};
int sum[6];  // 6줄에 써있는 숫자 합 => 모두 26이 되는 게 목표
int cnt[6];  // 각 줄에 채워진 숫자 개수
int vis[12 + 1]; // 게임판에 사용된 숫자(1~12) 체크


void Input() {
	char c;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> c;
			arr[i][j] = c;
			
			if (c >= 'A' && c <= 'L' ) {
				vis[c - 'A' + 1] = 1; // 사용된 숫자 체크
			}
		}
	}

	for (int i = 0; i < 12; i++) {
		if (arr[B[i].r][B[i].c] == 'x') E.push_back(i);
	}
	cnt_empty = E.size();
}

void Init_Sum() {
	for (int i = 0; i < 12; i++) {
		int r = B[i].r;
		int c = B[i].c;
		if (arr[r][c] == 'x') continue;

		for (int j = 0; j < 2; j++) {
			sum[LINE[i][j]] += arr[r][c] - 'A' + 1;
			cnt[LINE[i][j]]++;
		}
	}
}


int DFS(int e) {
	if (e == cnt_empty) return 1;

	// 1 ~ 12 중 사용되지 않은 숫자 선택 (작은 수부터!)
	int n = E[e];
	int r = B[n].r, c = B[n].c;
	int a = LINE[n][0];
	int b = LINE[n][1];

	for (int i = 1; i <= 12; i++) {
		if (vis[i]) continue;
		
		// 가지치기
		if (cnt[a] == 3 && sum[a] + i != 26) continue;
		if (sum[a] + i > 26) break; // i보다 더 큰 숫자는 당연히 선택 불가
		if (cnt[b] == 3 && sum[b] + i != 26) continue;
		if (sum[b] + i > 26) break;

		// n번 노드에 숫자 i 선택하기
		arr[r][c] = i - 1 + 'A';
		vis[i] = 1;
		sum[a] += i; cnt[a]++;
		sum[b] += i; cnt[b]++;
		
		if (DFS(e + 1)) return 1;

		// 복원
		vis[i] = 0;
		sum[a] -= i; cnt[a]--;
		sum[b] -= i; cnt[b]--;
	}
	return 0;
}

void PrintArr() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Init_Sum();

	DFS(0);
	PrintArr();
}
