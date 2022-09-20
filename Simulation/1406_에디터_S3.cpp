/************************************************/
// [1406] 에디터 (실버3)
// list<char>(s.begin(), s.end()) -> range 생성자
// 문자열 s의 모든 문자를 list의 요소로 연결한다.
/************************************************/
// 72ms
#if 1
#include <iostream>
#include <list>
#include <string>
using namespace std;

string s; // 입력 문자열 10만자리 -> 용량 크니까 전역변수!
list<char> L;
list<char>::iterator cursor;

void Solve() {
	int N;
	char c, add;

	cin >> N;
	while (N--) {
		cin >> c;
		if (c == 'L' && cursor != L.begin()) cursor--;
		else if (c == 'D' && cursor != L.end()) cursor++;
		else if (c == 'B' && cursor != L.begin()) L.erase(prev(cursor));
		else if (c == 'P'){
			cin >> add;
			L.insert(cursor, add);
		}
	}
}

void Input() {
	cin >> s;
	//for (char c : s) L.push_back(c);

	// range 생성자 이용
	L = list<char>(s.begin(), s.end());
	cursor = L.end();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
	
	for (char v : L) cout << v;
	cout << "\n";
}
#endif
