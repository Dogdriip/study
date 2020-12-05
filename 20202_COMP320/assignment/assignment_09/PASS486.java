/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_09;

import java.io.*;
import java.util.StringTokenizer;

public class PASS486 {
    static int[] erased = new int[10000001];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        for (int i = 1; i <= 10000000; i++) {
            for (int j = i; j <= 10000000; j += i) {
                erased[j]++;
            }
        }

        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int lo = Integer.parseInt(st.nextToken());
            int hi = Integer.parseInt(st.nextToken());

            int ans = 0;
            for (int x = lo; x <= hi; x++) {
                if (erased[x] == n) ans++;
            }

            bw.write(String.valueOf(ans) + "\n");
        }

        bw.close();
    }
}
