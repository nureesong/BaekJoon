#include <iostream>
#include <algorithm>
using namespace std;

int N;
double F[100000 + 10];

void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> F[i];
    }    
}

int BS_lower(int s, int e, double t) {
    // lb : t 이상인 값 중 최소 인덱스
    int lb = -1;
    while (s <= e) {
        int m = (s + e) / 2;

        if (F[m] >= t) {
            lb = m;
            e = m - 1;
        }
        else s = m + 1;
    }
    return lb;
}

long long Solve() {
    // 최대 cnt : NC2 = 약 10^5 * 10^5 / 2 = 5 * 10^9 = 50억
    long long cnt = 0;
    sort(F, F+N);

    for (int i = N-1; i > 0; i--) {
        // Lower bound = F[i] * 0.9
        int lb = BS_lower(0, i-1, 0.9 * F[i]);
        
        if (lb != -1) cnt += i - lb;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << Solve() << "\n";
}
