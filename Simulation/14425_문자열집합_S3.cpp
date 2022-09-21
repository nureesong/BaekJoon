/***********************************/
// [14425] 문자열 집합 (실버3)
// unordered_multiset: 64ms
// Binary Search     : 72ms
/***********************************/
// Unordered_multiset
#if 0
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int N, M;
int cnt;
string tmp;
unordered_multiset<string> s;

void Input() {
	cin >> N >> M;
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

	while (M--) {
		cin >> tmp;
		if (s.find(tmp) != s.end()) cnt++;
	}
	cout << cnt << "\n";
}

#endif

// Binary Search
#if 0
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N, M, cnt;
string arr[10000 + 10];

int BS(int s, int e, string tar) {
	while (s <= e) {
		int m = (s + e) / 2;

		if (arr[m] == tar) return 1;

		if (arr[m] < tar) s = m + 1;
		else e = m - 1;
	}
	return 0;
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + N);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();	

	string tmp;
	while (M--) {
		cin >> tmp;
		if (BS(0, N - 1, tmp)) cnt++;
	}
	cout << cnt << "\n";
}
#endif
