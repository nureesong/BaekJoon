/**********************************/
// [5585] 거스름돈 (그리디)
/*********************************/
#include <iostream>
using namespace std;

int pay;
int coin[] = { 500, 100, 50, 10, 5, 1 };

int Solve() {
	int rem = 1000 - pay; // 620
	int cnt = 0;

	for (int i = 0; i < 6; i++) {
		cnt += rem / coin[i];
		rem %= coin[i];
	}
	
	return cnt;
}

int main() {
	cin >> pay;
	cout << Solve() << "\n";
}
