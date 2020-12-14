/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_13;

import java.io.*;
import java.util.*;

public class SOLONG {

    static final int GO_MAX = 30;
    static HashMap<String, Integer> mp;

    static class Pair<T1, T2> {
        T1 x;
        T2 y;
        public Pair(T1 x, T2 y) {
            this.x = x;
            this.y = y;
        }
        public T1 first() { return x; }
        public T2 second() { return y; }
    }

    static class Trie {
        Trie[] go = new Trie[GO_MAX];
        int output;  // 여기서 끝나는 단어 id.
        int first;  // 이 노드가 추천하는 단어. 제일 먼저 들어온 단어.

        Trie() {
            Arrays.fill(go, null);
            output = -1;
            first = -1;
        }

        void insert(String s, int id, int idx) {
            if (s.length() == idx) {
                output = id;
            } else {
                char x = s.charAt(idx);
                int nx = x - 'A';
                if (go[nx] == null) {
                    go[nx] = new Trie();
                }
                if (go[nx].first == -1) {
                    go[nx].first = id;
                }
                go[nx].insert(s, id, idx + 1);
            }
        }

        Trie find(String s, int idx) {
            if (s.length() == idx) return this;
            int nx = s.charAt(idx) - 'A';
            if (go[nx] == null) {
                return null;
            }
            return go[nx].find(s, idx + 1);
        }

        int keystroke(String s, int id, int idx) {
            if (s.length() == idx) {
                return 0;
            }

            if (first == id) {
                return 1;
            }
            int nx = s.charAt(idx) - 'A';
            return 1 + go[nx].keystroke(s, id, idx + 1);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int m = Integer.parseInt(st.nextToken());

            ArrayList<Pair<String, Integer>> p = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                st = new StringTokenizer(br.readLine());
                String s = st.nextToken();
                int freq = Integer.parseInt(st.nextToken());

                p.add(new Pair<>(s, freq));
            }

            // Sort p
            Collections.sort(p, new Comparator<Pair<String, Integer>>() {
                @Override
                public int compare(Pair<String, Integer> o1, Pair<String, Integer> o2) {
                    if (o1.second().equals(o2.second())) return o1.first().compareTo(o2.first());
                    return o2.second().compareTo(o1.second());
                }
            });

            // HashMap
            mp = new HashMap<>();

            // Construct trie
            Trie root = new Trie();
            for (int i = 0; i < p.size(); i++) {
                root.insert(p.get(i).first(), i, 0);
                mp.put(p.get(i).first(), i);
            }
            root.first = -1;

            // Sum keystrokes of M words
            st = new StringTokenizer(br.readLine());
            int ans = m - 1;  // all tabs
            for (int i = 0; i < m; i++) {
                String s = st.nextToken();

                Trie node = root.find(s, 0);
                if (node == null || node.output == -1) {
                    ans += s.length();
                } else {
                    ans += root.keystroke(s, node.output, 0);
                }
            }

            bw.write(ans + "\n");

        }

        bw.close();
    }

}
