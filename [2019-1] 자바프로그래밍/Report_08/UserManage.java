import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class UserManage extends JFrame {
	private JPanel pBase;
	
	private JPanel pLeft;
	private JPanel pLeftInfo;
	private JPanel pLabel;
	private JPanel pInput;
	private JPanel pID;
	private JTextField tfName, tfID1, tfID2, tfPhone, tfAddress;
	
	private JPanel pRight;
	private JPanel pRightShowAll;
	private JPanel pRightButton;
	private JButton bShowAll;
	private JTextArea taInfo;
	private JButton bRegister, bModify, bDelete, bExit;
	
	private String[] menu = {"이름", "주민번호", "전화번호", "주소"}; 
	private ArrayList<String> aName = new ArrayList<String>();
	private ArrayList<String> aID1 = new ArrayList<String>();
	private ArrayList<String> aID2 = new ArrayList<String>();
	private ArrayList<String> aPhone = new ArrayList<String>();
	private ArrayList<String> aAddress = new ArrayList<String>();
	private int totalCnt = 0;
	
	private JPanel pModifyDialog;
	private JTextField tfModifyPhone, tfModifyAddress;
	private JPanel pDeleteDialog;
	
	private void ShowInfo() {
		// taInfo에 정보 출력
		taInfo.setText("");
		taInfo.append("전체 인원의 개인정보 입니다.\n");
		for (int i = 0; i < 4; i++) {
			taInfo.append(menu[i] + "\t");
		}
		taInfo.append("\n=========================================\n");
		for (int i = 0; i < totalCnt; i++) {
			taInfo.append(aName.get(i) + "\t");
			taInfo.append(aID1.get(i) + aID2.get(i) + "\t");
			taInfo.append(aPhone.get(i) + "\t");
			taInfo.append(aAddress.get(i) + "\n");
		}
		taInfo.append("=========================================\n");
		taInfo.append("총 " + totalCnt + "명");
	}
	
	public UserManage() {
		setTitle("사용자 관리");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new BorderLayout());
		
		////////////// 전체 패널
		pBase = new JPanel(); pBase.setLayout(new BorderLayout());
		c.add(pBase);
		
		
		//////// 왼쪽
		pLeft = new JPanel(); pLeft.setLayout(new GridLayout(2, 1));
		pLeftInfo = new JPanel(); pLeftInfo.setLayout(new BorderLayout());
		
		// 왼쪽 라벨
		pLabel = new JPanel(); pLabel.setLayout(new GridLayout(4, 1));
		pLabel.add(new JLabel("이름 : ", JLabel.RIGHT));
		pLabel.add(new JLabel("주민번호 : ", JLabel.RIGHT));
		pLabel.add(new JLabel("전화번호 : ", JLabel.RIGHT));
		pLabel.add(new JLabel("주소 : ", JLabel.RIGHT));
		
		pLeftInfo.add(pLabel, BorderLayout.WEST);

		// 왼쪽 필드
		pInput = new JPanel(); pInput.setLayout(new GridLayout(4, 1));
		tfName = new JTextField(20);
		pInput.add(tfName);
		
		pID = new JPanel(); pID.setLayout(new GridLayout(1, 2));
		tfID1 = new JTextField(10);
		tfID2 = new JTextField(10);
		pID.add(tfID1);
		pID.add(tfID2);
		pInput.add(pID);

		tfPhone = new JTextField(20);
		tfAddress = new JTextField(20);
		pInput.add(tfPhone);
		pInput.add(tfAddress);
		
		pLeftInfo.add(pInput, BorderLayout.CENTER);
		
		// 왼쪽 마무리
		pLeftInfo.setBorder(new TitledBorder(new SoftBevelBorder(SoftBevelBorder.RAISED), "개인정보"));
		pLeft.add(pLeftInfo);

		pBase.add(pLeft, BorderLayout.WEST);
		
		
		
		//////// 오른쪽
		pRight = new JPanel(); pRight.setLayout(new BorderLayout());
		
		// 전체보기 패널
		pRightShowAll = new JPanel(); pRightShowAll.setLayout(new FlowLayout(FlowLayout.LEFT));
		
		bShowAll = new JButton("전체보기");
		bShowAll.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				ShowInfo();
			}
		});
		pRightShowAll.add(bShowAll);
		pRightShowAll.add(new JLabel("<== 이것을 누르면 전체보기가 됩니다."));
		pRight.add(pRightShowAll, BorderLayout.NORTH);
		
		// 개인정보 textarea
		taInfo = new JTextArea();
		pRight.add(taInfo, BorderLayout.CENTER);
		
		// 밑 버튼
		pRightButton = new JPanel(); pRightButton.setLayout(new GridLayout(1, 4));
		bRegister = new JButton("등록");
		bModify = new JButton("수정");
		bDelete = new JButton("삭제");
		bExit = new JButton("종료");
		
		bRegister.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				String name = tfName.getText();
				String id1 = tfID1.getText();
				String id2 = tfID2.getText();
				String phone = tfPhone.getText();
				String address = tfAddress.getText();
				aName.add(name);
				aID1.add(id1);
				aID2.add(id2);
				aPhone.add(phone);
				aAddress.add(address);
				
				totalCnt++;
				ShowInfo();
			}
		});
		bModify.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				String name = tfName.getText();
				String id1 = tfID1.getText();
				String id2 = tfID2.getText();
				String phone = tfPhone.getText();
				String address = tfAddress.getText();
				
				int i;
				for (i = 0; i < totalCnt; i++) {
					if (aName.get(i).equals(name) && aID1.get(i).equals(id1) && aID2.get(i).equals(id2)) {
						break;
					}
				}
				
				if (i == totalCnt) {
					taInfo.setText("찾을 수 없습니다.");
				} else {
					taInfo.setText("해당 사용자를 찾았습니다. 수정하세요.");
					pModifyDialog = new JPanel(); pModifyDialog.setLayout(new BorderLayout());
					
					JPanel label = new JPanel(); label.setLayout(new GridLayout(4, 1));
					label.add(new JLabel("이름 : ", JLabel.RIGHT));
					label.add(new JLabel("주민번호 : ", JLabel.RIGHT));
					label.add(new JLabel("전화번호 : ", JLabel.RIGHT));
					label.add(new JLabel("주소 : ", JLabel.RIGHT));
					
					JPanel field = new JPanel(); field.setLayout(new GridLayout(4, 1));
					field.add(new JLabel(name));
					field.add(new JLabel(id1 + "-" + id2));
					tfModifyPhone = new JTextField(20);
					tfModifyPhone.setText(phone);
					field.add(tfModifyPhone);
					tfModifyAddress = new JTextField(20);
					tfModifyAddress.setText(address);
					field.add(tfModifyAddress);
					
					pModifyDialog.add(label, BorderLayout.WEST);
					pModifyDialog.add(field, BorderLayout.CENTER);
					
					int result = JOptionPane.showConfirmDialog(null, pModifyDialog, "수정", JOptionPane.OK_CANCEL_OPTION);
					if (result == JOptionPane.OK_OPTION) {
						String newPhone = tfModifyPhone.getText();
						String newAddress = tfModifyAddress.getText();
						aPhone.set(i, newPhone);
						aAddress.set(i, newAddress);
						taInfo.setText("수정 완료");
					}
				}
			}
		});
		bDelete.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				String name = tfName.getText();
				String id1 = tfID1.getText();
				String id2 = tfID2.getText();
				
				int i;
				for (i = 0; i < totalCnt; i++) {
					if (aName.get(i).equals(name) && aID1.get(i).equals(id1) && aID2.get(i).equals(id2)) {
						break;
					}
				}
				
				if (i == totalCnt) {
					taInfo.setText("찾을 수 없습니다.");
				} else {
					pDeleteDialog = new JPanel(); pDeleteDialog.setLayout(new BorderLayout());
					
					JPanel label = new JPanel(); label.setLayout(new GridLayout(2, 1));
					label.add(new JLabel("이름 : ", JLabel.RIGHT));
					label.add(new JLabel("주민번호 : ", JLabel.RIGHT));
					
					JPanel field = new JPanel(); field.setLayout(new GridLayout(2, 1));
					
					JTextField tfTempName = new JTextField(20);
					tfTempName.setText(name);
					field.add(tfTempName);
					
					JPanel idfield = new JPanel(); idfield.setLayout(new GridLayout(1, 2));
					JTextField tfTempID1 = new JTextField(10);
					tfTempID1.setText(id1);
					JTextField tfTempID2 = new JTextField(10);
					tfTempID2.setText(id2);
					idfield.add(tfTempID1);
					idfield.add(tfTempID2);
					field.add(idfield);
					
					pDeleteDialog.add(label, BorderLayout.WEST);
					pDeleteDialog.add(field, BorderLayout.CENTER);
					
					int result = JOptionPane.showConfirmDialog(null, pDeleteDialog, "삭제", JOptionPane.OK_CANCEL_OPTION);
					if (result == JOptionPane.OK_OPTION) {
						aName.remove(i);
						aID1.remove(i);
						aID2.remove(i);
						aPhone.remove(i);
						aAddress.remove(i);
						taInfo.setText("삭제 완료");
						totalCnt--;
					}
				}
			}
		});
		bExit.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				System.exit(0);
			}
		});
		
		pRightButton.add(bRegister);
		pRightButton.add(bModify);
		pRightButton.add(bDelete);
		pRightButton.add(bExit);

		pRight.add(pRightButton, BorderLayout.SOUTH);
		
		// 오른쪽 마무리
		pRight.setBorder(new TitledBorder(new SoftBevelBorder(SoftBevelBorder.RAISED), "개인정보확인"));
		pBase.add(pRight);
		
		/////////// 끝
		
		setSize(1000, 500);
		setVisible(true);
	}

	public static void main(String[] args) {
		new UserManage();
	}

}
