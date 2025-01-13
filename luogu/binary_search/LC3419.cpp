/**
 * @Time : 2025/1/12-8:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3419 二分答案 逆向思维 bfs
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 最大边权最小 二分答案 val
     * 首先将所有边权 <= val的边进行建图
     * 条件1在反图中就是指 从0出发可以通过这些边到达所有结点
     * 条件3规定了在原图中的出度，也就是反图中的入度
     * 以bfs的方式来遍历 那么从0出发第一轮访问的点 其在反图中的入度为1
     * 也就是原图中的出度为1 肯定 <= threshold
     * 然后再从第一轮访问的点继续遍历，第二轮访问的点同理
     * 因此以bfs的方式访问到的点 在原图中只需要出度为1即可 肯定满足条件三
     * 在不关心如何选择边的情况下，bfs和dfs在搜索上的效果都一样 因此以dfs来写会更方便
     */
    int n;
    vector<vector<int>> edges;
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        this->edges = edges, this->n = n;
        int lo = 1, hi = 1e6 + 1;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo == 1e6 + 1 ? -1 : lo;
    }

    bool check(int val) {
        vector<vector<int>> graph(n);
        vector<bool> marked(n, false);
        for(auto& edge : edges) {
            if(edge[2] <= val)
                graph[edge[1]].push_back(edge[0]);
        }
        function<int(int)> dfs = [&](int v) -> int {
            int cnt = 1;
            marked[v] = true;
            for(int w : graph[v]){
                if(!marked[w]) cnt += dfs(w);
            }
            return cnt;
        };
        return dfs(0) == n;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}