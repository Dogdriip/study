/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package Assignment_01;

import java.util.Scanner;

public class FESTIVAL {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        for (int tc = 0; tc < c; tc++) {
            int n = sc.nextInt(), l = sc.nextInt();
            int[] cost = new int[n + 1];
            int[] psum = new int[n + 1];

            for (int i = 1; i <= n; i++) {
                cost[i] = sc.nextInt();
                psum[i] = psum[i - 1] + cost[i];
            }

            double ans = Double.MAX_VALUE;
            for (int i = 0; i <= n; i++) {
                for (int j = i + 1; j <= n; j++) {
                    if (j - i < l) continue;
                    double val = (double)(psum[j] - psum[i]) / (j - i);
                    ans = Math.min(ans, val);
                }
            }

            System.out.println(ans);
        }
    }
}
