/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_04;

import java.util.Arrays;
import java.util.Scanner;

public class BOGGLE {
    public static char[][] ma;
    public static String s;
    public static int[][][] dp;
    public static final int[][] dir = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    public static boolean bound(int y, int x) {
        return (y >= 0 && y < 5 && x >= 0 && x < 5);
    }

    public static int solution(int y, int x, int idx) {
        if (idx == s.length() - 1) {
            return 1;
        }

        if (dp[y][x][idx] != -1) return dp[y][x][idx];

        boolean res = false;
        for (int[] d : dir) {
            int ny = y + d[0];
            int nx = x + d[1];
            if (bound(ny, nx) && ma[ny][nx] == s.charAt(idx + 1)) {
                res |= (solution(ny, nx, idx + 1) == 1);
            }
        }

        return dp[y][x][idx] = (res ? 1 : 0);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            ma = new char[5][5];

            for (int i = 0; i < 5; i++) {
                String tmp = sc.next();
                for (int j = 0; j < 5; j++) {
                    ma[i][j] = tmp.charAt(j);
                }
            }
            int n = sc.nextInt();
            for (int i = 0; i < n; i++) {
                s = sc.next();

                // initialize dp
                dp = new int[5][5][10];
                for (int[][] pl : dp) for (int[] row : pl) Arrays.fill(row, -1);

                // find start position
                boolean res = false;
                for (int y = 0; y < 5; y++) {
                    for (int x = 0; x < 5; x++) {
                        if (ma[y][x] == s.charAt(0)) {
                            res |= (solution(y, x, 0) == 1);
                        }
                    }
                }

                System.out.println(s + (res ? " YES" : " NO"));
            }
        }
    }
}
