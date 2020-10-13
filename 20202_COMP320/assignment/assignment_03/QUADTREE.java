/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_03;

import java.util.Scanner;

public class QUADTREE {
    public static String solution(String s, int x) {
        if (s.charAt(x) != 'x') {
            return String.valueOf(s.charAt(x));
        }

        String ul = solution(s, x + 1);
        String ur = solution(s, x + 1 + ul.length());
        String ll = solution(s, x + 1 + ul.length() + ur.length());
        String lr = solution(s, x + 1 + ul.length() + ur.length() + ll.length());

        return "x" + ll + lr + ul + ur;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        for (int tc = 0; tc < c; tc++) {
            String s = sc.next();
            System.out.println(solution(s, 0));
        }
    }
}
