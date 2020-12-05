/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_09;

import java.io.*;
import java.util.StringTokenizer;

public class MODPOWER {
    static int modPower(int n, int m, int k) {  // (m^k) % n
        int res = 1;

        m %= n;
        if (m == 0) {
            return 0;
        }

        for (int i = 0; i < 31; i++) {
            if ((k & (1 << i)) != 0) {
                res = (res * m) % n;
            }
            m = (m * m) % n;
        }

        return res;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());

        bw.write(String.valueOf(modPower(n, m, k)) + "\n");  // (m^k) % n
        bw.close();
    }
}
