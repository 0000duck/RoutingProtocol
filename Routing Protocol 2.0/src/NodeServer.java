import java.io.*;
import java.net.*;
import java.util.*;

public class NodeServer extends Thread {
	
	private int port;
	private static char nodeName;
	private static int nodeIndex;
	public static int nodeUpdateTime;//��㷢��·����Ϣ��ʱ����
	public int pathUpdateTime;//��ӡ��ǰ������·����Ϣ��ʱ����
	public static int HBPacketTime;//����������ʱ����
	
	//�յ�����Щ�ڵ��·����Ϣ����¼���߹��Ľڵ㣩
	public static Set<Character> from = new HashSet<Character>();//?
	//��¼崻��ڵ�
	public static Map<Character, Object> deadMap = new TreeMap<Character, Object>();
	//���ڲ��Ըýڵ���ھ��Ƿ�崻�
	public static Map<Character, Integer> onlineNodesMap = new TreeMap<Character, Integer>();
	//������������ͼ
	public static Map<String, Integer> routingMap = new HashMap<String, Integer>();
	
	public static Map<Character, Object> directMap = new TreeMap<Character, Object>();

	//����������Ϣ(nodeUpdateTime,pathUpdateTime,HBPacketTime)
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
		//����������Ϣ
		assignmentLoader();
		// NodeServer.directMap��ʼ��
		directMap.put(nodeName, 0);// �ȷ����Լ��Ľڵ�
		for (Iterator<Character> it = Node.originMap.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			int weight = (int) Node.originMap.get(key);
			directMap.put(key, weight);
		}
		// routingMap��ʼ��
		//���A��ʼ�����routingMap: <AB,2>, <AC,5>, <AD,1>
		char[] c = new char[2];
		c[0] = nodeName;
		for (Iterator<Character> it = directMap.keySet().iterator(); it.hasNext();) {
			c[1] = it.next();
			if (c[1] == c[0])//���������ڵ� ������
				continue;
			String s = String.copyValueOf(c);
			routingMap.put(s, (int) directMap.get(c[1]));
		}

		//ÿ�� HBPacketTime ��������onlineNodesMap�еĽڵ�(������ڵ�)��Ӧ��valueֵ��1
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
		
		// ÿ�� nodeUpdateTime �жϽڵ��Ƿ�崻� �������ڽ��㲥崻����
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

		// ÿ��pathUpdateTime ����routingMap��������ͼ
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
						//��崻��Ľڵ��ͼ��ȥ��
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

	//�ڵ���������Ͻ��հ� �������̴߳�����յ���map
	public void run() {
		try {
			DatagramSocket serverSocket = new DatagramSocket(port);// ��port�˿ڽ�����Ϣ
			System.out.println(nodeName + "NodeServer started.");

			while (true) {
				byte[] buffer = new byte[1024 * 16];
				DatagramPacket recvPacket = new DatagramPacket(buffer, buffer.length);
				serverSocket.receive(recvPacket);

				byte[] recvData = new byte[recvPacket.getLength()];
				System.arraycopy(buffer, 0, recvData, 0, recvData.length);

				Map<Character, Object> map = NodeClient.convertByteArrayToMap(recvData);
				//�����̴߳����յ�������
				Thread dataProcess = new DataProcess(nodeName, port, map);
				dataProcess.start();
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	// �Լ�����Ŀ���̨������·������
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
		//��崻��Ľڵ��ͼ��ȥ��
		for (Iterator<Character> it = deadMap.keySet().iterator(); it.hasNext();) {
		Character key = it.next();
		G.disableVertex(key);
	}
		G.Dijkstra(G, nodeIndex);
	};
}
