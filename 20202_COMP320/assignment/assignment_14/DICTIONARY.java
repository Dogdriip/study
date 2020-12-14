/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_14;

import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class DICTIONARY {

    static String[] words;
    static ArrayList<ArrayList<Integer>> adj;
    static int[] indeg;
    static ArrayList<Integer> order;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            int n = Integer.parseInt(br.readLine());

            words = new String[n + 1];
            adj = new ArrayList<>(26);
            for (int i = 0; i < 26; i++) {
                adj.add(new ArrayList<>());
            }
            indeg = new int[26];
            order = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                words[i] = br.readLine();
            }

            for (int i = 0; i < n - 1; i++) {
                String s1 = words[i], s2 = words[i + 1];
                int mn_len = Math.min(s1.length(), s2.length());
                for (int j = 0; j < mn_len; j++) {
                    if (s1.charAt(j) != s2.charAt(j)) {
                        // s1[j] -> s2[j] edge
                        int u = s1.charAt(j) - 'a';
                        int v = s2.charAt(j) - 'a';
                        adj.get(u).add(v);
                        indeg[v]++;
                        break;
                    }
                }
            }

            // Topological sort
            ArrayDeque<Integer> q = new ArrayDeque<>();
            for (int i = 0; i < 26; i++) {
                if (indeg[i] == 0) {
                    q.push(i);
                }
            }

            while (!q.isEmpty()) {
                int x = q.poll();
                order.add(x);

                for (int nx : adj.get(x)) {
                    indeg[nx]--;
                    if (indeg[nx] == 0) {
                        q.push(nx);
                    }
                }
            }

            if (order.size() != 26) {
                bw.write("INVALID HYPOTHESIS\n");
            } else {
                for (int it : order) {
                    bw.write(it + 'a');
                }
                bw.write("\n");
            }

        }

        bw.close();
    }

}
