package problem1;

public class Book extends Item {
	private String ISBN, title, author;

	public String getISBN() {
		return ISBN;
	}
	public void setISBN(String ISBN) {
		this.ISBN = ISBN;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	public void showInfo() {
		super.showInfo();
		System.out.println("ISBN>>" + this.ISBN);
		System.out.println("제목>>" + this.title);
		System.out.println("저자>>" + this.author);
	}
}
