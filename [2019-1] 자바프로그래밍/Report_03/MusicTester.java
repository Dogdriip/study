
public class MusicTester {

	public static void main(String[] args) {
		Music m = new Music("흥부전", 1700);
		Classic c = new Classic("운명", 1808, "베토벤");
		Pop p = new Pop("보헤미안 랩소디", 1980, "퀸");
		System.out.println(m);
		System.out.println(c);
		System.out.println(p);
	}

}
