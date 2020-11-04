/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_06;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class NUMB3RS {
    static int n, d, p;
    static ArrayList<Integer>[] adj;
    static double[][] dp;

    static double solution(int day, int x) {
        if (day == 0) return (x == p ? 1 : 0);

        if (dp[day][x] != -1) return dp[day][x];
        double res = 0;
        for (int i = 0; i < adj[x].size(); i++) {
            int nx = adj[x].get(i);
            res += solution(day - 1, nx) / adj[nx].size();
        }

        return dp[day][x] = res;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            n = sc.nextInt();
            d = sc.nextInt();
            p = sc.nextInt();

            adj = new ArrayList[n + 1];
            for (int i = 0; i < n; i++) {
                adj[i] = new ArrayList<>();
            }
            dp = new double[d + 1][n + 1]; // day, currnode
            for (int i = 0; i <= d; i++) {
                Arrays.fill(dp[i], -1);
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (sc.nextInt() == 1) {
                        adj[i].add(j);
                        adj[j].add(i);
                    };
                }
            }

            int t = sc.nextInt();
            while (t-- > 0) {
                int x = sc.nextInt();
                System.out.print(solution(d, x) + " ");
            }
            System.out.println();
        }
    }
}
