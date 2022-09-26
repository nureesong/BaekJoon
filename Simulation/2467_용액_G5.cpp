/********************************/
// [2467] 용액 (골드5)
// 투포인터 O(N) - 12ms, 2412KB
// 0은 산성에 포함시키기
/********************************/

// [솔루션] 투포인터 O(N) - 12ms, 2412KB
// 가장 왼쪽, 오른쪽에서부터 합을 계산하며
// l + r < 0 이면 l을 증가시키고
// l + r > 0 이면 r을 감소시키기
// 두 수의 부호를 고려할 필요없다!
#if 0
#include <iostream>
using namespace std;

int N;
int arr[100000 + 5];

int minabs = 0x7fffffff;
int small, large;

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

void Solve() {
	int l = 0, r = N - 1;
	int sum;

	while (l < r) {
		sum = arr[l] + arr[r];

		if (abs(sum) < minabs) {
			minabs = abs(sum);
			small = arr[l];
			large = arr[r];
		}
		if (minabs == 0) return;
		
		if (sum < 0) l++;
		else r--;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
	cout << small << " " << large << "\n";
}
#endif


// [내 코드] 투포인터 O(N + N) - 12ms, 2412KB
// 0과 근접한 음수, 양수부터 합 계산
// 두 수의 부호가 같은 경우, 다른 경우 나눠서 진행
#if 0
#include <iostream>
using namespace std;

int N;
int arr[100000 + 5];
int mid; // 산성용액 시작부분

int minabs = 0x7fffffff;
int small, large;

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

void Solve() {
	// 산성용액 시작지점 찾기 (0은 산성에 포함)
	for (mid = 0; arr[mid] < 0; mid++);

	// 서로 다른 부호끼리 합 해보기 (0과 근접한 값부터)
	int neg = mid - 1, pos = mid; 
	int sum;

	while (neg >= 0 && pos < N) {
		sum = arr[neg] + arr[pos];

		if (abs(sum) < minabs) {
			minabs = abs(sum);
			small = arr[neg];
			large = arr[pos];
		}
		if (minabs == 0) return;
		
		if (sum < 0) pos++;
		else neg--;
	}

	// 음수끼리 합
	if (mid >= 2) {
		sum = abs(arr[mid - 1]) + abs(arr[mid - 2]);
		if (sum < minabs) {
			minabs = sum;
			small = arr[mid - 2];
			large = arr[mid - 1];
		}
	}

	// 양수끼리 합
	if (mid <= N - 2) {
		sum = arr[mid] + arr[mid + 1];
		if (sum < minabs) {
			minabs = sum;
			small = arr[mid];
			large = arr[mid + 1];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
	cout << small << " " << large << "\n";
}
#endif
