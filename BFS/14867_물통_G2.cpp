/*************************************/
// [14867] 물통 (골드2)
// - 비트 마스킹: a, b 둘다 int니까 32bit로 표현
//   64비트짜리 long long 공간에 앞32칸은 a, 뒤32칸은 b 물 양 저장
// - set에 구조체를 넣을거면 비교객체 만들어줘야 함.
// - unordered_set에 구조체를 넣을거면 hash 연산 정의해줘야 함 -> 복잡 그 잡채
/*************************************/
// 솔루션 - A, B 물의 양을 하나의 수(64비트)로 합치기 -> 108ms
// A * 100001 + B로 합치는 것도 가능
#if 0
#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int A, B, C, D;
struct STATUS {
	int a, b, cnt;
};
queue<STATUS> q;

unordered_set<unsigned long long> vis;

// A와 B의 물의 양을 하나의 수(64비트)로 합치기
unsigned long long GetKey(int a, int b) {
	return ((unsigned long long)a << (32)) + (unsigned long long)b;
}

int BFS() {
	if (C == 0 && D == 0) return 0;

	// 6가지 경우 모두 둘 중 한 물통은 비거나 가득찬다.
	if (!(C == 0 || C == A || D == 0 || D == B)) return -1;

	q.push({ 0,0,0 });
	vis.insert(0);

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		STATUS cases[6] = {
			{A, cur.b, cur.cnt + 1}, // F(A)
			{cur.a, B, cur.cnt + 1}, // F(B)
			{0, cur.b, cur.cnt + 1}, // E(A)
			{cur.a, 0, cur.cnt + 1}, // E(B)
		};
		// Move(A, B): A에서 B로 이동
		int move = (cur.a <= B - cur.b) ? cur.a : B - cur.b;
		cases[4] = { cur.a - move, cur.b + move, cur.cnt + 1 };
		// Move(B, A): B에서 A로 이동
		move = (cur.b <= A - cur.a) ? cur.b : A - cur.a;
		cases[5] = { cur.a + move, cur.b - move, cur.cnt + 1 };
		
		
		for (int i = 0; i < 6; i++) {
			STATUS next = cases[i];
			unsigned long long k = GetKey(next.a, next.b);

			if (vis.find(k) != vis.end()) continue;
			if (next.a == C && next.b == D) return next.cnt;

			q.push(next);
			vis.insert(k);
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> A >> B >> C >> D;
	cout << BFS() << "\n";
}
#endif


// set에 구조체 넣고 Comp 객체 customize -> 276ms (set 느림)
#if 0
#include <iostream>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

int A, B, C, D;
struct STATUS {
	int a, b, cnt;
};
queue<STATUS> q;

struct VIS {
	int a, b;
};
struct COMP { // a, b 오름차순
	bool operator()(const VIS &d1, const VIS &d2) const {
		if (d1.a == d2.a) return d1.b < d2.b;
		return d1.a < d2.a;
	}
};
set<VIS, COMP> vis;


int BFS() {
	if (C == 0 && D == 0) return 0;
	if (!(C == 0 || C == A || D == 0 || D == B)) return -1;

	q.push({ 0,0,0 });
	vis.insert({ 0,0 });

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		STATUS next[6] = {
			{A, cur.b, cur.cnt + 1}, // F(A)
			{cur.a, B, cur.cnt + 1}, // F(B)
			{0, cur.b, cur.cnt + 1}, // E(A)
			{cur.a, 0, cur.cnt + 1}, // E(B)
		};
		// Move(A, B)
		int move = (cur.a <= B - cur.b) ? cur.a : B - cur.b;
		next[4] = { cur.a - move, cur.b + move, cur.cnt + 1 };
		// Move(B, A)
		move = (cur.b <= A - cur.a) ? cur.b : A - cur.a;
		next[5] = { cur.a + move, cur.b - move, cur.cnt + 1 };


		for (int i = 0; i < 6; i++) {
			STATUS ndata = next[i];
			if (vis.find({ ndata.a, ndata.b }) != vis.end()) continue;
			if (ndata.a == C && ndata.b == D) return ndata.cnt;

			q.push(ndata);
			vis.insert({ ndata.a, ndata.b });
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> A >> B >> C >> D;
	cout << BFS() << "\n";
}
#endif


// unord_set에 구조체 넣고 Hash 객체 customize -> 104ms
#if 1
#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int A, B, C, D;
struct STATUS {
	int a, b, cnt;
};
queue<STATUS> q;

struct VIS {
	int a, b;
	bool operator==(const VIS &d) const {
		return ((a == d.a) && (b == d.b));
	}
};
struct MyHASH {
	size_t operator()(const VIS &d) const {
		return d.a^d.b;
	}
};
unordered_set<VIS, MyHASH> vis;


int BFS() {
	if (C == 0 && D == 0) return 0;
	if (!(C == 0 || C == A || D == 0 || D == B)) return -1;

	q.push({ 0,0,0 });
	vis.insert({ 0,0 });

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		STATUS next[6] = {
			{A, cur.b, cur.cnt + 1}, // F(A)
			{cur.a, B, cur.cnt + 1}, // F(B)
			{0, cur.b, cur.cnt + 1}, // E(A)
			{cur.a, 0, cur.cnt + 1}, // E(B)
		};
		// Move(A, B)
		int move = (cur.a <= B - cur.b) ? cur.a : B - cur.b;
		next[4] = { cur.a - move, cur.b + move, cur.cnt + 1 };
		// Move(B, A)
		move = (cur.b <= A - cur.a) ? cur.b : A - cur.a;
		next[5] = { cur.a + move, cur.b - move, cur.cnt + 1 };

		for (int i = 0; i < 6; i++) {
			STATUS ndata = next[i];
			if (vis.find({ ndata.a, ndata.b }) != vis.end()) continue;
			if (ndata.a == C && ndata.b == D) return ndata.cnt;

			q.push(ndata);
			vis.insert({ ndata.a, ndata.b });
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> A >> B >> C >> D;
	cout << BFS() << "\n";
}
#endif
