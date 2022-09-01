#include <stdio.h>

int N, d, k, c;
int arr[30000 + 10];

void input(void) {
	scanf("%d %d %d %d", &N, &d, &k, &c);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
}

int count(int i) {
	int tmp, cnt = 1; // 쿠폰번호는 항상 먹을 수 있음
	int flag[3000 + 10] = { 0, };  // 1부터 시작

	for (int j = 0; j < k; j++) {
		// 초밥 가짓수 체크 (쿠폰번호 제외)
		tmp = arr[(i + j) % N];
		if (tmp == c) continue;

		if (flag[tmp]) continue;
		flag[tmp] = 1; cnt++;
	}
	return cnt;
}

int solve(void) {
	int cnt, max = 0;

	for (int i = 0; i < N; i++) {
		cnt = count(i);
		if (cnt > max) max = cnt;
		//printf("i = %d,  cnt = %d,  max = %d\n", i, cnt, max);
	}
	return max;
}

void main(void) {
	//freopen("in.txt", "r", stdin);
	input();
	printf("%d\n", solve());
}
