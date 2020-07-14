import java.util.Scanner;

public class Report_02 {
	
	static void method1() {
		Scanner sc = new Scanner(System.in);
		
		// 결과 스크린샷에 맞춰 account1의 초기 balance를 50, account2의 초기 balance를 0으로 설정하였습니다.
		Account account1 = new Account(50.0);
		Account account2 = new Account(0.0);
		
		System.out.print("Enter deposit amount for account1: ");
		account1.credit(sc.nextDouble());
		System.out.print("Enter deposit amount for account2: ");
		account2.credit(sc.nextDouble());
		
		System.out.println("account1 balance: $" + account1.getBalance());
		System.out.println("account2 balance: $" + account2.getBalance());
	}
	
	static void method2() {
		System.out.println();
		Account1 account = new Account1("홍길동");
		account.credit(1000.0);
		account.print();
	
		account.addInterest(1.1);
		account.print();
	}
	
	static void method3() {
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter first integer : ");
		int a = sc.nextInt();
		System.out.print("Enter second integer : ");
		int b = sc.nextInt();
		
		System.out.println();
		System.out.println("Sum is " + (a + b));
		System.out.println("Product is " + (a * b));
		System.out.println("Difference is " + (a - b));
		System.out.println("Quotient is " + (a / b));
	}

	public static void main(String[] args) {
		method1();
		method2();
		method3();
	}

}
