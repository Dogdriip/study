/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_12;

import java.io.*;
import java.util.*;

public class INSERTION {

    static int[] a;
    static int[] ans;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            int n = Integer.parseInt(br.readLine());
            a = new int[n + 1];
            ans = new int[n + 1];

            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= n; i++) {
                a[i] = Integer.parseInt(st.nextToken());
            }

            for (int i = 1; i <= n; i++) {
                ans[i] = i;
            }
            for (int i = n; i >= 1; i--) {
                int tmp = ans[i - a[i]];
                for (int j = i - a[i]; j < i; j++) {
                    ans[j] = ans[j + 1];
                }
                ans[i] = tmp;
            }

            for (int i = 1; i <= n; i++) {
                bw.write(ans[i] + " ");
            }
            bw.write("\n");

        }

        bw.close();
    }

}
