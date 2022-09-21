/***********************************/
// [1920] 수 찾기 (실버4)
// unordered_set: 64ms
// set: 86ms
// Binary Search: 52ms
/***********************************/
// Unordered Set
#if 0
#include <iostream>
#include <unordered_set>
using namespace std;

int N, M;
unordered_set<int> s;

void Input() {
	int tmp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		s.insert(tmp);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); 
	cout.tie(0);

	Input();

	cin >> M;
	int num;
	for (int i = 0; i < M; i++) {
		cin >> num;
		cout << (s.find(num) != s.end()) << "\n";
	}
}
#endif

// Binary Search
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[100000 + 10];

int BS(int s, int e, int num) {
	while (s <= e) {
		int m = (s + e) / 2;

		if (arr[m] == num) return 1;

		if (arr[m] < num) s = m + 1;
		else e = m - 1;
	}
	return 0;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	sort(arr, arr + N);

	cin >> M;
	int num;
	while (M--) {
		cin >> num;
		cout << BS(0, N-1, num) << '\n';
	}
}
#endif
