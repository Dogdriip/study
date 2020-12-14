package finalexam;

import java.io.*;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.StringTokenizer;

public class JOSEPHUS {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        for (int k = 2; k <= 999; k++) {
            int n = 1000;

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
            // bw.write(String.valueOf(a) + " " + String.valueOf(b) + "\n");
            if (a == 777) {
                bw.write(String.valueOf(a) + " " + String.valueOf(b) + "\n");
                bw.write(k + "\n");
                break;
            }
        }

        bw.close();
    }
}
