/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_13;

import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class MatrixArea {

    static int l;
    static int[][] ma;
    static boolean[][] visited;
    static int[] dy = {0, 0, -1, 1};
    static int[] dx = {-1, 1, 0, 0};
    static int cnt;
    static ArrayList<Integer> res;

    static void dfs(int y, int x) {
        visited[y][x] = true;
        cnt++;
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny >= 0 && ny < l && nx >= 0 && nx < l && ma[ny][nx] == 1 && !visited[ny][nx]) {
                dfs(ny, nx);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            l = Integer.parseInt(br.readLine());
            ma = new int[l + 1][l + 1];
            visited = new boolean[l + 1][l + 1];

            StringTokenizer st;
            for (int i = 0; i < l; i++) {
                st = new StringTokenizer(br.readLine());
                for (int j = 0; j < l; j++) {
                    ma[i][j] = Integer.parseInt(st.nextToken());
                }
            }

            res = new ArrayList<>();
            for (int i = 0; i < l; i++) {
                for (int j = 0; j < l; j++) {
                    if (ma[i][j] == 1 && !visited[i][j]) {
                        cnt = 0;
                        dfs(i, j);
                        res.add(cnt);
                    }
                }
            }

            if (res.isEmpty()) {
                bw.write("0\n");
            } else {
                Collections.sort(res);

                bw.write(res.size() + "\n");
                for (int it : res) {
                    bw.write(it + " ");
                }
                bw.write("\n");
            }

        }

        bw.close();
    }

}
