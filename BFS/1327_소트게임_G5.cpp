/***********************************/
// [1327] 소트 게임 (골드5)
// BFS, Queue, 동일한 가중치
/***********************************/
// 문자열 - i ~ i+K-1 전부 reverse (36ms)
// 문자열 - i ~ i+K-1 에서 대칭끼리 swap (28ms)
#if 0
#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

int N, K;
int arr[8 + 2];
string num, tar;
unordered_set<string> vis; // 크기가 너무 커서 배열로 못 만든다.

struct STATUS {
	string n;
	int cnt;
};
queue<STATUS> q;


string Reverse(string num, int i) {
	// K개 문자열에서 대칭끼리 swapping
	char tmp;
	for (int j = 0; j < K / 2; j++) {
		tmp = num[i + j];
		num[i + j] = num[i + K-1 - j];
		num[i + K-1 - j] = tmp;
	}
	return num;
  
  // K개의 문자열 전부 뒤집기
	/*string rev = "";
	for (int j = 0; j < i; j++) rev += num[j];
	for (int j = i + K - 1; j >= i; j--) rev += num[j];
	for (int j = i + K; j < N; j++) rev += num[j];
	return rev;*/
}

int BFS() {
	// 1부터 N까지 정수로 이루어진 N자리 순열이므로
	// 오름차순 정렬된 문자열 = "123...N"
	for (char c = '1'; c <= N + '0'; c++) tar += c;
	
	if (num == tar) return 0;

	q.push({ num, 0 });
	vis.insert(num);

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int i = 0; i <= N - K; i++) {
			string next = Reverse(cur.n, i);
			int ncnt = cur.cnt + 1;

			if (next == tar) return ncnt;
			if (vis.find(next) != vis.end()) continue;

			q.push({ next, ncnt });
			vis.insert(next);
		}
	}
	return -1;
}

void Input() {
	cin >> N >> K;
	char c;
	for (int i = 0; i < N; i++) {
		cin >> c;
		num += c;
		arr[i] = c - '0';
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << BFS() << "\n";
}
#endif
