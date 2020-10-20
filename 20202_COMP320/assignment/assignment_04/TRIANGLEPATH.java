/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_04;

import java.util.Arrays;
import java.util.Scanner;

public class TRIANGLEPATH {
    public static int n;
    public static int[][] ma;
    public static int[][] dp;

    public static int solution(int y, int x) {
        if (y == n - 1) return ma[y][x];

        if (dp[y][x] != -1) return dp[y][x];
        return dp[y][x] = Math.max(solution(y + 1, x), solution(y + 1, x + 1)) + ma[y][x];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            n = sc.nextInt();
            ma = new int[n + 1][n + 1];
            dp = new int[n + 1][n + 1];
            for (int[] row : dp) Arrays.fill(row, -1);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j <= i; j++) {
                    ma[i][j] = sc.nextInt();
                }
            }

            System.out.println(solution(0, 0));
        }
    }
}
