import java.io.*;
import java.net.*;
import java.util.*;

public class NodeClient {
	
	public int nodeUpdateTime;//结点发送路径信息的时间间隔
	public int pathUpdateTime;//打印当前结点最短路径信息的时间间隔
	public int HBPacketTime;//发送心跳包的间隔时间
	private char nodeName;
//	private int nodeIndex;
	
	public static Map<Character,Object> directMap;
	
	public void setNode(char m) {
		nodeName = m;
//		nodeIndex = nodeName - 65;
	}
	
	//载入配置文件（nodeUpdateTime，pathUpdateTime，HBPacketTime）
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
	
	public NodeClient(char m) {
		
		nodeName = m;
//		nodeIndex = nodeName - 65;
		
		//载入配置文件（nodeUpdateTime，pathUpdateTime，HBPacketTime）
		assignmentLoader();
		
		//每隔HBPacketTime向直接相邻节点发送心跳包的线程
		//结点A的心跳包内容 <A,"HeartBeat">
		new Thread() {
			public void run() {
				while (true) {
					try {
						Map<Character,Object> m1 = new HashMap<Character,Object>();
						m1.put(nodeName, "HeartBeat");
						for (Iterator<Character> it = Node.originMap.keySet().iterator(); it.hasNext();) {
							char key = it.next();
							int portNum = (int) Node.portMap.get(key);
							NodeClient.send("127.0.0.1", portNum, m1);
						}
						sleep(HBPacketTime);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}.start();
		
		//每隔nodeUpdateTime向直接相连节点发送与当前结点直接相连的结点路径信息的线程
		//节点A发包的 directMap: <A,0>, <B,2>, <C,5>, <D,1>
		//来自A节点（value为0）的路由信息：
		//与A直接相连的节点有B，C，D；路径权重分别为2，5，1
		new Thread() {
			public void run() {
				while (true) {
					try {
						directMap = new TreeMap<Character,Object>();
						directMap.put(nodeName, 0);//先放入自己的节点
						for (Iterator<Character> it = Node.originMap.keySet().iterator(); it.hasNext();) {
							char key = it.next();
							int weight = (int) Node.originMap.get(key);
							directMap.put(key, weight);
						}
						for (Iterator<Character> it = directMap.keySet().iterator(); it.hasNext();) {
							char key = it.next();
							if(key == nodeName) continue;
							int portNum = (int) Node.portMap.get(key);
							NodeClient.send("127.0.0.1", portNum, directMap);
						}
						sleep(nodeUpdateTime);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}.start();
	}
	
	//向  IP地址ip、端口号 port 的结点发送 map
	public static void send(String ip, int port, Map<Character, Object> map) {
		try {
			byte[] data = convertMapToByteArray(map);

			DatagramSocket socket = new DatagramSocket();
			DatagramPacket packet = new DatagramPacket(data, data.length);

			packet.setSocketAddress(new InetSocketAddress(ip, port));
			socket.send(packet);
			socket.close();

		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	//把map转化为字节数组
	public static byte[] convertMapToByteArray(Map<Character, Object> map) {
		try {
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			ObjectOutputStream oos = new ObjectOutputStream(baos);
			oos.writeObject(map);
			oos.flush();
			oos.close();
			baos.close();
			return baos.toByteArray();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	//将字节数组转化回map
	public static Map<Character, Object> convertByteArrayToMap(byte[] data) {
		try {
			ByteArrayInputStream bais = new ByteArrayInputStream(data);
			ObjectInputStream ois = new ObjectInputStream(bais);
			Map<Character, Object> result = (Map<Character, Object>) ois.readObject();
			return result;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	
}
