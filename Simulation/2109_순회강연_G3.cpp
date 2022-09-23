/************************************/
// [2109] 순회강연 (골드3)
// **주의** d일째가 아닌 d일 안에서 선택하는 것이다!
/************************************/

// [솔루션] set의 lower_bound, erase 활용 (4ms)
// 비어있는 날을 set에 담아서 빈 곳 중 제일 큰 값 빠르게 탐색 O(NlogN)
// lower_bound(key): 찾으려는 key값 이후 위치 중 첫번째 인덱스 리턴
#if 1
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int N, maxd;

struct DATA {
	int p, d;
}arr[10000 + 10];

bool comp(DATA& a, DATA& b) {
	return a.p > b.p;
}

set<int, greater<int>> s; // 내림차순 정렬

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i].p >> arr[i].d;
		maxd = (arr[i].d > maxd) ? arr[i].d : maxd;
	}
}

int Solve() {
	// 강연료 기준 내림차순 정렬
	sort(arr, arr + N, comp);

	// 비어있는 날 set에 담기
	for (int i = 1; i <= maxd; i++) {
		s.insert(i);
	}

	int sum = 0;
	for (int i = 0; i < N; i++) {
		// 찾으려는 키 값이 없으면, 이후 인덱스 중 첫번째 위치 리턴
		// s를 내림차순 정렬해놨으므로 d이하의 날짜 중 제일 최근 의미
		auto iter = s.lower_bound(arr[i].d);
		
		if (iter != s.end()) {
			sum += arr[i].p;
			s.erase(iter);
		}
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
#endif


// 정렬 & 그리디 (32ms)
// n일째에 이미 강연 스케줄이 있으면 이전에 비어있는 날 탐색 O(N^2)
#if 0
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int N;
int chk[10000 + 10]; // n일째 강연 여부

struct DATA {
	int p, d;
}arr[10000 + 10];

bool comp(DATA& a, DATA& b) {
	return a.p > b.p;
}


void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i].p >> arr[i].d;
	}
}

int Solve() {
	// 강연료 기준 내림차순 정렬
	sort(arr, arr + N, comp);

	int sum = 0;
	for (int i = 0; i < N; i++) {
		int day = arr[i].d;

		// 해당일에 강연 스케줄 비었으면 강의하기
		if (!chk[day]) { 
			chk[day] = 1;
			sum += arr[i].p;
			continue;
		}
		
		// 강연 스케줄이 있으면 이전 날짜 중에 비는 곳 찾기
		for (int j = day - 1; j > 0; j--) {
			if (!chk[j]) {
				chk[j] = 1;
				sum += arr[i].p;
				break;
			}
		}
	}

	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
#endif
