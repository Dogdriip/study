package problem1;

public class CD extends Item {
	private String name, singer;

	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getSinger() {
		return singer;
	}
	public void setSinger(String singer) {
		this.singer = singer;
	}
	public void showInfo() {
		super.showInfo();
		System.out.println("앨범>>" + this.name);
		System.out.println("가수>>" + this.singer);
	}
}
