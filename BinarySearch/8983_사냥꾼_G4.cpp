/*********************************/
// [8983] 사냥꾼 (골드4)
/*********************************/
// Binary Search - O(MlogM + NlogM)
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

int M, N, L;
int x[100000 + 10];

struct Point {
	int a, b;
}ani[100000 + 10];

void Input() {
	cin >> M >> N >> L;
	for (int i = 0; i < M; i++) {
		cin >> x[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> ani[i].a >> ani[i].b;
	}
}

int BinarySearch_Lower(int s, int e, int t) {
	// t보다 크거나 같은 값 중에 제일 작은 인덱스 찾기
	int lb = -1;
	while (s <= e) {
		int m = (s + e) / 2;
		if (x[m] >= t) {
			lb = m;
			e = m - 1;
		}
		else s = m + 1;
	}
	return lb;
}

int BinarySearch_Upper(int s, int e, int t) {
	// t보다 작거나 같은 값 중에 제일 큰 인덱스 찾기
	int ub = -1;
	while (s <= e) {
		int m = (s + e) / 2;
		if (x[m] <= t) {
			ub = m;
			s = m + 1;
		}
		else e = m - 1;
	}
	return ub;
}

int Solve() {
	int cnt = 0;
	int lb, ub;
	sort(x, x + M);

	for (int i =0; i < N; i++) {
		if (ani[i].b > L) continue;
		
		// |x - a| + b <= L  ->   a - (L-b) <= x <= a + (L-b)
		// lb : a - (L -b) 이상인 값 중 제일 작은 인덱스
		// lb를 찾았더라도 lb번째 사대가 상한 a + (L-b) 을 벗어나도 못 잡는다.
		lb = BinarySearch_Lower(0, M - 1, ani[i].a - (L - ani[i].b));
		if (lb < 0 || x[lb] > ani[i].a + (L - ani[i].b)) continue;
		cnt++;
		cout << ani[i].a << " " << ani[i].b << ",  " << lb << " " << ub << "\n\n";
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	cout << Solve();
}
#endif


// 이중 포인트 전략   O(NlogN + MlogM + M+N)
// 둘다 정렬해놓고 동물 idx, 사대 idx 따로 움직이기
// 동물 정렬: x, y 좌표의 합 기준으로 정렬 (즉, 대각선 방향으로 정렬)
// 거리 <= L 이면 잡히니까 동물idx++ (같은 사대에서 그 다음 동물 탐색)
// 거리 > L 이고 사대 < 동물이면 사대idx++ (다음 사대에서 같은 동물 겨냥)
// 거리 > L 이고 사대 > 동물이면 동물idx++
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

int M, N, L;
int x[100000 + 10];

struct Point {
	int a, b;
}ani[100000 + 10];

void Input() {
	cin >> M >> N >> L;
	for (int i = 0; i < M; i++) {
		cin >> x[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> ani[i].a >> ani[i].b;
	}
}

bool comp(const Point& x, const Point& y) {
	return x.a + x.b < y.a + y.b;
}

int Solve() {
	int cnt = 0;
	int gidx = 0, aidx = 0;

	sort(x, x + M);
	sort(ani, ani + N, comp);

	while (gidx < M && aidx < N) {
		int dist = abs(x[gidx] - ani[aidx].a) + ani[aidx].b; // 동물과 사대 사이 거리

		if (dist <= L) {  // 현재 사대에서 동물을 잡을 수 있다.
			cnt++;
			aidx++;  // 다음 동물 탐색
		}
		else if (x[gidx] < ani[aidx].a) { // 사대가 동물보다 왼쪽에 있으므로
			gidx++;  // 다음 사대로 넘어가서 그 동물을 잡을 수 있는지 다시 확인
		}
		else {         // 사대가 더 오른쪽에 있으면 
			aidx++;  // 같은 사대에서 그 다음 동물 탐색
		}
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);
	Input();
	cout << Solve();
}
#endif
