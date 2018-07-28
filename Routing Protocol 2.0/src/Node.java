import java.io.*;
import java.net.*;
import java.util.*;

/*��ҵҪ��ͼ�����������룺
A 2000 configA.txt
B 2001 configB.txt
C 2002 configC.txt
D 2003 configD.txt
E 2004 configE.txt
F 2005 configF.txt
*/

/*����һ��ͼ�����������룺
A 3000 configG.txt
B 3001 configH.txt
C 3002 configI.txt
D 3003 configJ.txt
E 3004 configK.txt
F 3005 configL.txt
*/

public class Node {
	NodeClient nodeClient;
	static NodeServer nodeServer;
//	DataProcess dataProcess;
	public char nodeName;
	public int nodeIndex;
	public int port;
	//��ȡ�ڵ���Ϣ���ļ�·��
	private String txtPath;
	//ֱ�������Ľڵ�·����Ϣ
	public static Map<Character, Object> originMap = new LinkedHashMap<Character, Object>();
	//ֱ�������Ľڵ�˿���Ϣ
	public static Map<Character, Object> portMap = new TreeMap<Character, Object>();
	
	/**
	 * �����ڵ㣬��ʼ���ڵ��UDP�ͻ���
	 * @param n  �ڵ�����
	 * @param p  �ڵ�˿ں�
	 * @param t  �ڵ�·����Ϣ���ļ�·����.txt��
	 */
	public Node(String n, String p, String t) {
		nodeName  = n.charAt(0);
		nodeIndex = nodeName - 65;
		port = Integer.parseInt(p);
		txtPath = t;
		loadMap();//���� originMap �� portMap
		nodeClient = new NodeClient(nodeName);
	}
	
	public char getNodeName() {
		return nodeName;
	}
	
	//���� originMap �� portMap
	//�ڵ�A�� originMap: <B,2>, <C,5>, <D,1>
	//�ڵ�A�� portMap: <B,2001>, <C,2002>, <D,2003>
	public void loadMap() {
		try {
			FileInputStream fis = new FileInputStream(txtPath);
			InputStreamReader isr = new InputStreamReader(fis,"GBK");
			BufferedReader br = new BufferedReader(isr);
			String s = null;
			s = br.readLine();//�Ȱ�ֱ�������Ľڵ�������꣬��һ�вſ�ʼload Map
			while((s = br.readLine()) != null) {
				String[] str = s.split(" ");
				originMap.put(str[0].charAt(0),Integer.parseInt(str[1]));
				portMap.put(str[0].charAt(0),Integer.parseInt(str[2]));
			}
			br.close();
			isr.close();
			fis.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	//ÿ�����̴���һ��Node���ʵ�������д���һ����Ӧ��nodeClient���ʵ����, ����һ����Ӧ�� nodeServer�߳� 
	public static void main(String[] args) {
		
	new Thread() {
		synchronized public void run() {
			Node a = new Node(args[0], args[1], args[2]);
			Thread nodeServer = new NodeServer(a.nodeName,a.port);
			nodeServer.start();
		}
	}.start();
	
	//����̨���롰l"�ɴ�ӡ����ǰ�ڵ��Ӧ�����·����Ϣ
	new Thread() {
		synchronized public void run() {
			while (true) {
				String line = null;
				Scanner scanner = new Scanner(System.in);
				line = scanner.nextLine();
				if (line.equals("l")) {
					nodeServer.myInput();
				}
			}
		}
	}.start();
	}

}
