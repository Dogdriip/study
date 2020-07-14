import javax.swing.*;
import java.awt.*;

public class MyPhone extends JFrame{

	private JPanel lcdJPanel = new JPanel();
	private JTextArea lcdJTextArea;
	private String lcdOutput = "";
	
	private JPanel keyJPanel = new JPanel();
	private JButton keyJButton[] = new JButton[15];
	
	private String btn_str[] = {"Send", "clr", "End", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"};
	
	public MyPhone() {
		setTitle("MyPhone");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());
		
		lcdJTextArea = new JTextArea(lcdOutput, 5, 20);
		lcdJPanel.add(lcdJTextArea);
		
		keyJPanel.setLayout(new GridLayout(5, 3));
		for (int i = 0; i < 15; i++) {
			keyJButton[i] = new JButton(btn_str[i]);
		}
		for (int i = 0; i < 15; i++) {
			keyJPanel.add(keyJButton[i]);
		}
		
		contentPane.add(lcdJPanel, BorderLayout.NORTH);
		contentPane.add(keyJPanel, BorderLayout.CENTER);
		
		setSize(300, 500);
		setVisible(true);
	}
	
	
	public static void main(String[] args) {
		new MyPhone();
	}

}
