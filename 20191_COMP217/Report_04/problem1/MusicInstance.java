package problem1;

public class MusicInstance {
	
	public static void main(String[] args) {
		Music m = new Music("흥부전", 1700);
		Classic c = new Classic("캐논", 1732, "파핼벨");
		Pop p = new Pop("바람이 분다", 2004, "이소라");
		
		Music[] musics = {m, c, p};
		for (Music currentMusic : musics) {
			System.out.println(currentMusic);
			if (currentMusic instanceof Classic) {
				 Classic music = (Classic)currentMusic;
				 System.out.println(music.composer);
			} else if (currentMusic instanceof Pop) {
				Pop music = (Pop)currentMusic;
				 System.out.println(music.singer);
			}
		}
		
		for (Music currentMusic : musics) {
			System.out.println(currentMusic.getClass().getSimpleName());
		}
	}

}
