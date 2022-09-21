/***********************************/
// [9367] 관리 난항 (실버2)
// undo_map<차종, CAR*> 포인터로 두면 데이터 추가시 동적 할당할 때 
// CAR 구조체 자체를 두는 것보다 더 가벼워서 빠르다.
/***********************************/
// 100.0으로 나누면서 소수점에 오차가 생기는데,
// 오차가 생긴 값에 car[cn].p를 곱하면 그 오차의 영향이 증폭된다.
// 그래서 정수 곱셈을 먼저 하고, 실수 나눗셈을 마지막에 하는 게 그나마 오차가 작다.
//iter->second.cost += (int)ceil((double)car[cn].p * (s / 100.0));
//iter->second.cost += (int)ceil((car[cn].p * s) / 100.0);
#if 0
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;

int N, M; // 자동차 종류, 사건기록 로그 수

struct CAR {
	int p, q, k; // 원가, 초기 대여비용, 주행거리 1km당 추가비용
};
unordered_map<string, CAR> car; // 차종 - 원가, 대여비, 추가비

struct LOG {
	string state;   // 대여상태(p/r, Err)
	string carname; // 차종
	int cost;       // 총 청구비용 
};
map<string, LOG> ht; // 첩보원이름 - 대여상태, 차종, 청구비용


void Solve() {
	string S, e, C; int t, d, s;

	for (int i = 0; i < M; i++) {
		cin >> t >> S >> e;
		if (e == "p") { // p는 key가 없거나, r 다음에만 올 수 있다.
			cin >> C;

			auto iter = ht.find(S);
			if (iter == ht.end()) ht.insert({ S, {e, C, car[C].q} });
			else if (iter->second.state != "r") iter->second.state = "Err";
			else {
				iter->second.state = e;
				iter->second.carname = C;
				iter->second.cost += car[C].q;
			}
		}
		else if (e == "a") { // a는 p 다음에만 올 수 있다.
			cin >> s;

			auto iter = ht.find(S);
			if (iter == ht.end()) ht.insert({ S, {"Err", "Err", -1} });
			else if (iter->second.state != "p") iter->second.state = "Err";
			else {
				string cn = iter->second.carname;

				// 아예 정수로만 계산해서 오차가 생기지 않게 하자!
				// A % 100 = 0    -> (A + 99) / 100 = A / 100     (몫 그대로)
				// A % 100 = 1~99 -> (A + 99) / 100 = A / 100 + 1 (몫 1 증가 => 소수점 올림)
				iter->second.cost += (car[cn].p * s + 99) / 100;
			}
		}
		else { // r은 p 다음에만 올 수 있다.
			cin >> d;
			
			auto iter = ht.find(S);
			if (iter == ht.end()) ht.insert({ S, {"Err", "Err", -1} });
			else if (iter->second.state != "p") iter->second.state = "Err";
			else {
				string cn = iter->second.carname;
				iter->second.state = e;
				iter->second.cost += (d * car[cn].k);
			}
		}
	}
}

void Input() {
	// Init
	car.clear();
	ht.clear();

	string name; int p, q, k;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> name >> p >> q >> k;
		car.insert({ name, {p,q,k} });
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		Input();
		Solve();

		for (auto iter = ht.begin(); iter != ht.end(); iter++) {
			cout << iter->first << " ";
			if (iter->second.state == "r") cout << iter->second.cost << "\n";
			else cout << "INCONSISTENT\n";
		}
	}
}
#endif
