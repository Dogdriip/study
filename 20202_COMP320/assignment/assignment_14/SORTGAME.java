/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_14;

import java.io.*;
import java.util.*;

public class SORTGAME {

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

    static ArrayList<Integer> v = new ArrayList<>();
    static boolean[] visited = new boolean[9];
    static Map<ArrayList<Integer>, Integer> dp = new HashMap<>();

    static void precalc() {
        ArrayList<Integer> v = new ArrayList<>();
        for (int i = 1; i <= 8; i++) v.add(i);

        ArrayDeque<Pair<ArrayList<Integer>, Integer>> q = new ArrayDeque<>();
        dp.put(v, 0);
        q.add(new Pair<>(v, 0));
        while (!q.isEmpty()) {
            Pair<ArrayList<Integer>, Integer> curr = q.poll();
            ArrayList<Integer> x = curr.first();
            int step = curr.second();

            for (int i = 0; i < 8; i++) {
                for (int j = i + 1; j < 8; j++) {
                    for (int k = i; k <= (i + j) / 2; k++) {
                        Collections.swap(x, k, j - k + i);
                    }

                    ArrayList<Integer> tmp = new ArrayList<>(x);

                    if (!dp.containsKey(tmp)) {
                        dp.put(tmp, step + 1);
                        q.add(new Pair<>(tmp, step + 1));
                    }

                    for (int k = i; k <= (i + j) / 2; k++) {
                        Collections.swap(x, k, j - k + i);
                    }

                }
            }

        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        precalc();

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            int n = Integer.parseInt(br.readLine());

            ArrayList<Integer> a = new ArrayList<>();

            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                int x = Integer.parseInt(st.nextToken());
                a.add(x);
            }
            for (int i = n; i < 8; i++) {
                a.add(i + 1);
            }

            ArrayList<Integer> perm = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                int small = 1;
                for (int j = 0; j < n; j++) {
                    if (a.get(i) > a.get(j)) {
                        small++;
                    }
                }
                perm.add(small);
            }
            for (int i = n + 1; i <= 8; i++) {
                perm.add(i);
            }

            bw.write(dp.get(perm) + "\n");

        }

        bw.close();
    }

}
