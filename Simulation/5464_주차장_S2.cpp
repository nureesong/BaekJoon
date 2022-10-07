/************************************/
// [5464] 주차장 (실버2)
// 기억하자!! 우큐 디폴트는 내림차순....
/************************************/

#include <iostream>
#include <queue>
using namespace std;

int N, M, M2;
int fee[100 + 1]; // 각 주차공간 별 단위무게 당 요금
int order[4000]; // 차량 출입순서 (2M개)

struct CAR {
	int n, w; // i번 차량이 주차한 공간 번호, 차량 무게
}C[2000 + 1];

queue<int> q; // 대기 차량 저장공간
priority_queue<int, vector<int>, greater<int>> pq; // 비어있는 주차공간 번호 (오름차순)

void Input() {
	cin >> N >> M;
	M2 = M * 2;
	for (int i = 1; i <= N; i++) {
		cin >> fee[i];
		pq.push(i);
	}
	for (int i = 1; i <= M; i++) {
		cin >> C[i].w;
	}
	for (int i = 0; i < M2; i++) {
		cin >> order[i];
	}
}

int Solve() {
	int sumfee = 0;

	for (int i = 0; i < M2; i++) {
		int n = order[i];

		if (n > 0) {
			// 주차공간이 남아있으면 주차
			if (!pq.empty()) {
				int p = pq.top(); pq.pop();
				C[n].n = p;
				sumfee += C[n].w * fee[p];
			}
			else { // 빈 공간 없으면 대기
				q.push(n);
			}
		}
		else {
			n = -n; // 음수에서 양수로!
			int p = C[n].n; // n번 차량이 쓰던 주차공간
			pq.push(p);     // 빈 공간 됐으니까 푸시

			// 대기 중인 차량 있으면 배정
			if (!q.empty()) {
				int wait = q.front(); q.pop();
				C[wait].n = pq.top();
				sumfee += C[wait].w * fee[pq.top()];
				pq.pop();
			}
		}
	}
	return sumfee;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
