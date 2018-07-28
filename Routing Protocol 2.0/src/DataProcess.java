import java.io.*;
import java.util.*;

public class DataProcess extends Thread{
	private int port;
	private static char nodeName;
	private static int nodeIndex;
	public int nodeUpdateTime;
	public int pathUpdateTime;
	public int HBPacketTime;
	// 当前在线节点，用于测试节点是否宕机
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
			//如果收到了心跳包
			if (rec.values().contains("HeartBeat")) { 
				// 处理心跳包
				dealWithHB(rec);
			}
			//如果收到了宕机信息
			if (rec.values().contains("dead")) {
				//处理收到的节点宕机信息
				for (Iterator<Character> it = rec.keySet().iterator(); it.hasNext();) {
					char key = it.next();
					NodeServer.deadMap.put(key,"dead");
				}
				//向直接相连节点转播宕机信息
				for (Iterator<Character> it = NodeServer.directMap.keySet().iterator(); it.hasNext();) {
					char key = it.next();
					if (key == nodeName)
						continue;
					int portNum = (int) Node.portMap.get(key);
					NodeClient.send("127.0.0.1", portNum, rec);
				}
			} 
			//如果收到了路径信息
			if(!rec.values().contains("HeartBeat") && !rec.values().contains("dead")) {
				//处理路径信息
				addRoutingMap(rec);
				//转发路径信息
				forwardMap(rec);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	//載入配置文件
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

	//处理心跳包
	synchronized public void dealWithHB(Map<Character, Object> map) {
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			NodeServer.onlineNodesMap.put(key, 3);
		}
	}
	
	//处理路径信息
	synchronized public void addRoutingMap(Map<Character, Object> map) {
		char[] c = new char[2];
		// 获取消息来源
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			if ((int) map.get(key) == 0) {
				c[0] = key;
				NodeServer.from.add(key);
				break;
			}
		}
		//把路径信息加入routingMap
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			c[1] = it.next();
			if (c[1] == c[0]) continue;
			String s = String.copyValueOf(c);
			NodeServer.routingMap.put(s, (int) map.get(c[1]));
		}
	}
	
	//转发路径信息
	synchronized public void forwardMap(Map<Character, Object> map) {
		char from = 0;
		//确定消息来源
		for (Iterator<Character> it = map.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			if ((int) map.get(key) == 0) {
				from = key;
				break;
			}
		}
		//把路径信息转发给除发来的节点和自身节点之外的直接相连节点
		for (Iterator<Character> it = NodeServer.directMap.keySet().iterator(); it.hasNext();) {
			char key = it.next();
			if (key == from || key == nodeName)
				continue;
			int portNum = (int) Node.portMap.get(key);
			NodeClient.send("127.0.0.1", portNum, map);
		}
	}
}
