package problem1;

public class Item {
	private int itemId;
	private String description, maker;
	private int price;
	
	public int getItemId() {
		return itemId;
	}
	public void setItemId(int itemId) {
		this.itemId = itemId;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public String getMaker() {
		return maker;
	}
	public void setMaker(String maker) {
		this.maker = maker;
	}
	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}
	public void showInfo() {
		System.out.println("상품ID>>" + this.itemId);
		System.out.println("상품 설명>>" + this.description);
		System.out.println("생산자>>" + this.maker);
		System.out.println("가격>>" + this.price);
	}
}
