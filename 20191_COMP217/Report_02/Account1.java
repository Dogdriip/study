
public class Account1 {
	private String name;
	private double balance;

	public Account1(String n){
		this.name = n;
		this.balance = 0;
	}

	public String getName() {
		return this.name;
	}

	public double getBalance() {
		return this.balance;
	}

	public void credit(double b) {
		this.balance = b;
	}
		
	public void print() {
		System.out.println("예금주 : " + this.name);
		System.out.println("잔액 : " + this.balance);
		System.out.println();
	}
		
	public void addInterest(double interestRates) {
		this.balance *= interestRates;
	}
}
