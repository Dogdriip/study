
public class Classic extends Music {
	private String composer;
	
	public Classic(String name, int year, String composer) {
		super(name, year);
		this.composer = composer;
	}
	
	@Override
	public String toString() {
		return String.format("Classic [곡명=%s, 연도=%d, 작곡가=%s]", this.name, this.year, this.composer);
	}
}
