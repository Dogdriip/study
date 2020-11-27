#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool erased[1000001];
vector<ll> prime;

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    for (int i = 2; i <= 1000001; i++) {
        if (!erased[i]) {
            prime.push_back(i);
            for (int j = i * 2; j <= 1000001; j += i) {
                erased[j] = true;
            }
        }
    }

    int n; cin >> n;
    int ans = 0;
    int mx = 0;
    while (n--) {
        int k; cin >> k;
        int orig = k;

        int cnt = 0;

        for (int i = 0; i < prime.size(); i++) {
            if (k == 1) break;
            if (prime[i] * prime[i] > orig) {
                cout << k;
                cnt++;
                break;
            }
            while (k % prime[i] == 0) {
                k /= prime[i];
                cout << prime[i] << ' ';
                cnt++;
            }
        }
        cout << '\n';

        if (cnt == 1) ans++;
        if (mx <= cnt) {
            mx = cnt;
            cout << "**" << cnt << "**" << orig << '\n';
        }
    }
    cout << ans << '\n';
    cout << mx << '\n';

    return 0;
}