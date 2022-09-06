/****************************************************************/
// [12886] 돌 그룹 - 골드4
// 힌트: 세수의 합은 항상 일정하므로 두 수만 있으면 중복방문 확인 가능
//       세 수를 항상 정렬하고 가장 작은수, 중간 수 두 개만 확인한다
/****************************************************************/
#if 0
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int A, B, C;
bool vis[1500 + 10][1500 + 10];  // i: 가장 작은 수, j: 중간 수

struct STATUS {
	int s[3]; // x,y,z
};


int BFS() {
	if (A == B && A == C) return 1;
	STATUS start = { {A,B,C} };
	sort(start.s, start.s + 3);  
	
	queue<STATUS> q;
	q.push(start);  // 큐에는 항상 정렬해서 넣기!!
	vis[start.s[0]][start.s[1]] = true;
	
	while (!q.empty()) {
		STATUS cur = q.front();
		q.pop();

		int x = cur.s[0];
		int y = cur.s[1];
		int comb[3][3] = { {x, -x, 0},{x, 0, -x},{0, y, -y} };

		for (int i = 0; i < 3; i++) {
			int nx = cur.s[0] + comb[i][0];
			int ny = cur.s[1] + comb[i][1];
			int nz = cur.s[2] + comb[i][2];

			STATUS next = { {nx,ny,nz} };
			sort(next.s, next.s + 3);
			
			if (next.s[0] == next.s[1] && next.s[1] == next.s[2]) return 1;
			if (vis[next.s[0]][next.s[1]]) continue;

			q.push(next);
			vis[next.s[0]][next.s[1]] = true;
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin >> A >> B >> C;
	int sum = A + B + C;

	if (sum % 3) { // 세 수의 합이 3배수가 아니면 무조건 불가능
		cout << "0\n";
	}
	else {
		cout << BFS() << "\n";
	}
}
#endif
