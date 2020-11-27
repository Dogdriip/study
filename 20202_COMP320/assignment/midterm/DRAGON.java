package midterm;

import java.util.Scanner;

public class DRAGON {
    static long[] dp = new long[101];  // dp[i] := i세대 curve의 길이

    static char solution(String curve, int gen, int skip) {
        if (gen == 0) return curve.charAt(skip);

        for (int i = 0; i < curve.length(); i++) {
            if (curve.charAt(i) == 'X' || curve.charAt(i) == 'Y') {  // can be replaced
                if (skip >= dp[gen]) {  // if also can be skipped, skip it
                    skip -= dp[gen];
                } else if (curve.charAt(i) == 'X') {  // replace X
                    return solution("XF+YF", gen - 1, skip);
                } else {  // replace X
                    return solution("FX-FY", gen - 1, skip);
                }
            } else if (skip > 0) {  // ignore
                skip--;
            } else {  // found answer
                return curve.charAt(i);
            }
        }

        return '0';
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // configure dp[]
        dp[0] = 1;
        for (int i = 1; i <= 100; i++) {
            dp[i] = dp[i - 1] * 2 + 2;
        }

        int c = sc.nextInt();
        while (c-- > 0) {
            int n = sc.nextInt();
            int p = sc.nextInt();
            int l = sc.nextInt();

            for (int i = p - 1; i < p + l - 1; i++) {
                System.out.print(solution("FX", n, i));
            }
            System.out.println();
        }
    }
}
