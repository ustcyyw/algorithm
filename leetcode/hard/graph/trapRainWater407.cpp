/**
 * @Time : 2022/8/31-8:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
    /**
     * 针对格子进行考虑，某个格子的高度为h[i][j]
     * 定义路径高度：某一条路径上所有格子高度的最大值
     * 其所能存放的水取决于它到边界的所有路线中，经过的路径高度的最小值（木桶短板）记为maxH[i][j]
     * 注意：由于该点的路径起点高度就是h[i][j]，因此maxH[i][j] >= h[i][j]
     *
     * 如果是计算点(x,y)到边界的最小路径和，可以使用dijkstra来对每一个点进行计算
     * 但我们要求的是路径高度的最小值，不能直接套用
     *
     * 点(x,y)到边界的路径高度的最小值，与边界到点(x,y)的路径高度的最小值等价
     * 计算转化为从边界向内计算
     * dijkstra是单源最短路径算法，所以这里引入超级源点来将多个边界起点转化为单一起点
     * 超级源点的高度为0，与每一个边界格子相临接
     *
     * 在求最短路径的时候，是对路径和进行松弛，每次选择的边，使得经过该边的非最短路径树顶点到源点距离最短
     * 本题中，对高度进行松弛，每次选择的点，使得该点的临接点最大高度变大，但变大幅度是最小的
     * 于是每次选择的点应该是当前高度最小的点，然后更新临接点的高度 max(h[i1][j1], maxH[i0][j0])
     * 然后将更新后的高度再次放入优先队列
     * 于是从超级源点出发，会将每个边界点的最大高度最小值更新为其本身的高度
     * 等价于初始时候将所有边界加入队列
     */
    const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
public:
    int trapRainWater(vector<vector<int>>& height) {
        int n = height.size(), m = height[0].size();
        vector<vector<int>> maxH(n, vector(m, 0));
        // dijkstra中需要标记某个点是否在最短路径数中，本题类似，标记某个点是否已访问过
        vector<vector<bool>> marked(n, vector(m, false));
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for(int i = 0; i < n; i++){
            pq.push({height[i][0], i, 0}), pq.push({height[i][m - 1], i, m - 1});
            marked[i][0] = true, marked[i][m - 1] = true;
        }
        for(int i = 1; i < m - 1; i++){
            pq.push({height[0][i], 0, i}), pq.push({height[n - 1][i], n - 1, i});
            marked[0][i] = true, marked[n - 1][i] = true;
        }
        while (!pq.empty()){
            auto& cur = pq.top();
            int h = cur[0], x = cur[1], y = cur[2];
            pq.pop();
            for(int i = 0; i < 4; i++){
                int nx = x + dx[i], ny = y + dy[i];
                if(nx < 0 || ny < 0 || nx > n - 1 || ny > m - 1 || marked[nx][ny]) continue;
                maxH[nx][ny] = max(height[nx][ny], h);
                marked[nx][ny] = true;
                pq.push({maxH[nx][ny], nx, ny});
            }
        }
        int res = 0;
        for(int i = 1; i < n - 1; i++){
            for(int j = 1; j < m - 1; j++)
                res += maxH[i][j] - height[i][j];
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}