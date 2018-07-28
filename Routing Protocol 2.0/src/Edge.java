public class Edge{
    int weight;
    int startP;
    int endP;
    public void addEdge(int s,int e,int w){
        startP = s;
        endP = e;
        weight = w;
    }

    public boolean isBigger(Edge oneEdge){
        if(weight > oneEdge.weight)
            return true;
        else
            return false;
    }
};