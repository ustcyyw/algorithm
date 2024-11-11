/**
 * @Time : 2023/3/20-8:50 PM
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
     * 对于某一种颜色 其出现的上下左右四个方向的极值，就确定了这个颜色的矩形大小
     * 因此对于某种颜色，一次必须涂色至上下左右四个方向的极限位置，没有涂第二次的机会
     *
     * 那么在这种颜色v范围内的颜色w，一定是在v之后涂的
     * 这就确定了一种涂色顺序，有优先级之分 v -> w
     * 是否可以涂色成最终的结果，就是按涂色的优先级依次涂色，是否可以完成涂色
     * 将颜色看成结点，涂色顺序就是有向边
     *
     * 拓扑排序
     * 如果可以得出拓扑排序，就可以完成涂色
     * 是否有拓扑排序，就取决于该有向图中是否存在环
     *
     */
    bool isPrintable(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // range 四个元素分别表示上下左右
        vector<vector<int>> range(61, vector(4, -1));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int c = grid[i][j];
                if(range[c][0] == -1){
                    range[c][0] = range[c][1] = i;
                    range[c][2] = range[c][3] = j;
                } else {
                    range[c][0] = min(range[c][0], i), range[c][1] = max(range[c][1], i);
                    range[c][2] = min(range[c][2], j), range[c][3] = max(range[c][3], j);
                }
            }
        }
        // 查找各个颜色区域内的其它颜色，建有向图
        vector<vector<int>> graph(61, vector(0, 0));
        for(int i = 0; i < 61; i++)
            if(range[i][0] != -1) build(grid, graph, range[i], i);
        // 查看是否有环
        vector<int> degree(61, 0);
        for(int i = 0; i < 61; i++){
            for(int w : graph[i]) // 如果某种颜色不存在，那么graph[i]为空集 不影响存在的颜色对应结点的度数
                degree[w]++;
        }
        queue<int> queue;
        for(int i = 0; i < 61; i++)
            if(degree[i] == 0) queue.push(i);
        while (!queue.empty()){
            int v = queue.front();
            for(int w : graph[v])
                if(--degree[w] == 0) queue.push(w);
            queue.pop();
        }
        for(int i = 0; i < 61; i++)
            if(degree[i] > 0) return false;
        return true;
    }

    void build(vector<vector<int>>& grid, vector<vector<int>>& graph, vector<int>& range, int v){
        vector<bool> marked(61, false);
        for(int i = range[0]; i <= range[1]; i++){
            for(int j = range[2]; j <= range[3]; j++){
                int w = grid[i][j];
                if(w == v || marked[w]) continue;
                marked[w] = true;
                graph[v].push_back(w); // w在v之后涂色
            }
        }
    }

};

int main(){
    Solution s;
    
    cout << 0 << endl;
}