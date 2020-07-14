package problem2;
import java.util.*;

public class PhonePrint {
	
	public static void main(String[] args) {
		ArrayList<Phone> arr = new ArrayList<Phone>();
		Scanner sc = new Scanner(System.in);
		
		System.out.println("전화번호 정보를 입력하세요.");
		for (int i = 0; i < 2; i++) {
			System.out.print("이름>>");
			String name = sc.next();
			System.out.print("주소>>");
			String address = sc.next();
			System.out.print("전화번호>>");
			String telNum = sc.next();
			
			Phone p = new Phone(name, address, telNum);
			arr.add(p);
			
			System.out.println("---------------------");
		}
		
		for (int i = 0; i < 2; i++) {
			System.out.println(arr.get(i).toString());
		}
		
		sc.close();
	}
	
}
