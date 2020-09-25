/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package Assignment_02;

import java.util.Scanner;

public class CLOCKSYNC {
    public static boolean[][] linked = new boolean[10][16];
    public static final int INF = 9999;

    public static void link() {
        linked[0][0] = linked[0][1] = linked[0][2] = true;
        linked[1][3] = linked[1][7] = linked[1][9] = linked[1][11] = true;
        linked[2][4] = linked[2][10] = linked[2][14] = linked[2][15] = true;
        linked[3][0] = linked[3][4] = linked[3][5] = linked[3][6] = linked[3][7] = true;
        linked[4][6] = linked[4][7] = linked[4][8] = linked[4][10] = linked[4][12] = true;
        linked[5][0] = linked[5][2] = linked[5][14] = linked[5][15] = true;
        linked[6][3] = linked[6][14] = linked[6][15] = true;
        linked[7][4] = linked[7][5] = linked[7][7] = linked[7][14] = linked[7][15] = true;
        linked[8][1] = linked[8][2] = linked[8][3] = linked[8][4] = linked[8][5] = true;
        linked[9][3] = linked[9][4] = linked[9][5] = linked[9][9] = linked[9][13] = true;
    }

    public static int solution(int[] state, int x) {
        if (x == 10) {
            boolean succeed = true;
            for (int i = 0; i < 16; i++) {
                if (state[i] != 12) {
                    succeed = false;
                    break;
                }
            }
            return (succeed ? 0 : INF);
        }

        int ret = INF;
        for (int i = 0; i < 4; i++) {
            ret = Math.min(ret, i + solution(state, x + 1));

            // push x switch
            for (int clock = 0; clock < 16; clock++) {
                if (linked[x][clock]) {
                    state[clock] += 3;
                    if (state[clock] == 15) state[clock] = 3;
                }
            }
        }
        return ret;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        link();

        int c = sc.nextInt();
        for (int tc = 0; tc < c; tc++) {
            int[] state = new int[16];

            for (int i = 0; i < 16; i++) {
                state[i] = sc.nextInt();
            }

            int ans = solution(state, 0);
            System.out.println((ans == INF ? -1 : ans));
        }
    }
}
