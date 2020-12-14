#include <bits/stdc++.h>

using namespace std;

map<vector<int>, int> toSort;
map<vector<int>, vector<int>> par;

void bt(vector<int> v) {
    for (auto it : v) {
        cout << it << ' ';
    }
    cout << '\n';

    if (!par[v].empty()) {
        bt(par[v]);
    }
}

void precalc(int n)
{
    vector<int> perm(n);
    for(int i=n - 1; i >= 0; i--)
        perm[n - 1 - i] = i;

    queue<vector<int>> q;
    q.push(perm);
    toSort[perm] = 0;

    int dist = 0;
    while(!q.empty())
    {
        int size = q.size();
        dist++;
        while(size--)
        {
            vector<int> here = q.front();
            q.pop();

            for(int i=0; i < n; i++)
            {
                for(int j=i+2; j <= n; j++)
                {
                    vector<int> orig = here;
                    reverse(here.begin() + i, here.begin() + j);
                    if(toSort.count(here) == 0)
                    {
                        q.push(here);
                        toSort[here] = dist;
                        par[here] = orig;
                    }
                    reverse(here.begin() + i, here.begin() + j);
                }
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    for(int i=1; i <= 8; i++)
        precalc(i);

    int N;
    scanf("%d", &N);

    vector<int> a(N);
    for(int i=0; i < N; i++)
        scanf("%d", &a[i]);

    printf("%d\n", toSort[a]);

    bt(a);

    return 0;
}