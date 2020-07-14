package problem1;

public class JavaProgramming extends Book {
	private String language;

	public String getLanguage() {
		return language;
	}
	public void setLanguage(String language) {
		this.language = language;
	}
	public void showInfo() {
		super.showInfo();
		System.out.println("언어>>" + this.language);
	}
}
