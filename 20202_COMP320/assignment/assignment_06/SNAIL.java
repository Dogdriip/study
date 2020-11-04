/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_06;

import java.util.Arrays;
import java.util.Scanner;

public class SNAIL {
    public static double[][] dp;
    public static int n, m;

    public static double solution(int day, int climbed) {
        if (day == m) return (climbed >= n ? 1 : 0);

        if (dp[day][climbed] != -1) return dp[day][climbed];
        return dp[day][climbed] = 0.75 * solution(day + 1, climbed + 2) + 0.25 * solution(day + 1, climbed + 1);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            n = sc.nextInt();
            m = sc.nextInt();
            dp = new double[m + 1][2 * n + 1];  // day, climbed
            for (int i = 0; i <= m; i++) {
                Arrays.fill(dp[i], -1);
            }

            System.out.println(solution(0, 0));
        }
    }
}
