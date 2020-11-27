/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_08;

import java.util.*;

public class LUNCHBOX {
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

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int c = sc.nextInt();
        while (c-- > 0) {
            int n = sc.nextInt();

            ArrayList<Pair<Integer, Integer>> p = new ArrayList<>();
            int[] m = new int[n + 1];
            int[] e = new int[n + 1];

            for (int i = 0; i < n; i++) {
                m[i] = sc.nextInt();
            }
            for (int i = 0; i < n; i++) {
                e[i] = sc.nextInt();
            }
            for (int i = 0; i < n; i++) {
                p.add(new Pair<>(m[i], e[i]));  // 돌리는 데 걸리는 시간, 먹는 데 걸리는 시간
            }
            Collections.sort(p, new Comparator<Pair<Integer, Integer>>() {
                @Override
                public int compare(Pair<Integer, Integer> o1, Pair<Integer, Integer> o2) {
                    return -o1.second().compareTo(o2.second());
                }
            });

            int ans = 0, untileat = 0;
            for (int i = 0; i < n; i++) {
                Pair<Integer, Integer> x = p.get(i);
                untileat += x.first();
                ans = Math.max(ans, untileat + x.second());
            }

            System.out.println(ans);
        }
    }
}
