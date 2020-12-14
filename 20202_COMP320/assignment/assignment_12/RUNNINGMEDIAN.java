/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_12;

import java.io.*;
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class RUNNINGMEDIAN {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            long A = 1983;
            PriorityQueue<Long> min_heap = new PriorityQueue<>();
            PriorityQueue<Long> max_heap = new PriorityQueue<>(Collections.reverseOrder());
            long ans = 0;

            for (int i = 0; i < n; i++) {
                if (max_heap.size() > min_heap.size()) {
                    min_heap.add(A);
                } else {
                    max_heap.add(A);
                }

                if (!max_heap.isEmpty() && !min_heap.isEmpty() && max_heap.peek() > min_heap.peek()) {
                    long max_top = max_heap.poll(), min_top = min_heap.poll();
                    max_heap.add(min_top); min_heap.add(max_top);
                }

                ans += max_heap.peek();
                ans %= 20090711;

                A = (A * a + b) % 20090711;
            }

            bw.write(String.valueOf(ans) + "\n");
        }

        bw.close();
    }
}