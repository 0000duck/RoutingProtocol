import java.io.*;
import java.net.*;
import java.util.*;

public class NodeClient {
	
	public int nodeUpdateTime;//��㷢��·����Ϣ��ʱ����
	public int pathUpdateTime;//��ӡ��ǰ������·����Ϣ��ʱ����
	public int HBPacketTime;//�����������ļ��ʱ��
	private char nodeName;
//	private int nodeIndex;
	
	public static Map<Character,Object> directMap;
	
	public void setNode(char m) {
		nodeName = m;
//		nodeIndex = nodeName - 65;
	}
	
	//���������ļ���nodeUpdateTime��pathUpdateTime��HBPacketTime��
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
		
		//���������ļ���nodeUpdateTime��pathUpdateTime��HBPacketTime��
		assignmentLoader();
		
		//ÿ��HBPacketTime��ֱ�����ڽڵ㷢�����������߳�
		//���A������������ <A,"HeartBeat">
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
		
		//ÿ��nodeUpdateTime��ֱ�������ڵ㷢���뵱ǰ���ֱ�������Ľ��·����Ϣ���߳�
		//�ڵ�A������ directMap: <A,0>, <B,2>, <C,5>, <D,1>
		//����A�ڵ㣨valueΪ0����·����Ϣ��
		//��Aֱ�������Ľڵ���B��C��D��·��Ȩ�طֱ�Ϊ2��5��1
		new Thread() {
			public void run() {
				while (true) {
					try {
						directMap = new TreeMap<Character,Object>();
						directMap.put(nodeName, 0);//�ȷ����Լ��Ľڵ�
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
	
	//��  IP��ַip���˿ں� port �Ľ�㷢�� map
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

	//��mapת��Ϊ�ֽ�����
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

	//���ֽ�����ת����map
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
