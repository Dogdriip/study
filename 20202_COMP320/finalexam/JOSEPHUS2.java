package finalexam;

import java.io.*;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.StringTokenizer;

public class JOSEPHUS2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int n = 1000, k = 7, m = 10;

        int[] group = new int[]{413, 977, 541, 230, 627, 751, 712, 160, 824, 731};  // size of m=10
        boolean[] dead = new boolean[]{false, false, false, false, false, false, false, false, false, false};
        int alive_n = 10;
        int notgroup_n = 990;

        Deque<Integer> q = new ArrayDeque<>();
        for (int i = 1; i <= n; i++) {
            q.add(i);
        }

        while (q.size() > 2) {
            int x = q.poll();  // dead person

            bw.write(String.valueOf(x) + " dead ");

            // check if he is in group
            boolean deadingroup = false;
            for (int i = 0; i < 10; i++) {
                if (x == group[i]) {
                    dead[i] = true;
                    deadingroup = true;
                    break;
                }
            }
            if (deadingroup) {
                alive_n--;
            } else {
                notgroup_n--;
            }

            bw.write(alive_n + " " + notgroup_n + "\n");

            if (alive_n > notgroup_n) {
                for (int i = 0; i < 10; i++) {
                    bw.write(String.valueOf(dead[i]) + " ");
                }
                bw.write("\n");
                break;
            }

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

        bw.close();
    }
}
