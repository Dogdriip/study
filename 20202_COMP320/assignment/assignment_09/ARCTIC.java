/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_09;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class ARCTIC {
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

    static int n;
    static ArrayList<Pair<Double, Double>> points;
    static int[] par;

    static double dist(Pair<Double, Double> u, Pair<Double, Double> v) {
        return Math.sqrt((u.first() - v.first()) * (u.first() - v.first()) + (u.second() - v.second()) * (u.second() - v.second()));
    }

    static int Find(int x) {
        if (par[x] < 0) return x;
        return par[x] = Find(par[x]);
    }
    static void Union(int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;
        par[x] += par[y];
        par[y] = x;
    }

    static boolean check(double x) {
        par = new int[n + 1];
        Arrays.fill(par, -1);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dist(points.get(i), points.get(j)) <= x) {
                    Union(i, j);
                }
            }
        }

        // check if all connected
        for (int i = 0; i < n; i++) {
            if (par[i] == -n) return true;
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            n = Integer.parseInt(br.readLine());
            points = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                double x = Double.parseDouble(st.nextToken());
                double y = Double.parseDouble(st.nextToken());

                points.add(new Pair<Double, Double>(x, y));
            }

            double l = -1, r = 1001;
            while (Math.abs(l - r) >= 1e-6) {
                double mid = (l + r) / 2;
                if (check(mid)) {
                    r = mid;
                } else {
                    l = mid;
                }
            }

            String res = String.format("%.2f", l);
            bw.write(res + "\n");
        }

        bw.close();
    }
}
