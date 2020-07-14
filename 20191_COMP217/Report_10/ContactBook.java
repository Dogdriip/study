import java.io.*;
import java.util.*;

public class ContactBook implements Serializable {
	private ArrayList<Contact> list = new ArrayList<Contact>();
	
	ContactBook() {
		this.list = new ArrayList<Contact>();
	}
	
	void addContact(Contact con) {
		this.list.add(con);
	}
	void removeContact(int num) {
		this.list.remove(num);
	}
	int size() {
		return this.list.size();
	}
	Contact get(int index) {
		return this.list.get(index);
	}
}
