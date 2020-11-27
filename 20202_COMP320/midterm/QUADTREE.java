package midterm;

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

        // return "x" + ll + lr + ul + ur;

        // orig
        // 1 2  ul ur
        // 3 4  ll lr

        // 상하 swap
        // 3 4  ll lr
        // 1 2  ul ur

        // 좌우 swap
        // 2 1  ur ul
        // 4 3  lr ll

        return "x" + ur + ul + lr + ll;
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
