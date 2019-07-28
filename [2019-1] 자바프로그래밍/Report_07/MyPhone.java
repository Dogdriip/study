import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MyPhone extends JFrame{

	private JPanel lcdJPanel = new JPanel();
	private JTextArea lcdJTextArea;
	private String lcdOutput = "";
	
	private JPanel keyJPanel = new JPanel();
	private JButton keyJButton[] = new JButton[15];
	
	private String btn_str[] = {"Send", "clr", "End", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"};
	
	private class MyMouseListener extends MouseAdapter {
		private int idx;
		
		public MyMouseListener(int idx) {
			this.idx = idx;
		}
		
		public void mouseClicked(MouseEvent e) {
			lcdJTextArea.append(btn_str[this.idx]);
		}
	}
	
	public MyPhone() {
		setTitle("MyPhone");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());
		
		lcdJTextArea = new JTextArea(lcdOutput, 6, 25);
		lcdJPanel.add(lcdJTextArea);
		
		keyJPanel.setLayout(new GridLayout(5, 3));
		for (int i = 0; i < 15; i++) {
			keyJButton[i] = new JButton(btn_str[i]);
		}
		
		// Send
		keyJButton[0].addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				lcdJTextArea.append("\n전화 거는 중...\n");
			}
		});
		// clr
		keyJButton[1].addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				String text = lcdJTextArea.getText();
				if (!text.isEmpty()) lcdJTextArea.setText(text.substring(0, text.length() - 1));
			}
		});
		// End
		keyJButton[2].addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				lcdJTextArea.setText("");
			}
		});
		// 0~9, *, #
		for (int i = 3; i < 15; i++) {
			keyJButton[i].addMouseListener(new MyMouseListener(i));
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
