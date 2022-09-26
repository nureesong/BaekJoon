/************************************/
// [2812] 크게 만들기 (골드3)
// Monotonic stack: 스택에 남길 숫자를 저장한다. (내림차순)
// 스택의 맨 뒤부터 현재값과 비교 O(N) - 20ms
// 단, 마지막에 스택을 거꾸로 출력해야 되니까 deque 사용!!
/************************************/

#include <iostream>
#include <deque>
using namespace std;

int N, K;
int arr[500000 + 5];  // 입력으로 주어진 숫자
deque<int> deq;       // 남길 숫자 (monotonic stack)

void Solve() {
	int cnt = K; // 남아있는 제거할 숫자 개수

	// 남아있는 숫자의 맨 뒤부터 현재값과 비교 O(N)
	for (int i = 0; i < N; i++) {
		// deq.back() >= arr[i] 가 될 때까지 스택의 마지막 값을 제거한다.
		// 스택이 비었거나 이미 K개 제거했으면 while문 진입X
		while (cnt && (!deq.empty()) && (arr[i] > deq.back())) {
			deq.pop_back();
			cnt--;
		}

		deq.push_back(arr[i]);
	}

	// 앞쪽부터 (N - K)자리만 출력
	int digit = N - K;
	for (int i = 0; i < digit; i++) {
		cout << deq.front();
		deq.pop_front();
	}
}

void Input() {
	char c;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> c;
		arr[i] = c - '0';
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
}
