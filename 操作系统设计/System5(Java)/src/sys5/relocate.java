package sys5;
import java.awt.*;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.text.DecimalFormat;  
import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableModel;
import java.awt.*;
import java.text.DecimalFormat;  
import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;

public class relocate extends JFrame implements ActionListener,WindowListener{
	
	public JLabel label1=new JLabel("        ָ�����߼���ַ��ʮ���ƣ���");
	public JLabel label2=new JLabel("        �����ַ�Ĵ�����ʮ���ƣ���");
	public JLabel label3=new JLabel("        ҳ�ţ�");
	public JLabel label4=new JLabel("        ҳ��ƫ��:");
	public JTextField field1=new JTextField();
	public JTextField field2=new JTextField();
	public JTextField field3=new JTextField();
	public JTextField field4=new JTextField();
	//public pageTable ptable=new pageTable();
	//public pageTable tableModel = new pageTable();
	public JTable table;
	JScrollPane jsp = new JScrollPane(table);
	public JButton button1=new JButton("����");
	public JPanel panel1=new JPanel();
	public JPanel panel2=new JPanel();
	int pnum=4;
	String[] columnNames= {
			"ҳ��",
			"������",
			};
	Object[][] data1= {
				{0,22},
				{1,3},
				{2,5},
				{3,31},
				{4,13},
				{5,23},
				{6,20},
				{7,9},
				{8,22},
				{9,31},
				{10,17},
				{11,15},
				{12,16},
				{13,12},
				{14,4},
				{15,11}
				};
	int[][] data= {
			{0,22},
			{1,3},
			{2,5},
			{3,31},
			{4,13},
			{5,23},
			{6,20},
			{7,9},
			{8,22},
			{9,31},
			{10,17},
			{11,15},
			{12,16},
			{13,12},
			{14,4},
			{15,11}
			};
	
	private class aaa extends WindowAdapter{
		public void windowClosing(WindowEvent we){
			System.exit(0);
		}
	}
  
	public relocate() {
		super();
		
		setLayout(new BorderLayout());
		panel1.setLayout(new GridLayout(2,2));
		addWindowListener(new aaa());
		//TableModel tableModel;
		table=new JTable(data1,columnNames);
		//table.setModel(tableModel);
		panel1.add(label1);
		panel1.add(field1);
		panel1.add(label2);
		panel1.add(field2);
		panel1.add(label3);
		panel1.add(field3);
		panel1.add(label4);
		panel1.add(field4);
		add("North",panel1);
		add("Center",table);
		add("South",button1);
		pack();
		setVisible(true);
		setSize(800, 400);
		setLocation(340,200);
		button1.addActionListener((ActionListener) this);
		
	}
	
	
	
	public void actionPerformed(ActionEvent e) {
		if(e.getSource()==button1)
		{
			if(field1.getText().equals("")) 
			{
				JOptionPane.showMessageDialog(null,"�߼���ַ����Ϊ�գ�");
				
			}
			else
			{
				int logAddr=Integer.parseInt(field1.getText());
				int pageNum=logAddr/16;
				int offset=logAddr%16;
				int row=data.length;
				int col=data[0].length;
				int phyNum=0;
				//
				field3.setText(String.valueOf(pageNum));
				field4.setText(String.valueOf(offset));
				//if(data[pageNum][1]=="-1") {
				//	JOptionPane.showMessageDialog(null,"����ҳ����");
				//}
				//else {
				if(pageNum>pnum) {
					JOptionPane.showMessageDialog(null,"����Խ���жϣ�");
				}
				else {
					phyNum=data[pageNum][1];
					field2.setText(String.valueOf(offset+phyNum*16));
				}
					
				//}
				
			}
		}
	}
	
	public static void main(String args[])
	{
		relocate rlc=new relocate();
		
	}



	@Override
	public void windowOpened(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void windowClosing(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void windowClosed(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void windowIconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void windowDeiconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void windowActivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void windowDeactivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}
}
