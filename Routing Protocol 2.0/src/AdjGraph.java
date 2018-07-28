public class AdjGraph {
	final int INFINITY=1000;
	int verNum;
	int edgeNum;
	int[][] matrix;
	int[] mark;

	AdjGraph(int v){
		verNum = v;
	    edgeNum = 0;
		mark = new int[verNum];
		matrix = new int[verNum][verNum];
	    for(int i = 0; i < verNum; i++)
	    	mark[i] = 0;//标记数组 0未访问， 1已访问
	    int i, j;
	    for(i = 0; i < verNum; i++)
	        for(j = 0; j < verNum; j++)
	        	matrix[i][j] = INFINITY;//邻接矩阵初始化
	}
	public void showMatrix(){
	   for(int i = 0; i < verNum; i++){
	       for(int j = 0; j < verNum; j++){
	    	   System.out.print("  ");
	           if(matrix[i][j]==INFINITY)
	        	   System.out.print("∞");
	            else
	            	System.out.print(matrix[i][j]);
	       }
			System.out.println();
	   }
		System.out.println();
	}
	public int getVerNum(){    return verNum;}
	public int getEdgeNum(){    return edgeNum;}
	public int getStartP(Edge oneEdge){return oneEdge.startP;}
	public int getEndP(Edge oneEdge){return oneEdge.endP;}
	public int getWeight(Edge oneEdge) {return oneEdge.weight;}
	
	public void setEdge(char a, char b, int w) {
		int s = a - 65;
		int e = b - 65;
	    if(matrix[s][e] == INFINITY)
	        edgeNum++;
	    matrix[s][e] = w;
	}
	public void disableVertex(char v) {//v节点crash
		int v_index = v - 65;
		for(int i = 0; i < verNum; i++) {
			if(matrix[i][v_index] != INFINITY) {
				matrix[i][v_index] = INFINITY;
				edgeNum--;
			}
			matrix[v_index][i] = INFINITY;
		}
	}
	public boolean isLastEdge(Edge oneEdge){//判断是不是DFS中某点出发的最后一条边
	    int icounter = 0;
	    for(int i = oneEdge.endP+1; i < verNum; i++){
	        if(matrix[oneEdge.startP][i] != INFINITY&&matrix[oneEdge.startP][i] != 0){
	            icounter++;
	            break;
	        }
	    }
	    if(mark[oneEdge.endP] == 1 && oneEdge.endP == verNum-1)
	        return true;
	    if(matrix[oneEdge.startP][oneEdge.endP] != INFINITY && icounter == 0)
	        return true;
	    else
	        return false;
	}
	public boolean isEdge(Edge oneEdge){
	    if(oneEdge.weight==INFINITY||oneEdge.weight==0||oneEdge.endP<0 && oneEdge.endP>= verNum)
	        return false;
	    else
	        return true;
	}
	public Edge firstEdge(int v) {
	    Edge tmpEdge = new Edge();
	    tmpEdge.startP = v;
	    tmpEdge.endP = 0;
	    tmpEdge.weight = INFINITY;
	    for(int i = 0; i < verNum; i++){
	        if(matrix[v][i]!=INFINITY&&matrix[v][i]!=0){
	            tmpEdge.endP = i;
	            tmpEdge.weight = matrix[v][i];
	            break;
	        }
	    }
	    return tmpEdge;
	}
	public Edge nextEdge(Edge preEdge) {
	    Edge tmpEdge = new Edge();
	    tmpEdge.startP = preEdge.startP;

	    if(isLastEdge(preEdge)){
	        for(int i = 0; i < verNum; i++){
	            if(matrix[tmpEdge.startP][i]==INFINITY||matrix[tmpEdge.startP][i]==0){
	                tmpEdge.endP = i;
	                tmpEdge.weight = matrix[tmpEdge.startP][i];
	                break;
	            }
	        }
	    }
	    else{
	        for(int i = preEdge.endP+1; i < verNum; i++){
	            if(matrix[tmpEdge.startP][i]!=INFINITY&&matrix[tmpEdge.startP][i]!=0){
	                tmpEdge.endP = i;
	                tmpEdge.weight = matrix[tmpEdge.startP][i];
	                break;
	            }
	        }
	    }
	    return tmpEdge;
	}
	
	
	public void getPath(Dist[] D,int s){
	    int i = 0;
	    int[] arr = new int[10];
	    if(D[s].pre == s){
	    	System.out.println((char)(s+65));
	        return;
	    }
	    else{
	        arr[i++] = s;
	        for(;D[s].pre != -1; s = D[s].pre)
	            arr[i++] = D[s].pre;
		        for(i = i-1; i >= 0; i--) 
		        	System.out.print((char)(arr[i]+65));
	    }
	}
	
	public int minVertex(AdjGraph G, Dist[] D){
	    int minD = INFINITY, index = 0;
	    for(int i = 0; i < G.getVerNum();i++){
	        if(G.mark[i] == 0){
	            if(D[i].len < minD){
	                minD = D[i].len;
	                index = i;
	            }
	        }
	    }
	    return index;
	}
	
	public void Dijkstra(AdjGraph G,int s) {
	    Dist[] D=new Dist[G.getVerNum()];
		for(int i = 0; i < G.getVerNum(); i++){
	       G.mark[i] = 0;
	       D[i] = new Dist();
	       D[i].len = INFINITY;
	       D[i].pre = -1;
	    }
	    G.mark[s] = 1;
	    D[s].len = 0;
	    for(Edge e = G.firstEdge(s);G.isEdge(e); e = G.nextEdge(e)){
	        D[e.endP].len = e.weight;
	        D[e.endP].pre = s;
	    }
	    for(int i = 0; i < G.getVerNum(); i++){
	        int v = minVertex(G,D);     //找到距离s最小的顶点
	        if(D[v].len == INFINITY)
	            break;
	        G.mark[v] = 1;
	        for(Edge e = G.firstEdge(v); G.isEdge(e);e = G.nextEdge(e)){
	            if(D[G.getEndP(e)].len > (D[v].len+G.getWeight(e))){
	                D[G.getEndP(e)].len = D[v].len+G.getWeight(e);
	                D[G.getEndP(e)].pre = v;
	            }
	        }
	    }
	    for(int j = 0; j < G.getVerNum(); j++){
	    	if(j == s)
	    		continue;
	    	System.out.print("least-cost path to node ");
	    	System.out.print((char)(j+65));
	    	System.out.print("  path: ");
	        G.getPath(D,j);
	    	System.out.print(" and the cost is ");
	    	if(D[j].len == INFINITY)
	    		System.out.println('∞');
	    	else 
	    		System.out.println(D[j].len);
	    }
	}
	
//	public static void main(String[] args) {
//	    AdjGraph G = new AdjGraph(6);
//	    G.setEdge('A','B',2);
//	    G.setEdge('A','C',5);
//	    G.setEdge('A','D',1);
//	    G.setEdge('B','A',2);
//	    G.setEdge('B','C',3);
//	    G.setEdge('B','D',2);
//	    G.setEdge('C','A',5);
//	    G.setEdge('C','B',3);
//	    G.setEdge('C','D',3);
//	    G.setEdge('C','E',1);
//	    G.setEdge('C','F',5);
//	    G.setEdge('D','A',1);
//	    G.setEdge('D','B',2);   
//	    G.setEdge('D','C',3);
//	    G.setEdge('D','E',1);
//	    G.setEdge('E','C',1);
//	    G.setEdge('E','D',1);
//	    G.setEdge('E','F',2);
//	    G.setEdge('F','C',5);
//	    G.setEdge('F','E',2);
//	    G.disableVertex('B');
//	    G.showMatrix();
//	    
//	    G.Dijkstra(G,0);
//	}
}
