/***************************/
// [1158] 요세푸스 문제 (실버4)
/***************************/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, K;
queue<int> q;
vector<int> sol;

void RemoveK() {
    for (int i = 0; i < K-1; i++) {
        q.push(q.front());
        q.pop();
    }
    sol.push_back(q.front());
    q.pop();
}

void Solve() {
    for (int i = 0; i < N; i++) {
        RemoveK();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        q.push(i);
    }

    Solve();

    cout << "<" << sol[0];
    for (int i = 1; i < N; i++) {
        cout << ", " << sol[i];
    }
    cout << ">\n";
}
