/************************************************/
// [2467] 용액 (골드5)
// 이진탐색 O(NlogN) - 16ms, 2412KB
// 현재 숫자의 반대 부호값과 가까운 두 개만 더해보기
// 0은 산성에 포함
// 투포인터 O(N)     - 12ms, 2412KB (Simulation 폴더 참고)
/***********************************************/

#include <iostream>
using namespace std;

int N;
int arr[100000 + 5]; // 오름차순 정렬
int minabs = 0x7fffffff;
int small, large;

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}


// target 이하인 값들 중 최댓값의 인덱스 리턴
int BS_upper(int s, int e, int tar) {
	int ub = -1;
	while (s <= e) {
		int m = (s + e) / 2;
		if (arr[m] <= tar) {
			ub = m;
			s = m + 1;
		}
		else e = m - 1;
	}
	return ub;
}

void Solve() {
	int sum;

	for (int i = 0; i < N; i++) {
		// 현재 값의 반대 부호가 상한인 인덱스 찾기
		// 특성값이 전부 음수이면 항상 ub = N-1
		//         전부 0과 양수이면 항상 ub = -1
		// 현재 값의 반대 부호 이하인 값이 없으면 ub = -1

		int ub = BS_upper(i + 1, N - 1, -arr[i]);
		
		if (ub != -1) {
			sum = abs(arr[i] + arr[ub]);
			if (sum < minabs) {
				minabs = sum;
				small = arr[i];
				large = arr[ub];
			}
		}

		// ub의 다음 값이랑도 더해보기
		if (ub + 1 != i && ub + 1 < N) {
			sum = abs(arr[i] + arr[ub + 1]);
			if (sum < minabs) {
				minabs = sum;
				// *주의* ub = -1이면 i < ub+1 성립X -> 마지막에 대소비교
				small = arr[i];
				large = arr[ub + 1];
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();

	// *주의*에 의해 대소비교 필요!
	if (small > large) cout << large << " " << small << "\n";
	else cout << small << " " << large << "\n";
}
