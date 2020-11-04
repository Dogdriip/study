/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_06;

import java.util.Arrays;
import java.util.Scanner;

public class POLY {
    public static final int MOD = 10000000;
    public static int[][] dp;

    public static int solution(int x, int up) {
        if (x == up) return 1;

        if (dp[x][up] != -1) return dp[x][up];
        int res = 0;
        for (int down = 1; down <= x - up; down++) {
            res += (solution(x - up, down) % MOD) * (up + down - 1);
            res %= MOD;
        }

        return dp[x][up] = res;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            int n = sc.nextInt();
            dp = new int[n + 1][n + 1];
            for (int i = 0; i <= n; i++) {
                Arrays.fill(dp[i], -1);
            }

            int ans = 0;
            for (int i = 1; i <= n; i++) {
                ans += solution(n, i);
                ans %= MOD;
            }
            System.out.println(ans);
        }
    }
}
