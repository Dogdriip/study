/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package Assignment_02;

import java.util.Scanner;

public class PICNIC {
    public static int solution(int n, boolean[][] friend, boolean[] matched) {
        int first = -1;
        for (int i = 0; i < n; i++) {
            if (!matched[i]) {
                first = i;
                break;
            }
        }

        if (first == -1) {  // all of them are matched
            return 1;
        }

        int ret = 0;
        for (int i = first + 1; i < n; i++) {
            if (!matched[i] && friend[i][first]) {
                matched[i] = matched[first] = true;
                ret += solution(n, friend, matched);
                matched[i] = matched[first] = false;
            }
        }

        return ret;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        for (int tc = 0; tc < c; tc++) {
            int n = sc.nextInt();
            int m = sc.nextInt();

            boolean[][] friend = new boolean[n + 1][n + 1];
            for (int i = 0; i < m; i++) {
                int u = sc.nextInt();
                int v = sc.nextInt();
                friend[u][v] = friend[v][u] = true;
            }

            boolean[] matched = new boolean[n + 1];
            int ans = solution(n, friend, matched);
            System.out.println(ans);
        }
    }
}
