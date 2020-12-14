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

public class JOSEPHUS {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());

            Deque<Integer> q = new ArrayDeque<>();
            for (int i = 1; i <= n; i++) {
                q.add(i);
            }

            while (q.size() > 2) {
                q.poll();

                for (int i = 0; i < k - 1; i++) {
                    q.add(q.peek()); q.poll();
                }
            }

            int a = q.poll();
            int b = q.poll();
            if (a > b) {
                int t = a;
                a = b;
                b = t;
            }
            bw.write(String.valueOf(a) + " " + String.valueOf(b) + "\n");
        }

        bw.close();
    }
}
