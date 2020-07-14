import javax.swing.*;
import java.awt.*;
import java.util.*;

class ClockThread extends Thread {
	private JLabel txt;
	private Calendar c;
	private String clockText;
	
	public ClockThread(JLabel txt) {
		this.txt = txt;
	}
	
	public void run() {
		while(true) {
			try {
				c = Calendar.getInstance();
				int hour = c.get(Calendar.HOUR_OF_DAY);
				int min = c.get(Calendar.MINUTE);
				int second = c.get(Calendar.SECOND);
				clockText = Integer.toString(hour);
				clockText = clockText.concat(":");
				clockText = clockText.concat(Integer.toString(min));
				clockText = clockText.concat(":");
				clockText = clockText.concat(Integer.toString(second));
				
				txt.setText(clockText);
				sleep(1000);
			} catch (InterruptedException e) { return; }
		}
	}
}

public class DigitalClock extends JFrame {
	private JLabel txt = new JLabel("", JLabel.CENTER);
	
	public DigitalClock() {
		setTitle("DigitalClock");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container cp = getContentPane();
		cp.setLayout(new BorderLayout());
		
		cp.add(txt, BorderLayout.CENTER);
		
		setSize(300,200);
		setVisible(true);
		
		ClockThread th = new ClockThread(txt);
		th.start();
	}
	
	public static void main(String[] args) {
		new DigitalClock();
	}
}
