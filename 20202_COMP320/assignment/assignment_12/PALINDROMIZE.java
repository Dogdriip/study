/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_12;

import java.io.*;

public class PALINDROMIZE {
    static int[] fail;

    static void get_fail(int[] _fail, String _s) {
        int m = _s.length();
        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && _s.charAt(i) != _s.charAt(j)) j = _fail[j - 1];
            if (_s.charAt(i) == _s.charAt(j)) _fail[i] = ++j;
        }
    }

    static int maxOverlap(String a, String b) {
        // Get failure arr. from b
        get_fail(fail, b);

        int n = a.length(), m = b.length();
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j > 0 && a.charAt(i) != b.charAt(j)) j = fail[j - 1];
            if (a.charAt(i) == b.charAt(j)) {
                if (j == m - 1) {
                    return m;
                } else j++;
            }
        }

        return j;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            String s = br.readLine();
            String s_rev = (new StringBuffer(s)).reverse().toString();

            fail = new int[100005];

            int ans = s.length() * 2 - maxOverlap(s, s_rev);
            bw.write(String.valueOf(ans) + "\n");
        }

        bw.close();
    }
}
