/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_07;

import java.util.HashMap;
import java.util.Scanner;

public class TICTACTOE {
    static HashMap<String, Integer> dp;

    static boolean finished(char[][] state, int turn) {  // turn 사람이 끝냈는지
        char ch = (turn == 0 ? 'o' : 'x');
        for (int i = 0; i < 3; i++) {
            if (state[i][0] == ch && state[i][1] == ch && state[i][2] == ch) {
                return true;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (state[0][i] == ch && state[1][i] == ch && state[2][i] == ch) {
                return true;
            }
        }
        if (state[0][0] == ch && state[1][1] == ch && state[2][2] == ch) {
            return true;
        }
        if (state[0][2] == ch && state[1][1] == ch && state[2][0] == ch) {
            return true;
        }

        return false;
    }

    static int solution(char[][] state, int turn) {  // 현재 게임판 상태가 state이고 지금 둘 사람이 turn(o:0, x:1)일 때, turn이 이기면 2, 비기면 1, 지면 0을 반환
        if (finished(state, 1 - turn)) {
            return 0;  // 이미 이전 턴에서 상대가 끝낸 경우
        }

        String s = new String();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += state[i][j];
            }
        }

        if (dp.get(s) != null) return dp.get(s);
        int res = 987654231;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == '.') {
                    state[i][j] = (turn == 0 ? 'o' : 'x');
                    res = Math.min(res, solution(state, 1 - turn));  // 지는 게 우선. 순서 고정.
                    state[i][j] = '.';
                }
            }
        }
        
        int ret = 0;
        if (res == 987654231) ret = 1;
        else if (res == 2) ret = 0;
        else if (res == 1) ret = 1;
        else if (res == 0) ret = 2;

        dp.put(s, ret);
        return ret;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        while (c-- > 0) {
            char[][] ma = new char[3][3];
            int x_cnt = 0, o_cnt = 0;

            for (int i = 0; i < 3; i++) {
                String s = sc.next();
                for (int j = 0; j < 3; j++) {
                    ma[i][j] = s.charAt(j);
                    if (ma[i][j] == 'o') o_cnt++;
                    else if (ma[i][j] == 'x') x_cnt++;
                }
            }

            int turn = (o_cnt < x_cnt ? 0 : 1);

            dp = new HashMap<>();
            int res = solution(ma, turn);
            if (res == 2) {  // win
                System.out.println((turn == 0 ? 'o' : 'x'));
            } else if (res == 1) {  // draw
                System.out.println("TIE");
            } else {  // lose
                System.out.println((turn == 0 ? 'x' : 'o'));
            }
        }
    }
}
