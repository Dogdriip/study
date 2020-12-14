package finalexam;

import java.io.*;
import java.util.*;

public class ITES {
    static long prev;
    static long seed = 1983, a = 1273, b = 4936;
    static long nxt() {
        long ret = seed;
        seed = ((seed * a) + b) % 20090711;

        return ret;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        // StringTokenizer st = new StringTokenizer(br.readLine());
        // long k = Long.parseLong(st.nextToken());
        // int n = Integer.parseInt(st.nextToken());

        PriorityQueue<Long> min_heap = new PriorityQueue<>();
        PriorityQueue<Long> max_heap = new PriorityQueue<>(Collections.reverseOrder());

        long k = 92276042;

        ArrayList<Long> records = new ArrayList<>();

        long ans = 0, sum = 0;
        prev = 1983;
        Deque<Long> q = new ArrayDeque<>();
        while (true) {
            long nxt = nxt();
            sum += nxt;
            q.add(nxt);
            records.add(nxt);

            if (max_heap.size() > min_heap.size()) {
                min_heap.add(nxt);
            } else {
                max_heap.add(nxt);
            }

            if (!max_heap.isEmpty() && !min_heap.isEmpty() && max_heap.peek() > min_heap.peek()) {
                long max_top = max_heap.poll(), min_top = min_heap.poll();
                max_heap.add(min_top); min_heap.add(max_top);
            }

            while (sum > k) {
                sum -= q.poll();
            }

            if (sum == k) {
                ans++;
                System.out.println("found");
                System.out.println(max_heap.peek());
                break;
            }
        }

        Collections.sort(records);
        for (int i = 0; i < records.size(); i++) {
            if (records.get(i) > 10053166) {
                System.out.println(records.get(i));
                break;
            }
        }

        bw.write(String.valueOf(ans) + "\n");

        bw.close();
    }
}
