package problem2;

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
	
	@Override
	public String play() {
		return this.name + "을(를) 연주합니다.";
	}
}
