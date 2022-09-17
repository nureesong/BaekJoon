/*******************************************/
// [15661] 링크와 스타트 (골드5)
// 팀원 번호: 1 ~ N, 팀 번호: 0 - 스타트, 1 - 링크
// 1번 선수는 항상 0번(스타트)팀에 고정시키고 
// 2 ~ N번 선수가 팀을 선택하는 경우의 수만 고려한다.
// 각 팀에 팀원이 추가될 때마다 기존 팀원들과의 능력치 합산한다.
// 20ms: N번까지 전부 선택한 후 양팀이 1명 이상인지 확인
// 16ms: 한 팀이라도 N-1명이면 인원 꽉 찼으므로 패스
// 8ms : 가지치기 (mindiff = 0이 되면 가장 최솟값이므로 탐색 중단)
/********************************************/

// 가지치기 추가 - DFS 리턴값 주기
#if 1
#include <iostream>
#include <vector>
using namespace std;

int N;
int S[20 + 2][20 + 2];
int mindiff = 0x7fffffff;

// 0: 스타트 팀, 1: 링크 팀
vector<int> team[2]; // 확정된 팀원 번호 저장
int power[2];        // 확정된 팀원들로 계산된 능력치 저장

int AddPower(int n, int i) {
    int sum = 0;
    for (auto m : team[i]) {
        sum += S[n][m] + S[m][n];
    }
    return sum;
}

// n번 선수 팀 배정하는 2가지 경우 탐색
int DFS(int n) {
    // 가지치기 - 한 번이라도 두 팀의 능력치가 같았다면 최솟값이 0이므로 탐색 중단
    if (mindiff == 0) return 1;

    // 2 ~ N번 사원 전부 팀 배정 완료
    if (n > N) {
        int diff = abs(power[0] - power[1]);
        if (diff < mindiff) mindiff = diff;
        return 0;
    }

    for (int i = 0; i < 2; i++) {
        // 각 팀에 1명 이상이어야 하므로 (N-1)명이면 그 팀은 꽉 찬 상태
        if (team[i].size() == N-1) continue;

        // n번 선수가 i번 팀을 선택했을 때 기존 팀원들과의 능력치 합산
        int add = AddPower(n, i);
        power[i] += add;
        team[i].push_back(n);
        if (DFS(n + 1)) return 1;

        team[i].pop_back(); // 복원
        power[i] -= add;
    }
    return false;
}

void Input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> S[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    
    team[0].push_back(1);
    DFS(2);

    cout << mindiff << "\n";
    return 0;
}
#endif


// 가지치기X - 리턴값이 없는 DFS
#if 0
void DFS(int n) {
    // 가지치기 - 한 번이라도 두 팀의 능력치가 같았다면 최솟값이 0이므로 탐색 중단
    //if (mindiff == 0) return;

    // 2 ~ N번 사원 전부 팀 배정 완료
    if (n > N) {
        //if (team[1].size() < 1) return; // 각 팀에 1명 이상 있어야 함
        
        // 양 팀 모두 1명 이상 있다면 두 팀의 능력치 차이가 최소인지 확인
        int diff = abs(power[0] - power[1]);
        if (diff < mindiff) mindiff = diff;
        return;
    }

    for (int i = 0; i < 2; i++) {
        // 각 팀에 1명 이상이어야 하므로 (N-1)명이면 그 팀은 꽉 찬 상태
        if (team[i].size() == N-1) continue;

        // n번 선수가 i번 팀을 선택했을 때 기존 팀원들과의 능력치 합산
        int add = AddPower(n, i);
        power[i] += add;
        team[i].push_back(n);
        DFS(n + 1);
        team[i].pop_back(); // 복원
        power[i] -= add;
    }
}
#endif
