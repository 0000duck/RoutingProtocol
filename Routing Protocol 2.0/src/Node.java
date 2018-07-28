import java.io.*;
import java.net.*;
import java.util.*;

/*作业要求图的命令行输入：
A 2000 configA.txt
B 2001 configB.txt
C 2002 configC.txt
D 2003 configD.txt
E 2004 configE.txt
F 2005 configF.txt
*/

/*另外一张图的命令行输入：
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
	//读取节点信息的文件路径
	private String txtPath;
	//直接相连的节点路径信息
	public static Map<Character, Object> originMap = new LinkedHashMap<Character, Object>();
	//直接相连的节点端口信息
	public static Map<Character, Object> portMap = new TreeMap<Character, Object>();
	
	/**
	 * 构建节点，初始化节点的UDP客户端
	 * @param n  节点名字
	 * @param p  节点端口号
	 * @param t  节点路径信息的文件路径（.txt）
	 */
	public Node(String n, String p, String t) {
		nodeName  = n.charAt(0);
		nodeIndex = nodeName - 65;
		port = Integer.parseInt(p);
		txtPath = t;
		loadMap();//载入 originMap 和 portMap
		nodeClient = new NodeClient(nodeName);
	}
	
	public char getNodeName() {
		return nodeName;
	}
	
	//载入 originMap 和 portMap
	//节点A的 originMap: <B,2>, <C,5>, <D,1>
	//节点A的 portMap: <B,2001>, <C,2002>, <D,2003>
	public void loadMap() {
		try {
			FileInputStream fis = new FileInputStream(txtPath);
			InputStreamReader isr = new InputStreamReader(fis,"GBK");
			BufferedReader br = new BufferedReader(isr);
			String s = null;
			s = br.readLine();//先把直接相连的节点个数读完，下一行才开始load Map
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
	
	//每个进程创建一个Node类的实例（其中创建一个对应的nodeClient类的实例）, 运行一个对应的 nodeServer线程 
	public static void main(String[] args) {
		
	new Thread() {
		synchronized public void run() {
			Node a = new Node(args[0], args[1], args[2]);
			Thread nodeServer = new NodeServer(a.nodeName,a.port);
			nodeServer.start();
		}
	}.start();
	
	//控制台输入“l"可打印出当前节点对应的最短路径信息
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
