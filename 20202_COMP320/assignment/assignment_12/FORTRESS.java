/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_12;

import java.io.*;
import java.util.*;

public class FORTRESS {

    static class Pair<T1, T2> {
        T1 x;
        T2 y;
        public Pair(T1 x, T2 y) {
            this.x = x;
            this.y = y;
        }
        public T1 first() { return x; }
        public T2 second() { return y; }
    }
    static class Tuple<T1, T2, T3> {
        T1 x;
        T2 y;
        T3 z;
        public Tuple(T1 x, T2 y, T3 z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        public T1 first() { return x; }
        public T2 second() { return y; }
        public T3 third() { return z; }
    }

    static int n;
    static ArrayList<Tuple<Integer, Integer, Integer>> circles;
    static ArrayList<ArrayList<Integer>> adj;
    static boolean[] visited;
    static int rt;  // root
    static int mx_dist;

    static void dfs(int x, int p, int d) {
        if (mx_dist < d) {
            mx_dist = d;
            rt = x;
        }
        for (int nx : adj.get(x)) {
            if (nx != p) {
                dfs(nx, x, d + 1);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            n = Integer.parseInt(br.readLine());

            circles = new ArrayList<>();
            adj = new ArrayList<>();
            for (int i = 0; i < 10001; i++) {
                adj.add(new ArrayList<>());
            }
            visited = new boolean[10001];
            mx_dist = 0;

            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                int x = Integer.parseInt(st.nextToken());
                int y = Integer.parseInt(st.nextToken());
                int r = Integer.parseInt(st.nextToken());

                circles.add(new Tuple<>(x, y, r));
            }

            // sort circles
            Collections.sort(circles, new Comparator<Tuple<Integer, Integer, Integer>>() {
                @Override
                public int compare(Tuple<Integer, Integer, Integer> o1, Tuple<Integer, Integer, Integer> o2) {
                    return o1.third().compareTo(o2.third());
                }
            });

            // configure tree
            for (int i = 0; i < n - 1; i++) {
                for (int j = i + 1; j < n; j++) {
                    int ux = circles.get(i).first();
                    int uy = circles.get(i).second();
                    int ur = circles.get(i).third();
                    int vx = circles.get(j).first();
                    int vy = circles.get(j).second();
                    int vr = circles.get(j).third();

                    if ((vx - ux) * (vx - ux) + (vy - uy) * (vy - uy) <= (vr - ur) * (vr - ur)) {
                        adj.get(i).add(j);
                        adj.get(j).add(i);
                        break;
                    }
                }
            }

            // get diameter of tree
            dfs(0, -1, 0);
            dfs(rt, -1, 0);

            bw.write(mx_dist + "\n");
        }

        bw.close();
    }
}