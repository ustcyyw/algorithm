/**
 * @Time : 2023/12/10-3:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛119 t4
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        this->n = n;
        int u = (1 << n) - 1, cnt = 1; // 状态为0表示要关闭的分部
        for(int s = u; s; s = (s - 1) & u) {
            vector<vector<int>> graph(n, vector(n, (int)1e9));
            for(auto& road : roads) {
                int v = road[0], w = road[1], dis = road[2];
                if((1 << v) & s && (1 << w) & s) // 没被关闭的两个点 才算其距离
                    graph[v][w] = graph[w][v] = min(graph[v][w], dis);
            }
            floyd(graph); // n才10 用floyd算法最好
            cnt += check(graph, s, maxDistance);
        }
        return cnt;
    }

    bool check(vector<vector<int>>& dis, int s, int maxDistance) {
        for(int i = 0; i < n; i++) {
            if(!((1 << i) & s)) continue;
            for(int j = i + 1; j < n; j++) {
                if((1 << j) & s && dis[i][j] > maxDistance)
                    return false;
            }
        }
        return true;
    }

    void floyd(vector<vector<int>>& dis) {
        // 默认graph[i][i] = 0, 如果i,j不直接相连graph[i][j] = INT_MAX;
        for(int k = 0; k < n; k++){ // 枚举子图 规模从小到大，每次添加到子图中的点为k（这只是其中一种顺序）
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(dis[i][j] > dis[i][k] + dis[k][j])
                        dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}