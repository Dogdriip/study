/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_03;

import java.util.BitSet;
import java.util.Scanner;

public class FANMEETING {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int c = sc.nextInt();
        for (int tc = 0; tc < c; tc++) {
            String a = sc.next();
            String b = sc.next();

            BitSet member = new BitSet(200001);
            BitSet fan = new BitSet(200001);
            for (int i = a.length() - 1; i >= 0; i--) {
                if (a.charAt(i) == 'M') {
                    member.set(i);
                }
            }
            for (int i = b.length() - 1; i >= 0; i--) {
                if (b.charAt(i) == 'M') {
                    fan.set(i);
                }
            }

            int ans = 0;
            for (int i = 0; i < b.length() - a.length() + 1; i++) {
                BitSet fan_new = fan.get(b.length() - a.length() - i, b.length());
                if (!fan_new.intersects(member)) ans++;
            }

            System.out.println(ans);
        }
    }
}
