/**********************************/
// [백준 1912] 연속합 (실버2)
/*********************************/
#include <iostream>
using namespace std;

int N;
int arr[100000 + 10]; 

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

int Solve() {
	int sum = 0, max = arr[0];

	for (int i = 0; i < N; i++) {
		if (sum < 0) sum = arr[i];  // 새로 시작
		else sum += arr[i];
		
		if (sum > max) max = sum;
	}
	return max;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	freopen("in.txt", "r", stdin);
	Input();
	cout << Solve();
}
