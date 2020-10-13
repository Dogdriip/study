/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_03;

import java.util.Scanner;

public class FENCE {
    public static int solution(int[] a, int l, int r) {
        if (l == r) {
            return a[l];
        }

        int mid = (l + r) / 2;
        int res = Math.max(solution(a, l, mid), solution(a, mid + 1, r));

        int p_l = mid, p_r = mid;
        int min_h = a[mid];
        while (true) {
            res = Math.max(res, min_h * (p_r - p_l + 1));

            if (p_l == l && p_r == r) break;
            else if (p_l == l) {
                p_r++;
                min_h = Math.min(min_h, a[p_r]);
            } else if (p_r == r) {
                p_l--;
                min_h = Math.min(min_h, a[p_l]);
            } else {
                if (a[p_l - 1] > a[p_r + 1]) {
                    p_l--;
                    min_h = Math.min(min_h, a[p_l]);
                } else {
                    p_r++;
                    min_h = Math.min(min_h, a[p_r]);
                }
            }
        }

        return res;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        for (int tc = 0; tc < c; tc++) {
            int n = sc.nextInt();
            int[] a = new int[n + 1];
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextInt();
            }

            System.out.println(solution(a, 0, n - 1));
        }
    }
}
