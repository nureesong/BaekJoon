/**************************************************/
// [A1] 퍼즐 (백준 1525 - 골드2)
// BFS - set으로 vis 표현
// 퍼즐판 상황을 문자열로 표현하면 성능이 느리다.
// 1) 숫자 = 4B, 문자열(9글자) = 9B 이고,
// 2) 문자열을 큐에 넣을 때 string의 부가적인 정보도 같이 저장
// 퍼즐판 상황을 9자리 숫자로 표현하면 50ms
/**************************************************/

// 문자열 - 124ms, 18020KB
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
using namespace std;

string board; // 입력 보존
string target = "123456780";
int zero;

unordered_set<string> vis;

struct STATUS {
	string b; // 퍼즐판 상황
	int z;    // 문자열 중 0의 인덱스 (빈칸 위치)
	int d;    // 이동거리
};
queue<STATUS> q;

void Input() {
	char c;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> c;
			board += c;
			if (c == '0') zero = 3*i + j;
		}
	}
}

int BFS() {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	if (board == target) return 0;

	q.push({ board, zero, 0 });
	vis.insert(board);

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		int r = cur.z / 3;
		int c = cur.z % 3;
		

		for (int i = 0; i < 4; i++) {
			string nb = cur.b;
			int nr = r + dr[i];
			int nc = c + dc[i];
			int nz = nr * 3 + nc; // 인접영역 인덱스

			if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
			
			// 인접 칸끼리 숫자 바꾸기
			char tmp = nb[nz];
			nb[cur.z] = tmp;
			nb[nz] = '0';
			//cout << cur.b << " " << nb << "\n";

			if (nb == target) return cur.d + 1;
			if (vis.find(nb) != vis.end()) continue;

			q.push({ nb,nz,cur.d + 1 });
			vis.insert(nb);
		}
	}
	
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << BFS() << "\n";
}
