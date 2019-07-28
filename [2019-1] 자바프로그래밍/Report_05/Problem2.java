import java.util.*;

public class Problem2 {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		HashMap<String, Integer> mp = new HashMap<String, Integer>();
		String name;
		int point;
		
		System.out.println("** 포인트 관리 프로그램입니다 **");
		while (true) {
			System.out.print("이름과 포인트 입력>>");
			name = sc.next();
			if (name.equals("exit")) break;
			point = sc.nextInt();
			
			if (mp.containsKey(name)) {
				mp.put(name, mp.get(name) + point);
			} else {
				mp.put(name, point);
			}
			
			Set<String> keys = mp.keySet();
			Iterator<String> it = keys.iterator();
			while (it.hasNext()) {
				String key = it.next();
				int val = mp.get(key);
				System.out.print("(" + key + "," + val + ")");
			}
			System.out.println();
		}
		
		sc.close();
	}
	
}
