/*******************************************/
// [3195] ribari(어민) (골드3)
// Parametric Search - 최대 입양 아이들 수
// 탐색 범위: 각 마을 중 최소~최대 물고기 보유량
// 각 마을이 d명을 입양할 수 있는지 확인 -> O(N)
// 제일 왼쪽 마을부터 물고기 보유량 >= d 인지 확인
// 부족하면 오른쪽 마을에서 빌리고 남으면 오른쪽으로 이월
// 총 시간 복잡도: O(logB * N)
/*******************************************/

// 28ms, 2800KB
#include <iostream>
using namespace std;

int N;
struct TOWN {
	int p;       // position
	int f; // fish (물고기 이월하면서 누적되면 21억보다 클수도)
}town[100000 + 2];
long long minf = 0x7fffffff, maxf; // 최소, 최대 물고기 보유량


void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> town[i].p >> town[i].f;
		minf = (town[i].f < minf) ? town[i].f : minf;
		maxf = (town[i].f > maxf) ? town[i].f : maxf;
	}
}

int Check(int d) {
	// 왼쪽마을에서 물고기 받았으면 양수, 빌려줬으면 음수
	long long diff = 0; 

	for (int i = 0; i < N-1; i++) {
		int tax = town[i + 1].p - town[i].p;

		if (town[i].f + diff >= d) {
			diff = town[i].f + diff - d - tax;  // 남은 물고기 이월
			if (diff < 0) diff = 0;       // 음수면 이월하는 게 손해
		}
		else { // 물고기 부족한 경우 오른쪽 마을에서 빌려온다.
			diff = -(d - (town[i].f + diff) + tax);
		}
	}

	// 마지막 마을에 d 이상이면 입양 가능
	return town[N - 1].f + diff >= d;
}

int BS(int s, int e) {
	int sol = -1;
	while (s <= e) {
		int m = (s + e) / 2;
		if (Check(m)) {
			sol = m;
			s = m + 1;
		}
		else e = m - 1;
	}
	return sol;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << BS(minf, maxf) << "\n";
}
#endif
