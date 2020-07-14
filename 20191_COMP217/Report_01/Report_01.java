import java.util.Scanner;

public class Report_01 {

	static void method1() {
		Scanner sc = new Scanner(System.in);
		int grade, total = 0, cnt = 0;
		int avg;
		
		while (true) {
			System.out.print("Enter grade: ");
			grade = sc.nextInt();
			if (grade < 0) break;
			total += grade;
			cnt++;
		}
		
		avg = total / cnt;
		System.out.println();
		System.out.println("Total of " + cnt + " student grades is " + total);
		System.out.println("Class average is " + avg);
		
		sc.close();
	}
	
	static void method2() {
		Scanner sc = new Scanner(System.in);
		int grade;
		char initial[] = {'A', 'B', 'C', 'D', 'F'};
		int cnt[] = {0, 0, 0, 0, 0};
		
		while (true) {
			System.out.print("Enter grade: ");
			grade = sc.nextInt();
			if (grade < 0) break;
			
			if (grade >= 90) {
				cnt[0]++;
			} else if (grade >= 80) {
				cnt[1]++;
			} else if (grade >= 70) {
				cnt[2]++;
			} else if (grade >= 60) {
				cnt[3]++;
			} else {  // 60점 미만의 경우 F로 처리했습니다.
				cnt[4]++;
			}
		}
		
		System.out.println();
		System.out.println("Number of students who received each grade:");
		for (int i = 0; i < 5; i++) {
			System.out.println(initial[i] + ": " + cnt[i]);
		}
		
		sc.close();
	}
	
	static void method3() {
		Scanner sc = new Scanner(System.in);
		System.out.print("금액을 입력하시오 : ");
		int money = sc.nextInt();
		
		String name[] = {"오만원권", "만원권", "천원권", "오백원", "백원", "오십원", "십원", "일원"};
		String suffix[] = {"매", "매", "매", "개", "개", "개", "개", "개"};
		int val[] = {50000, 10000, 1000, 500, 100, 50, 10, 1};
		
		for (int i = 0; i < 8; i++) {
			if (money / val[i] > 0) {
				System.out.println(name[i] + ' ' + money / val[i] + suffix[i]);
				money %= val[i];
			}
		}
		
		sc.close();
	}
	
	public static void main(String[] args) {
		method1();
		// method2();
		// method3();
	}

}
