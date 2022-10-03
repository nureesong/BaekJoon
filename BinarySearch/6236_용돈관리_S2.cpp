/**********************************/
// [6236] 용돈 관리 (실버2)
// Parametric Search - 12ms, 2412KB
/**********************************/

#include <iostream>
using namespace std;

int N, M;
int arr[100000];

void Input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
}

int Check(int k) {
    int cur = 0;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (cur < arr[i]) {
            cnt++;
            if (cnt > M) return 0;

            cur = k - arr[i];
            if (cur < 0) return 0;
        }
        else cur -= arr[i];        
    }
    return 1;
}

int BS(int s, int e) {
    int m, sol = -1;

    while (s <= e) {
        m = (s + e) / 2;
        if (Check(m)) {
            sol = m;
            e = m - 1;
        }
        else s = m + 1;
    }
    return sol;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << BS(0, 1000000000) << "\n";
}
