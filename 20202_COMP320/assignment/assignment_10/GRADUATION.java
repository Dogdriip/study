/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_10;

import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class GRADUATION {
    static int[] prerequisite;
    static int[] classes;
    static int[][] dp;
    static int n, k, m, l;
    static final int INF = 987654321;

    static int popcnt(int x) {
        int res = 0;
        for (int i = 0; i < 31; i++) {
            if ((x & (1 << i)) != 0) res++;
        }
        return res;
    }

    static int graduate(int sem, int state) {
        if (popcnt(state) >= k) return 0;
        if (sem >= m) return INF;

        if (dp[sem][state] != -1) return dp[sem][state];

        int ret = INF;

        int canTake = (classes[sem] & ~state);
        for (int i = 0; i < n; i++) {
            if ((canTake & (1 << i)) != 0 && (state & prerequisite[i]) != prerequisite[i]) {
                canTake &= ~(1 << i);
            }
        }
        for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
            if (popcnt(take) > l) continue;
            ret = Math.min(ret, graduate(sem + 1, (state | take)) + 1);
        }

        ret = Math.min(ret, graduate(sem + 1, state));
        return dp[sem][state] = ret;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int C = Integer.parseInt(br.readLine());
        while (C-- > 0) {
            prerequisite = new int[12];  // p[i] := i번 과목의 선수과목 bitset
            classes = new int[10];  // classes[i] := i번 학기에 개설되는 과목 bitset
            dp = new int[10][(1 << 12)];  // dp[i][j] := i번 학기에 과목 들은 상태가 j일 때, 앞으로 필요한 학기
            for (int[] row : dp) {
                Arrays.fill(row, -1);
            }

            StringTokenizer st = new StringTokenizer(br.readLine());
            n = Integer.parseInt(st.nextToken());  // 과목 수
            k = Integer.parseInt(st.nextToken());  // 들어야 할 과목 수
            m = Integer.parseInt(st.nextToken());  // 학기 수
            l = Integer.parseInt(st.nextToken());  // 한 학기에 최대로 들을 수 있는 과목 수

            for (int i = 0; i < n; i++) {
                st = new StringTokenizer(br.readLine());
                int r = Integer.parseInt(st.nextToken());
                for (int j = 0; j < r; j++) {
                    int x = Integer.parseInt(st.nextToken());
                    prerequisite[i] |= (1 << x);
                }
            }

            for (int i = 0; i < m; i++) {
                st = new StringTokenizer(br.readLine());
                int c = Integer.parseInt(st.nextToken());
                for (int j = 0; j < c; j++) {
                    int x = Integer.parseInt(st.nextToken());
                    classes[i] |= (1 << x);
                }
            }

            int res = graduate(0, 0);
            bw.write((res == INF ? "IMPOSSIBLE" : String.valueOf(res)) + "\n");
        }

        bw.close();
    }
}
