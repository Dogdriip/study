package problem2;

public abstract class Music implements Payable {
	protected String name;
	protected int year;
	
	public Music(String name, int year) {
		this.name = name;
		this.year = year;
	}
	
	public String toString() {
		return String.format("Music [곡명=%s, 연도=%d]", this.name, this.year);
	}
}
