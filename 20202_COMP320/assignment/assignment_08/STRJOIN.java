/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_08;

import java.util.PriorityQueue;
import java.util.Scanner;

public class STRJOIN {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int c = sc.nextInt();
        while (c-- > 0) {
            PriorityQueue<Integer> pq = new PriorityQueue<>();

            int n = sc.nextInt();
            for (int i = 0; i < n; i++) {
                int x = sc.nextInt();
                pq.add(x);
            }

            int ans = 0;
            while (pq.size() > 1) {
                int tmp = pq.poll() + pq.poll();
                ans += tmp;
                pq.add(tmp);
            }
            System.out.println(ans);
        }
    }
}
