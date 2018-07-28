import java.io.*;
import java.util.*;

public class DataProcess extends Thread{
	private int port;
	private static char nodeName;
	private static int nodeIndex;
	public int nodeUpdateTime;
	public int pathUpdateTime;
	public int HBPacketTime;
	// ��ǰ���߽ڵ㣬���ڲ��Խڵ��Ƿ�崻�
	public Map<Character, Object> rec = new HashMap<Character, Object>();
	
	public DataProcess(char n, int p, Map<Character,Object> map) {
		nodeName = n;
		nodeIndex = nodeName - 65;
		port = p;
		assignmentLoader();
		rec = map;
	}
	
	public void run() {
		try {
			//����յ���������
			if (rec.values().contains("HeartBeat")) { 
				// ����������
				dealWithHB(rec);
			}
			//����յ���崻���Ϣ
			if (rec.values().contains("dead")) {
				//�����յ��Ľڵ�崻���Ϣ
				for (Iterator<Character> it = rec.keySet().iterator(); it.hasNext();) {
					char key = it.next();
					NodeServer.deadMap.put(key,"dead");
				}
				//��ֱ�������ڵ�ת��崻���Ϣ
				for (Iterator<Character> it = NodeServer.directMap.keySet().iterator(); it.hasNext();) {
					char key = it.next();
					if (key == nodeName)
						continue;
					int portNum = (int) Node.portMap.get(key);
					NodeClient.send("127.0.0.1", portNum, rec);
				}
			} 
			//����յ���·����Ϣ
			if(!rec.values().contains("HeartBeat") && !rec.values().contains("dead")) {
				//����·����Ϣ
				addRoutingMap(rec);
				//ת��·����Ϣ
				forwardMap(rec);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	//�d�������ļ�
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

	//����������
	synchronized public void dealWithHB(Map<Character, Object> map) {
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			NodeServer.onlineNodesMap.put(key, 3);
		}
	}
	
	//����·����Ϣ
	synchronized public void addRoutingMap(Map<Character, Object> map) {
		char[] c = new char[2];
		// ��ȡ��Ϣ��Դ
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			if ((int) map.get(key) == 0) {
				c[0] = key;
				NodeServer.from.add(key);
				break;
			}
		}
		//��·����Ϣ����routingMap
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			c[1] = it.next();
			if (c[1] == c[0]) continue;
			String s = String.copyValueOf(c);
			NodeServer.routingMap.put(s, (int) map.get(c[1]));
		}
	}
	
	//ת��·����Ϣ
	synchronized public void forwardMap(Map<Character, Object> map) {
		char from = 0;
		//ȷ����Ϣ��Դ
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			if ((int) map.get(key) == 0) {
				from = key;
				break;
			}
		}
		//��·����Ϣת�����������Ľڵ������ڵ�֮���ֱ�������ڵ�
		for (Iterator<Character> it = NodeServer.directMap.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			if (key == from || key == nodeName)
				continue;
			int portNum = (int) Node.portMap.get(key);
			NodeClient.send("127.0.0.1", portNum, map);
		}
	}
}
