#include <iostream>
using namespace std;

int N, d, k, c;
int arr[3000000 + 10];
int flag[3000 + 10];

int Solve() {
	int cnt = 1, max;
	flag[c] = 1;

	for (int i = 0; i < k; i++) {
		if (flag[arr[i]] == 0) cnt++;
		flag[arr[i]]++;
	}
	max = cnt;

	// Sliding window
	for (int i = 1; i < N; i++) {
		flag[arr[i - 1]]--;
		if (flag[arr[i - 1]] == 0) cnt--;
		
		if (flag[arr[(i + k - 1) % N]] == 0) cnt++;
		flag[arr[(i + k - 1) % N]]++;

		if (cnt > max) max = cnt;
	}
	return max;
}

void Input() {
	cin >> N >> d >> k >> c;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	cout << Solve() << "\n";
}
