package problem2;

public class Classic extends Music {
	public String composer;
	
	public Classic(String name, int year, String composer) {
		super(name, year);
		this.composer = composer;
	}
	
	@Override
	public String toString() {
		return String.format("Classic [곡명=%s, 연도=%d, 작곡가=%s]", this.name, this.year, this.composer);
	}
	
	@Override
	public String play() {
		return this.name + "을(를) 연주합니다.";
	}
}
