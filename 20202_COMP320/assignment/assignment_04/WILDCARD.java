/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_04;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;

public class WILDCARD {
    public static String w, s;
    public static int[][] dp;
    public static ArrayList<String> res;

    public static int solution(int w_idx, int s_idx) {
        if (dp[w_idx][s_idx] != -1) return dp[w_idx][s_idx];

        while (s_idx < s.length() && w_idx < w.length() && (w.charAt(w_idx) == '?' || w.charAt(w_idx) == s.charAt(s_idx))) {
            w_idx++; s_idx++;
        }

        if (w_idx == w.length()) {
            return dp[w_idx][s_idx] = (s_idx == s.length() ? 1 : 0);
        }
        if (w.charAt(w_idx) == '*') {
            for (int j = 0; j + s_idx <= s.length(); j++) {
                if (solution(w_idx + 1, s_idx + j) == 1) {
                    return dp[w_idx][s_idx] = 1;
                }
            }
        }
        return dp[w_idx][s_idx] = 0;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            w = sc.next();

            int n = sc.nextInt();
            res = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                s = sc.next();
                dp = new int[101][101];

                for (int[] row : dp) Arrays.fill(row, -1);
                if (solution(0, 0) == 1) {
                    res.add(s);
                }
            }

            Collections.sort(res);
            for (String it : res) {
                System.out.println(it);
            }
        }
    }
}
