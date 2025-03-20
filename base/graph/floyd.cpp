/**
 * @Time : 2023/4/26-8:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * floyd算法 时间复杂度n^3 空间复杂度n^2
     * 用于解决图中任意点之间的最短路问题
     * 入参：邻接矩阵
     *
     * 定义 dp[k][i][j] 表示通过子图G[k](结点编号1～k的子图)中的结点，i到j的最短路径长度。
     * i j 不一定在G[k]中
     * dp[k][i][j] = min(dp[k - 1][i][j], dp[k - 1][i][k] + dp[k - 1][k][j])
     * 第一种可能的方案：通过子图G[k-1]从i到j的最短路，不走结点k
     * 第二种可能的方案：现在可以经过k由i到j了，先通过子图G[k-1]从i到k，然后再通过子图G[k-1]从k到j。
     * 中间经过了点k，所以是通过子图G[k]才由此方案
     * 两种方案取最小
     *
     * 边界条件 如果dp[0][i][j]，不通过任何子图，由i到j
     * 那么dp[0][i][i] = 0 表示结点和自己的距离不经过任何子图，也是0
     * dp[0][i][j] = graph[i][j] ? graph[i][j] : 正无穷
     * 表示如果i，j不直接相连，那么他们不经过任何子图，无法到达，距离是正无穷。
     * 直接相连，则不通过任何子图，他们直接距离就是graph[i][j]
     *
     * 计算方向
     * 外层循环k，对结点编号枚举，但结点编号可以重排
     * 因此最外层的顺序可以是任意，只要是子图规模从1到n即可
     * 内层循环i，j，是枚举两个结点，只要将所有点对枚举一遍即可，顺序也可以是任意
     * 但是为了写得方便 都从1到n枚举（或者0到n-1枚举即可，具体看图中结点的编号）
     *
     * 另外，对于k这个维度，可以进行空间上的优化，dp[i][j]即可表示最短路径
     *
     * 注意
     * 1.因为外层循环k，是任意顺序，只是子图规模从小变大 因此可以解决图中动态加点的问题
     * 2.类似的 可以运用在动态添加边的最短路问题中
     */
    vector<vector<int>> dis;
    vector<vector<int>> path;
    void floyd(vector<vector<int>> graph) {
        // 默认graph[i][i] = 0, 如果i,j不直接相连graph[i][j] = INT_MAX;
        int n = graph.size();
        dis = vector(n, vector(n, INT_MAX));
        path =  vector(n, vector(n, -1));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
                dis[i][j] = graph[i][j];
        }
        for(int k = 0; k < n; k++){ // 枚举子图 规模从小到大，每次添加到子图中的点为k（这只是其中一种顺序）
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(dis[i][j] > dis[i][k] + dis[k][j])
                        path[i][j] = k, dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
};

/*
 * 动态加边的例子  LC2642
 * 首先维护好 floyd算法中的 dis[i][j]
 * 在动态加边 {v, w, cost} 时。
 * 枚举所有i,j
 * 对于 dis[i][j] 考虑 i -> v -> w -> j 的走法是否更短
 * 如果 cost >= dis[v][w] 则不用进行计算，因为在加入此边之前 v -> w 的路径权值已经更小了
 */
class Graph {
public:
    int n, max_val = (int)1e9;
    vector<vector<int>> dis;
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        dis = vector(n, vector(n, max_val));
        for(int i = 0; i < n; i++)
            dis[i][i] = 0;
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1], cost = edge[2];
            dis[v][w] = cost;
        }
        // floyd算法进行初始化
        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
    }
    // 添加有向边
    void addEdge(vector<int> edge) {
        int v = edge[0], w = edge[1], cost = edge[2];
        if(dis[v][w] <=  cost) return;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                dis[i][j] = min(dis[i][j], dis[i][v] + cost + dis[w][j]);
        }
    }

    int shortestPath(int node1, int node2) {
        return dis[node1][node2] == max_val ? -1 : dis[node1][node2];
    }
};

/*
 * floyd算法 同样可以处理可达性问题 同样可以使用动态加边
 * 将距离矩阵换成bool矩阵即可
 * 如lc 1462
 */
//public List<Boolean> checkIfPrerequisite(int n, int[][] edges, int[][] queries) {
//    boolean[][] con = new boolean[n][n]; // con[i][j]表示结点i和j是否联通
//    for(int i = 0; i < n; i++)
//        con[i][i] = true;
//    for(int[] edge : edges)
//    con[edge[0]][edge[1]] = true;
//    for(int k = 0; k < n; k++) {
//        for(int i = 0; i < n; i++) {
//            for(int j = 0; j < n; j++)
//                con[i][j] |= con[i][k] && con[k][j];
//        }
//    }
//    List<Boolean> res = new ArrayList();
//    for(int[] q : queries)
//    res.add(con[q[0]][q[1]]);
//    return res;
//}

int main(){
    Solution s;
    
    cout << 0 << endl;
}