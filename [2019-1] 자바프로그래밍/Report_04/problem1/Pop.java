package problem1;

public class Pop extends Music {
	public String singer;
	
	public Pop(String name, int year, String singer) {
		super(name, year);
		this.singer = singer;
	}
	
	@Override
	public String toString() {
		return String.format("Pop [곡명=%s, 연도=%d, 가수=%s]", this.name, this.year, this.singer);
	}
}
