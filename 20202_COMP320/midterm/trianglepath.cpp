#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int ma[101][101];
int memo[101][101];  // solution(y, x)의 메모값 (-1:저장 안됨, 0: 안됨, 1: 됨)
pii parent[101][101];
int n;

int solution(int y, int x) {  // solution(y, x) : (y, x)에서 ma[y][x]만큼 오른쪽이나 밑으로 뛸 수 있는가?
    if (y >= n || x >= n) {
        return 0;
    }
    if (y == n - 1 && x == n - 1) {
        return 1;
    }

    int& ret = memo[y][x];

    if (ret != -1) {
        return ret;
    }

    int res1 = solution(y, x + ma[y][x]);  // 오른쪽
    int res2 = solution(y + ma[y][x], x);  // 밑
    if (res1) {
        parent[y][x] = {y, x + ma[y][x]};
        return ret = res1;
    } else if (res2) {
        parent[y][x] = {y + ma[y][x], x};
        return ret = res2;
    } else {
        return 0;
    }

    // return ret = solution(y, x + ma[y][x]) || solution(y + ma[y][x], x);

}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int c; cin >> c;
    while (c--) {
        memset(ma, 0, sizeof(ma));
        memset(memo, -1, sizeof(memo));
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> ma[i][j];
            }
        }

        cout << (solution(0, 0) ? "YES\n" : "NO\n");

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << '(' << parent[i][j].first << ' ' << parent[i][j].second << ") ";
            }
            cout << "\n";
        }

        // bt(0, 0);

    }

    return 0;
}