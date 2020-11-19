/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_07;

import java.util.*;

class Pair<T> {
    T x, y;
    public Pair(T x, T y) {
        this.x = x;
        this.y = y;
    }
    public T first() {
        return x;
    }
    public T second() {
        return y;
    }
}

public class KLIS {
    static int n, k;
    // dp[i] := i에서 시작하는 lis의 최대 길이
    // cnt[i] := i에서 시작하는 lis의 개수
    static long[] a, dp, cnt;
    static final long MAX = (1L << 31) - 1;

    static void reconstruct(int x, int skip, ArrayList<Long> res) {
        if (x != -1) res.add(a[x]);

        if (lis(x) == 1) return;

        ArrayList<Pair<Long>> candidate = new ArrayList<>();
        for (int i = x + 1; i < n; i++) {
            if ((x == -1 || a[x] < a[i]) && lis(x) == 1 + lis(i)) {
                candidate.add(new Pair<>(a[i], (long)i));
            }
        }

        Collections.sort(candidate, new Comparator<Pair<Long>>() {
            @Override
            public int compare(Pair<Long> o1, Pair<Long> o2) {
                return o1.first().compareTo(o2.first());
            }
        });

        for (int i = 0; i < candidate.size(); i++) {
            long idx = candidate.get(i).second();
            long cnt = lis_cnt((int)idx);
            if (cnt <= skip) {
                skip -= cnt;
            } else {
                reconstruct((int)idx, skip, res);
                break;
            }
        }
    }

    static long lis_cnt(int x) {  // x에서 시작하는 lis의 개수
        if (lis(x) == 1) return 1;

        if (cnt[x + 1] != -1) return cnt[x + 1];

        long res = 0;
        for (int i = x + 1; i < n; i++) {
            if ((x == -1 || a[x] < a[i]) && lis(x) == 1 + lis(i)) {
                res = Math.min(MAX, res + lis_cnt(i));
            }
        }
        return cnt[x + 1] = res;
    }

    static long lis(int x) {  // x에서 시작하는 lis의 최대 길이
        if (dp[x + 1] != -1) return dp[x + 1];

        long res = 1;
        for (int i = x + 1; i < n; i++) {
            if (x == -1 || a[x] < a[i]) {
                res = Math.max(res, 1 + lis(i));
            }
        }
        return dp[x + 1] = res;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            n = sc.nextInt();
            k = sc.nextInt();

            a = new long[n + 1];
            dp = new long[n + 1];
            Arrays.fill(dp, -1);
            cnt = new long[n + 1];
            Arrays.fill(cnt, -1);

            for (int i = 0; i < n; i++) {
                a[i] = sc.nextInt();
            }

            ArrayList<Long> ans = new ArrayList<>();
            reconstruct(-1, k - 1, ans);

            System.out.println(ans.size());
            for (long it : ans) {
                System.out.print(it + " ");
            }
            System.out.println();
        }
    }
}

