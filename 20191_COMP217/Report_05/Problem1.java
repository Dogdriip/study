import java.util.*;

public class Problem1 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		ArrayList<Integer> arr = new ArrayList<Integer>();
		int n, inp;
		while (true) {
			System.out.println("1.ADD   2.REMOVE   3.PRINT POSITION   4.PRINT ALL   5.EXIT;");
			System.out.println("실행동작: ");
			n = sc.nextInt();
			
			switch(n) {
			case 1:
				System.out.println("입력 값: ");
				inp = sc.nextInt();
				if (!arr.contains(inp)) arr.add(inp);
				System.out.println();
				break;
			case 2:
				System.out.println("삭제 값: ");
				inp = sc.nextInt();
				for (int i = 0; i < arr.size(); i++) {
					if (arr.get(i).equals(inp)) {
						arr.remove(i);
						break;
					}
				}
				System.out.println();
				break;
			case 3:
				System.out.println("입력 값: ");
				inp = sc.nextInt();
				for (int i = 0; i < arr.size(); i++) {
					if (arr.get(i).equals(inp)) {
						System.out.println(inp + " 값은  " + (i + 1) + "번째에 위치");
						break;
					}
				}
				System.out.println();
				break;
			case 4:
				System.out.println("모든 값: ");
				for (int i = 0; i < arr.size(); i++) {
					System.out.print(arr.get(i) + " ");
				}
				System.out.println();
				break;
			case 5:
				sc.close();
				System.exit(0);
			}
			
		}
		
	}

}
