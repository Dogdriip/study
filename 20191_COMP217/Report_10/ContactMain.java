import java.util.*;
import java.io.*;

public class ContactMain {
	ObjectInputStream input;
	ObjectOutputStream output;
	ContactBook con = new ContactBook();
	
	public void openFile() {
		try {
			input = new ObjectInputStream(new FileInputStream("report10.ser"));
		} catch(IOException ioException) {
			System.err.println("Error opening file.");
		}
		
		try {
			if (input != null) {
				con = (ContactBook)input.readObject();
			}
		} catch(ClassNotFoundException classNotFoundException) {
			System.err.println("Unable to create object.");
		} catch(IOException ioException) {
			System.err.println("Error opening file.");
		}
		
	}
	
	public void saveFile() {
		try {
			output = new ObjectOutputStream(new FileOutputStream("report10.ser"));
		} catch (IOException ioException) {
			System.err.println("Error opening file.");
		}
		
		try {
			output.writeObject(con);
		} catch (IOException ioException) {
			System.err.println("Error opening file.");
		} catch (NoSuchElementException elementExcepition) {
			System.err.println("Invalid input. Please try again");
		}
		
		try {
			if (output != null) {
				output.close();
			}
		} catch (IOException ioException) {
			System.err.println("Error closing file.");
			System.exit(1);
		}
	}

	public static void main(String[] args) {
		ContactMain m = new ContactMain();
		Scanner sc = new Scanner(System.in);
		
		while (true) {
			m.openFile();
			System.out.println("1. 주소록 추가 / 2. 주소록 삭제 / 3. 주소록 출력 / 4. 주소록 저장 & 종료");
			int op = sc.nextInt();
			
			switch (op) {
			case 1:
				Contact c = new Contact();
				System.out.print("이름을 입력하시오 : ");
				c.setName(sc.next());
				System.out.print("전화번호를 입력하시오(-는 제외하고) : ");
				c.setPhone(sc.next());
				System.out.print("이메일을 입력하시오 : ");
				c.setEmail(sc.next());
				m.con.addContact(c);
				m.saveFile();
				break;
			case 2:
				System.out.print("삭제할 index 입력 : ");
				int idx = sc.nextInt();
				m.con.removeContact(idx);
				m.saveFile();
				break;
			case 3:
				for (int i = 0; i < m.con.size(); i++) {
					System.out.println("--------------------------------------");
					System.out.println(i + "번 연락처");
					Contact tmp = m.con.get(i);
					System.out.println("이름 : " + tmp.getName());
					System.out.println("전화번호 : " + tmp.getPhone());
					System.out.println("이메일 : " + tmp.getEmail());
				}
				break;
			case 4:
				m.saveFile();
				System.exit(0);
			}
		}
		
	}
	
}
