package midterm;

import java.util.PriorityQueue;
import java.util.Scanner;

public class STRJOIN {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int c = sc.nextInt();
        while (c-- > 0) {
            PriorityQueue<Integer> pq = new PriorityQueue<>();

            int n = sc.nextInt();
            for (int i = 0; i < n; i++) {
                int x = sc.nextInt();
                pq.add(x);
            }

            int ans = 0;
            while (pq.size() > 2) {
                int tmp = pq.poll() + pq.poll();
                ans += tmp;
                pq.add(tmp);
            }

            while (pq.size() > 0) {
                System.out.println(pq.poll());
            }

            System.out.println(ans);
        }
    }
}
