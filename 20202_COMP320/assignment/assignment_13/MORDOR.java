/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_13;

import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class MORDOR {

    static int[] a, bucket_mx, bucket_mn;
    static int sz;

    static int query(int l, int r) {
        int mx = -1, mn = 20001;

        while (l % sz != 0 && l <= r) {
            mn = Math.min(mn, a[l]);
            mx = Math.max(mx, a[l++]);
        }
        while ((r + 1) % sz != 0 && l <= r) {
            mn = Math.min(mn, a[r]);
            mx = Math.max(mx, a[r--]);
        }
        while (l <= r) {
            int bk = l / sz;

            mn = Math.min(mn, bucket_mn[bk]);
            mx = Math.max(mx, bucket_mx[bk]);
            l += sz;
        }

        return mx - mn;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int q = Integer.parseInt(st.nextToken());

            a = new int[n + 5];
            sz = (int)Math.sqrt(n);
            bucket_mx = new int[sz + 5];
            Arrays.fill(bucket_mx, -1);
            bucket_mn = new int[sz + 5];
            Arrays.fill(bucket_mn, 20001);

            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(st.nextToken());
            }

            // initialize buckets
            for (int i = 0; i < n; i++) {
                bucket_mx[i / sz] = Math.max(bucket_mx[i / sz], a[i]);
                bucket_mn[i / sz] = Math.min(bucket_mn[i / sz], a[i]);
            }

            while (q-- > 0) {
                st = new StringTokenizer(br.readLine());
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());

                bw.write(query(a, b) + "\n");
            }
        }

        bw.close();
    }

}
