package problem2;
import java.util.*;

public class PhoneManager {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		ArrayList<Phone> arr = new ArrayList<Phone>();
		
		System.out.println("----------------------------------");
		System.out.println("전화번호 관리 프로그램을 시작합니다.");
		System.out.println("----------------------------------");
		
		while (true) {
			System.out.print("삽입:1, 삭제:2, 전체보기:3, 종료:4 >>");
			int op = sc.nextInt();
			
			switch(op) {
			case 1:
				System.out.print("이름>>");
				String name = sc.next();
				System.out.print("주소>>");
				String address = sc.next();
				System.out.print("전화번호>>");
				String telNum = sc.next();
				
				Phone p = new Phone(name, address, telNum);
				arr.add(p);
				break;
			case 2:
				System.out.print("이름>>");
				String s = sc.next();
				for (int i = 0; i < arr.size(); i++) {
					if (arr.get(i).getName().equals(s)) {
						arr.remove(i);
						break;
					}
				}
				break;
			case 3:
				for (int i = 0; i < arr.size(); i++) {
					System.out.println(arr.get(i).toString());
				}
				break;
			case 4:
				System.out.println("프로그램을 종료합니다...");
				sc.close();
				System.exit(0);
			}
		}
	}

}
