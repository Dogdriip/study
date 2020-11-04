/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_06;

import java.util.Scanner;

public class ASYMTILING {
    public static int MOD = (int)1e9 + 7;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            int n = sc.nextInt();

            int[] dp = new int[n + 1];
            int[] asym = new int[n + 1];

            dp[1] = 1; dp[2] = 2;
            for (int i = 3; i <= n; i++) {
                dp[i] = (dp[i - 2] + dp[i - 1]) % MOD;
            }

            asym[1] = 1; asym[2] = 2;
            for (int i = 3; i <= n; i++) {
                if (i % 2 == 0) {
                    asym[i] = (dp[i / 2 - 1] + dp[i / 2]) % MOD;
                } else {
                    asym[i] = dp[i / 2] % MOD;
                }
            }

            System.out.println(((dp[n] + MOD) - asym[n]) % MOD);

        }
    }
}
