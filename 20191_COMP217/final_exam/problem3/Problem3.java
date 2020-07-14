package problem3;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Problem3 extends JFrame{
	private JTextField tf = new JTextField(20);
	private JTextArea ta = new JTextArea(7, 20);
	private JButton btnadd = new JButton("추가");
	
	public Problem3() {
		setTitle("텍스트영역 만들기  예제");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new FlowLayout());

		c.add(new JLabel("아래 창에 문자열을 입력하고 버튼을 클릭하세요"));
		c.add(tf);
		c.add(btnadd);
		c.add(new JScrollPane(ta));
		
		btnadd.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ta.append(tf.getText() + "\n");
			}
		});
		
		setSize(300, 300);
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new Problem3();
	}

}
