package problem4;
import javax.swing.*;
import java.awt.*;

public class Problem4 extends JFrame{
	private String btn_str[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"};

	private JPanel up = new JPanel();
	private JPanel center = new JPanel();
	private JPanel keypad = new JPanel();
	private JPanel down = new JPanel();
	private JPanel rightbtn = new JPanel();
	
	public Problem4() {
		setTitle("다이얼 패드");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout(0, 5));
		
		up.setLayout(new GridLayout(1, 4));
		up.add(new JButton("키패드"));
		up.add(new JButton("최근기록"));
		up.add(new JButton("즐겨찾기"));
		up.add(new JButton("연락처"));
		
		center.setLayout(new BorderLayout());
		center.add(new JTextField(), BorderLayout.NORTH);
		center.add(keypad, BorderLayout.CENTER);
		
		keypad.setLayout(new GridLayout(4, 3, 5, 1));
		for (int i = 0; i < 12; i++) {
			keypad.add(new JButton(btn_str[i]));
		}
		
		down.setLayout(new GridLayout(1, 2));
		down.add(new JButton("전화걸기"));
		down.add(rightbtn);
		
		rightbtn.setLayout(new GridLayout(1, 2));
		rightbtn.add(new JButton("이전"));
		rightbtn.add(new JButton("지우기"));
		
		contentPane.add(up, BorderLayout.NORTH);
		contentPane.add(center, BorderLayout.CENTER);
		contentPane.add(down, BorderLayout.SOUTH);
		
		setSize(400, 300);
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new Problem4();
	}

}
