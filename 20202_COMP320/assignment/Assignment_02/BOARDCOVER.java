/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package Assignment_02;

import java.util.Scanner;

public class BOARDCOVER {
    public static int[][][] blocks = {{{0, 0}, {0, 1}, {1, 0}},
                               {{0, 0}, {0, 1}, {1, 1}},
                               {{0, 0}, {1, 0}, {1, 1}},
                               {{0, 0}, {1, 0}, {1, -1}}};

    public static int solution(int h, int w, char[][] ma) {
        int blank_y = -1, blank_x = -1;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (ma[i][j] == '.') {
                    blank_y = i;
                    blank_x = j;
                    System.out.println(i + " " + j);
                    break;
                }
            }
            if (blank_y != -1 && blank_x != -1) {
                break;
            }
        }

        if (blank_y == -1 && blank_x == -1) {  // found solution
            return 1;
        }

        int ret = 0;
        for (int i = 0; i < 4; i++) {
            int b1_y = blank_y + blocks[i][0][0]; int b1_x = blank_x + blocks[i][0][1];
            int b2_y = blank_y + blocks[i][1][0]; int b2_x = blank_x + blocks[i][1][1];
            int b3_y = blank_y + blocks[i][2][0]; int b3_x = blank_x + blocks[i][2][1];
            if ((b1_y >= 0 && b1_y < h) && (b1_x >= 0 && b1_x < w)
                && (b2_y >= 0 && b2_y < h) && (b2_x >= 0 && b2_x < w)
                && (b3_y >= 0 && b3_y < h) && (b3_x >= 0 && b3_x < w)
                && ma[b1_y][b1_x] == '.' && ma[b2_y][b2_x] == '.' && ma[b3_y][b3_x] == '.') {
                ma[b1_y][b1_x] = ma[b2_y][b2_x] = ma[b3_y][b3_x] = '*';
                ret += solution(h, w, ma);
                ma[b1_y][b1_x] = ma[b2_y][b2_x] = ma[b3_y][b3_x] = '.';
            }
        }

        return ret;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        for (int tc = 0; tc < c; tc++) {
            int h = sc.nextInt();
            int w = sc.nextInt();
            sc.nextLine();

            char[][] ma = new char[h + 1][w + 1];
            int blank_cnt = 0;
            for (int i = 0; i < h; i++) {
                String tmp = sc.nextLine();
                for (int j = 0; j < w; j++) {
                    ma[i][j] = tmp.charAt(j);
                    if (ma[i][j] == '.') {
                        blank_cnt++;
                    }
                }
            }

            if (blank_cnt % 3 != 0) {
                System.out.println(0);
            } else {
                int ans = solution(h, w, ma);
                System.out.println(ans);
            }

        }
    }
}
