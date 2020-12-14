/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_10;

import java.io.*;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.StringTokenizer;

public class ITES {
    static long prev;
    static long nxt() {
        // A[i] = (A[i-1] * 214013 + 2531011) % 2^32
        long ret = prev % 10000 + 1;
        prev = (prev * 214013 + 2531011) % (1L << 32);
        return ret;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            long k = Long.parseLong(st.nextToken());
            int n = Integer.parseInt(st.nextToken());

            long ans = 0, sum = 0;
            prev = 1983;
            Deque<Long> q = new ArrayDeque<>();
            for (int i = 0; i < n; i++) {
                long nxt = nxt();
                sum += nxt;
                q.add(nxt);

                while (sum > k) {
                    sum -= q.poll();
                }

                if (sum == k) ans++;
            }

            bw.write(String.valueOf(ans) + "\n");
        }

        bw.close();
    }
}
