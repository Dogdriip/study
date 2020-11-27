/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_08;

import java.util.*;
import java.io.*;

public class BOARDCOVER2 {
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

    static int h, w, r, c;
    static char[][] ma;
    static ArrayList<ArrayList<Pair<Integer, Integer>>> _blocks;
    static ArrayList<ArrayList<Pair<Integer, Integer>>> blocks;
    static int block_sz;

    static int mx_cnt;
    static int empty_cnt;
    static int[][] covered;

    static boolean fill(int y, int x, ArrayList<Pair<Integer, Integer>> block, int d) {
        boolean res = true;
        for (Pair<Integer, Integer> cell : block) {
            int ny = y + cell.first(), nx = x + cell.second();
            if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
                covered[ny][nx] += d;
                res = res && (covered[ny][nx] == 1);
            } else {
                res = false;
            }
        }
        return res;
    }

    static boolean promise(int placed) {
        return ((empty_cnt / block_sz) + placed <= mx_cnt);
    }

    static void bf(int placed) {
        // promising
        if (promise(placed)) return;

        // find LU empty pos
        int y = -1, x = -1;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (covered[i][j] == 0) {
                    y = i;
                    x = j;
                    break;
                }
            }
            if (y != -1) break;
        }

        if (y == -1) {  // base case: if filled all
            mx_cnt = Math.max(mx_cnt, placed);
            return;
        }

        // try to fill with block
        for (ArrayList<Pair<Integer, Integer>> block : blocks) {
            if (fill(y, x, block, 1)) {  // block can be placed and filled
                empty_cnt -= block_sz;
                bf(placed + 1);
                empty_cnt += block_sz;
            }
            fill(y, x, block, -1);  // unfill
        }

        // try not to fill with block
        covered[y][x] = 1;
        empty_cnt--;
        bf(placed);
        covered[y][x] = 0;
        empty_cnt++;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            h = Integer.parseInt(st.nextToken());
            w = Integer.parseInt(st.nextToken());
            r = Integer.parseInt(st.nextToken());
            c = Integer.parseInt(st.nextToken());

            ma = new char[h + 1][w + 1];
            for (int i = 0; i < h; i++) {
                String tmp = br.readLine();
                for (int j = 0; j < w; j++) {
                    ma[i][j] = tmp.charAt(j);
                }
            }

            char[][] block = new char[r + 1][c + 1];
            block_sz = 0;
            for (int i = 0; i < r; i++) {
                String tmp = br.readLine();
                for (int j = 0; j < c; j++) {
                    block[i][j] = tmp.charAt(j);
                    if (block[i][j] == '#') {
                        block_sz++;
                    }
                }
            }

            // generate rotated blocks (4)
            ArrayList<Pair<Integer, Integer>> deg0 = new ArrayList<>();
            ArrayList<Pair<Integer, Integer>> deg90 = new ArrayList<>();
            ArrayList<Pair<Integer, Integer>> deg180 = new ArrayList<>();
            ArrayList<Pair<Integer, Integer>> deg270 = new ArrayList<>();
            int oy, ox;

            // deg0
            oy = -1; ox = -1;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (block[i][j] == '#') {
                        if (oy == -1) {  // origin found
                            oy = i; ox = j;
                        }
                        deg0.add(new Pair<>(i - oy, j - ox));
                    }
                }
            }
            // deg90
            oy = -1; ox = -1;
            for (int j = 0; j < c; j++) {
                for (int i = r - 1; i >= 0; i--) {
                    if (block[i][j] == '#') {
                        if (oy == -1) {  // origin found
                            oy = j; ox = i;
                        }
                        deg90.add(new Pair<>(j - oy, -(i - ox)));
                    }
                }
            }
            // deg180
            oy = -1; ox = -1;
            for (int i = r - 1; i >= 0; i--) {
                for (int j = c - 1; j >= 0; j--) {
                    if (block[i][j] == '#') {
                        if (oy == -1) {  // origin found
                            oy = i; ox = j;
                        }
                        deg180.add(new Pair<>(-(i - oy), -(j - ox)));
                    }
                }
            }
            // deg270
            oy = -1; ox = -1;
            for (int j = c - 1; j >= 0; j--) {
                for (int i = 0; i < r; i++) {
                    if (block[i][j] == '#') {
                        if (oy == -1) {  // origin found
                            oy = j; ox = i;
                        }
                        deg270.add(new Pair<>(-(j - oy), i - ox));
                    }
                }
            }

            // remove duplicates from blocks
            _blocks = new ArrayList<>(new ArrayList<>());  // temp
            _blocks.add(deg0);
            _blocks.add(deg90);
            _blocks.add(deg180);
            _blocks.add(deg270);

            blocks = new ArrayList<>(new ArrayList<>());

            for (int i = 0; i < 4; i++) {
                boolean dup = false;
                for (int j = i + 1; j < 4; j++) {
                    ArrayList<Pair<Integer, Integer>> u = _blocks.get(i);
                    ArrayList<Pair<Integer, Integer>> v = _blocks.get(j);

                    boolean alleq = true;
                    for (int k = 0; k < u.size(); k++) {
                        if ((!u.get(k).first().equals(v.get(k).first())) || (!u.get(k).second().equals(v.get(k).second()))) {
                            alleq = false;
                            break;
                        }
                    }

                    if (alleq) {
                        dup = true;
                        break;
                    }
                }

                if (!dup) {
                    blocks.add(_blocks.get(i));
                }
            }

            // solve
            mx_cnt = 0;  // 가장 많이 놓은 블럭 수
            empty_cnt = 0;  // 빈 개수 (promising에 사용)
            covered = new int[h + 1][w + 1];
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (ma[i][j] == '#') {
                        covered[i][j] = 1;
                    } else {
                        covered[i][j] = 0;
                        empty_cnt++;
                    }
                }
            }
            bf(0);
            bw.write(String.valueOf(mx_cnt));
            bw.write('\n');

        }

        bw.close();
    }
}
