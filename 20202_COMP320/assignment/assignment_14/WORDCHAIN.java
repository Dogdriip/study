/**
 * 저는 이 소스 코드를 스스로의 힘으로 작성하였습니다.
 * 만약 소스 코드를 복제한 것이 밝혀지면 어떤 불이익도 감수하겠습니다.
 * @author Dogdriip
 */

package assignment_14;

import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;

public class WORDCHAIN {

    static String[] words;
    static ArrayList<ArrayList<ArrayList<String>>> graph;
    static int[][] adj;
    static int[] indeg;
    static int[] outdeg;

    static boolean check_euler() {
        int p1 = 0, m1 = 0;
        for (int i = 0; i < 30; i++) {
            int d = outdeg[i] - indeg[i];
            if (d < -1 || d > 1) return false;
            if (d == 1) p1++;
            if (d == -1) m1++;
        }

        return (p1 == 1 && m1 == 1) || (p1 == 0 && m1 == 0);
    }

    static void _euler_circuit(int x, ArrayList<Integer> circuit) {
        for (int nx = 0; nx < 30; nx++) {
            while (adj[x][nx] > 0) {
                adj[x][nx]--;
                _euler_circuit(nx, circuit);
            }
        }
        circuit.add(x);
    }

    static ArrayList<Integer> euler_circuit() {
        ArrayList<Integer> circuit = new ArrayList<>();
        for (int i = 0; i < 30; i++) {
            if (outdeg[i] == indeg[i] + 1) {
                _euler_circuit(i, circuit);
                return circuit;
            }
        }
        for (int i = 0; i < 30; i++) {
            if (outdeg[i] > 0) {
                _euler_circuit(i, circuit);
                return circuit;
            }
        }

        return circuit;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int c = Integer.parseInt(br.readLine());
        while (c-- > 0) {
            int n = Integer.parseInt(br.readLine());

            words = new String[n + 1];
            graph = new ArrayList<>();
            for (int i = 0; i < 30; i++) {
                graph.add(new ArrayList<>());
                for (int j = 0; j < 30; j++) {
                    graph.get(i).add(new ArrayList<>());
                }
            }
            adj = new int[30][30];
            indeg = new int[30];
            outdeg = new int[30];

            for (int i = 0; i < n; i++) {
                words[i] = br.readLine();
                int u = words[i].charAt(0) - 'a';
                int v = words[i].charAt(words[i].length() - 1) - 'a';
                graph.get(u).get(v).add(words[i]);
                adj[u][v]++;
                outdeg[u]++;
                indeg[v]++;
            }

            if (!check_euler()) {
                bw.write("IMPOSSIBLE\n");
            } else {
                ArrayList<Integer> circuit = euler_circuit();
                if (circuit.size() != n + 1) {
                    bw.write("IMPOSSIBLE\n");
                } else {
                    Collections.reverse(circuit);

                    StringBuilder sb = new StringBuilder();
                    for (int i = 0; i < circuit.size() - 1; i++) {
                        int u = circuit.get(i), v = circuit.get(i + 1);
                        sb.append(graph.get(u).get(v).get(graph.get(u).get(v).size() - 1) + " ");
                        graph.get(u).get(v).remove(graph.get(u).get(v).size() - 1);
                    }

                    bw.write(sb.toString() + "\n");
                }
            }

        }

        bw.close();
    }

}
