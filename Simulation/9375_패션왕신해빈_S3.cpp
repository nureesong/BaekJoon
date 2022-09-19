/******************************************/
// [9375] 패션왕 신해빈 (실버3)
// unordered_map<의상 종류, 개수>  
// 의상 이름은 unique하므로 개수만 필요하다.
// 각 의상 종류별 : 0 ~ cnt개 선택 가능
// (cnt_0 + 1) * (cnt_1 + 1) * ... (cnt_2 + 1) - 1
// 1 빼는 이유: 아무것도 선택 안 하면 안 된다.
/******************************************/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int N;
unordered_map<string, int> ht; // 의상 종류 - 개수


void Input() {
	ht.clear();

	string clothtype, name;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> name >> clothtype;

		auto iter = ht.find(clothtype);
		if (iter != ht.end()) iter->second++;
		else ht.insert({ clothtype, 1 });
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
		
		int sol = 1;
		for (auto iter = ht.begin(); iter != ht.end(); iter++) {
			sol *= (iter->second + 1);
		}
		cout << sol - 1 << "\n";
	}
}
