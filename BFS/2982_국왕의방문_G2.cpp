/*******************************************/
// [2982] 국왕의 방문 (골드2)
// BFS + PQ - 4ms, 2892KB (솔루션 공부)
// 국왕 이동시간과 안 겹치게 조정해서 PQ에 푸쉬
/*******************************************/

#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
int A, B, K, G;
int path[1000 + 1];

struct EDGE {
	int time; // 도로 이동시간
	int flag; // -1: 도로 진입가능, 0 ~ G-1: 국왕이 i번째로 통과한 도로
};
unordered_map<int, EDGE> adj[1000 + 1];

struct LIMIT {
	int s, e; // 각 도로 통과하는 시간 구간 [s,e]
}TimeTable[1000]; 

struct STATUS {
	int n, sumt;
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		return a.sumt > b.sumt;
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;
int chk[1000 + 1]; // 각 노드에 도착한 최단시간 기록!!


void Input() {
	cin >> N >> M;
	cin >> A >> B >> K >> G;
	for (int i = 0; i < G; i++) {
		cin >> path[i];
	}
	int U, V, L;
	for (int i = 0; i < M; i++) {
		cin >> U >> V >> L;
		adj[U].insert({ V,{ L,-1 }});
		adj[V].insert({ U,{ L,-1 }});
	}
}

void MakeTimeTable() {
	int s = 0;
	for (int i = 0; i < G - 1; i++) {
		int a = path[i];
		int b = path[i + 1];
		adj[a][b].flag = i;
		adj[b][a].flag = i;

		int e = s + adj[a][b].time - 1;
		TimeTable[i] = { s,e };
		s = e + 1;
	}
}

int BFS() {
	fill(chk + 1, chk + N + 1, 0x7fffffff);
	pq.push({ A,K });
	chk[A] = K;

	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();
		if (cur.n == B) return cur.sumt - K;

		for (auto it = adj[cur.n].begin(); it != adj[cur.n].end(); it++) {
			STATUS next;
			next.n = it->first;
			int f = adj[cur.n][next.n].flag;

			// cur.sumt = cur.n과 next.n 사이 엣지에 진입하려는 시점
			// 같은 엣지를 국왕이 지나갔고, 현재 시점이 [s,e]에 포함되면 기다려야 함.
			if (f != -1 && cur.sumt >= TimeTable[f].s && cur.sumt <= TimeTable[f].e) {
				next.sumt = TimeTable[f].e + 1 + it->second.time;
			}
			else next.sumt = cur.sumt + it->second.time;

			if (next.sumt >= chk[next.n]) continue;
			pq.push(next);
			chk[next.n] = next.sumt;
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
  
	Input();
	MakeTimeTable();
	cout << BFS() << "\n";
}
