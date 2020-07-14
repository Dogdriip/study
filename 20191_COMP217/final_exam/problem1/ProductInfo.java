package problem1;
import java.util.*;

public class ProductInfo {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		ArrayList<Item> arr = new ArrayList<Item>();
		int cnt = 0;
		
		while (true) {
			System.out.print("상품 추가(1), 모든 상품 조회(2), 끝내기(3)>>");
			int op = Integer.parseInt(sc.nextLine());
			
			switch(op) {
			case 1:
				if (arr.size() >= 10) {
					System.out.println("10개 초과");
					break;
				}
				
				System.out.print("상품 종류 책(1), CD(2), 전공책(3)>>");
				int type = Integer.parseInt(sc.nextLine());
				
				System.out.print("상품설명>>");
				String description = sc.nextLine();
				System.out.print("생산자>>");
				String maker = sc.nextLine();
				System.out.print("가격>>");
				int price = Integer.parseInt(sc.nextLine());
				
				if (type == 1) {
					System.out.print("제목>>");
					String title = sc.nextLine();
					System.out.print("저자>>");
					String author = sc.nextLine();
					System.out.print("ISBN>>");
					String ISBN = sc.nextLine();
					
					Book b = new Book();
					b.setItemId(cnt++);
					b.setDescription(description);
					b.setMaker(maker);
					b.setPrice(price);
					b.setTitle(title);
					b.setAuthor(author);
					b.setISBN(ISBN);
					
					arr.add(b);
				} else if (type == 2) {
					System.out.print("앨범>>");
					String name = sc.nextLine();
					System.out.print("가수>>");
					String singer = sc.nextLine();
					
					CD cd = new CD();
					cd.setItemId(cnt++);
					cd.setDescription(description);
					cd.setMaker(maker);
					cd.setPrice(price);
					cd.setName(name);
					cd.setSinger(singer);
					
					arr.add(cd);
				} else {
					System.out.print("제목>>");
					String title = sc.nextLine();
					System.out.print("저자>>");
					String author = sc.nextLine();
					System.out.print("언어>>");
					String language = sc.nextLine();
					System.out.print("ISBN>>");
					String ISBN = sc.nextLine();
					
					JavaProgramming jp = new JavaProgramming();
					jp.setItemId(cnt++);
					jp.setDescription(description);
					jp.setMaker(maker);
					jp.setPrice(price);
					jp.setTitle(title);
					jp.setAuthor(author);
					jp.setLanguage(language);
					jp.setISBN(ISBN);
					
					arr.add(jp);
				}
				break;
			case 2:
				for (int i = 0; i < arr.size(); i++) {
					arr.get(i).showInfo();
				}
				break;
			case 3:
				sc.close();
				System.exit(0);
			}
		}

	}

}
