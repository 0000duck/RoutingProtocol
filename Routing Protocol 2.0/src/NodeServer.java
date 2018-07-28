import java.io.*;
import java.net.*;
import java.util.*;

public class NodeServer extends Thread {
	
	private int port;
	private static char nodeName;
	private static int nodeIndex;
	public static int nodeUpdateTime;//结点发送路径信息的时间间隔
	public int pathUpdateTime;//打印当前结点最短路径信息的时间间隔
	public static int HBPacketTime;//心跳包发包时间间隔
	
	//收到过哪些节点的路径信息（记录上线过的节点）
	public static Set<Character> from = new HashSet<Character>();//?
	//记录宕机节点
	public static Map<Character, Object> deadMap = new TreeMap<Character, Object>();
	//用于测试该节点的邻居是否宕机
	public static Map<Character, Integer> onlineNodesMap = new TreeMap<Character, Integer>();
	//用于生成网络图
	public static Map<String, Integer> routingMap = new HashMap<String, Integer>();
	
	public static Map<Character, Object> directMap = new TreeMap<Character, Object>();

	//载入配置信息(nodeUpdateTime,pathUpdateTime,HBPacketTime)
	public void assignmentLoader() {
		try {
			Properties p = new Properties();
			p.load(new FileInputStream("assignment.properties"));
			nodeUpdateTime = Integer.parseInt(p.getProperty("nodeUpdateTime"));
			pathUpdateTime = Integer.parseInt(p.getProperty("pathUpdateTime"));
			HBPacketTime = Integer.parseInt(p.getProperty("HBPacketTime"));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public NodeServer(char n, int p) {
		nodeName = n;
		nodeIndex = nodeName - 65;
		port = p;
		//载入配置信息
		assignmentLoader();
		// NodeServer.directMap初始化
		directMap.put(nodeName, 0);// 先放入自己的节点
		for (Iterator<Character> it = Node.originMap.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			int weight = (int) Node.originMap.get(key);
			directMap.put(key, weight);
		}
		// routingMap初始化
		//结点A初始化后的routingMap: <AB,2>, <AC,5>, <AD,1>
		char[] c = new char[2];
		c[0] = nodeName;
		for (Iterator<Character> it = directMap.keySet().iterator(); it.hasNext();) {
			c[1] = it.next();
			if (c[1] == c[0])//如果是自身节点 就跳过
				continue;
			String s = String.copyValueOf(c);
			routingMap.put(s, (int) directMap.get(c[1]));
		}

		//每隔 HBPacketTime 将所有在onlineNodesMap中的节点(除自身节点)对应的value值减1
		new Thread() {
			synchronized public void run() {
				while (true) {
					try {
						for (Iterator<Character> it = NodeServer.onlineNodesMap.keySet().iterator(); it.hasNext();) {
							char key = it.next();
							if (key == nodeName)
								continue;
							NodeServer.onlineNodesMap.put(key, NodeServer.onlineNodesMap.get(key) - 1);
						}
						sleep(HBPacketTime);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}.start();
		
		// 每隔 nodeUpdateTime 判断节点是否宕机 并向相邻结点广播宕机结点
		new Thread() {
			synchronized public void run() {
				while (true) {
					try {
						for (Iterator<Character> it = NodeServer.onlineNodesMap.keySet().iterator(); it.hasNext();) {
							char key = it.next();
							if (NodeServer.onlineNodesMap.get(key) < -30) {
								deadMap.put(key, "dead");
							}
						}
						for (Iterator<Character> ite = Node.originMap.keySet().iterator(); ite.hasNext();) {
							char k = ite.next();
							int portNum = (int) Node.portMap.get(k);
							NodeClient.send("127.0.0.1", portNum, deadMap);
						}
						sleep(nodeUpdateTime);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}.start();

		// 每隔pathUpdateTime 根据routingMap生成网络图
		new Thread() {
			synchronized public void run() {
				while (true) {
					try {
						System.out.println("========== least-cost path from " + nodeName + " ==========");
						AdjGraph G = new AdjGraph(6);
						for (Iterator<String> it = routingMap.keySet().iterator(); it.hasNext();) {
							String key = it.next();
							char[] nodes = key.toCharArray();
							if (from.contains(nodes[0]) && from.contains(nodes[1]))
								G.setEdge(nodes[0], nodes[1], routingMap.get(key));
							if (from.contains(nodes[0]) && nodes[1] == nodeName)
								G.setEdge(nodes[0], nodes[1], routingMap.get(key));
							if (from.contains(nodes[1]) && nodes[0] == nodeName)
								G.setEdge(nodes[0], nodes[1], routingMap.get(key));
						}
						//将宕机的节点从图中去除
						for (Iterator<Character> it = deadMap.keySet().iterator(); it.hasNext();) {
							Character key = it.next();
							G.disableVertex(key);
						}
						G.Dijkstra(G, nodeIndex);
						sleep(pathUpdateTime);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}.start();
	}

	//节点服务器不断接收包 并创建线程处理接收到的map
	public void run() {
		try {
			DatagramSocket serverSocket = new DatagramSocket(port);// 在port端口接受消息
			System.out.println(nodeName + "NodeServer started.");

			while (true) {
				byte[] buffer = new byte[1024 * 16];
				DatagramPacket recvPacket = new DatagramPacket(buffer, buffer.length);
				serverSocket.receive(recvPacket);

				byte[] recvData = new byte[recvPacket.getLength()];
				System.arraycopy(buffer, 0, recvData, 0, recvData.length);

				Map<Character, Object> map = NodeClient.convertByteArrayToMap(recvData);
				//创建线程处理收到的数据
				Thread dataProcess = new DataProcess(nodeName, port, map);
				dataProcess.start();
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	// 自己输入的控制台输出最短路径函数
	public static void myInput() {
		System.out.println("====== [myInput] === least-cost path from " + nodeName + " =====");
		AdjGraph G = new AdjGraph(6);
		for (Iterator<String> it = routingMap.keySet().iterator(); it.hasNext();) {
			String key = it.next();
			char[] nodes = key.toCharArray();
			if (from.contains(nodes[0]) && from.contains(nodes[1]))
				G.setEdge(nodes[0], nodes[1], routingMap.get(key));
			if (from.contains(nodes[0]) && nodes[1] == nodeName)
				G.setEdge(nodes[0], nodes[1], routingMap.get(key));
			if (from.contains(nodes[1]) && nodes[0] == nodeName)
				G.setEdge(nodes[0], nodes[1], routingMap.get(key));
		}
		//将宕机的节点从图中去除
		for (Iterator<Character> it = deadMap.keySet().iterator(); it.hasNext();) {
		Character key = it.next();
		G.disableVertex(key);
	}
		G.Dijkstra(G, nodeIndex);
	};
}
