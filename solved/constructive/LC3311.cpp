/**
 * @Time : 2025/1/15-9:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3311 构造 思维 模拟
 */
 /*
  * 拼图游戏 先找角上的元素 然后找第一列第一行
  * 填充完这些边界后发现 已经填了的最靠右的一列 每个元素只剩下一个相临元素了
  * 然后又可以唯一地填出新的一列
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int total, s;
    vector<unordered_set<int>> graph;
    vector<vector<int>> constructGridLayout(int total, vector<vector<int>>& edges) {
        this->total = total;
        graph.assign(total, {});
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].insert(w), graph[w].insert(v);
        }
        int n = init(), m = total / n;
        vector<vector<int>> ans(n, vector(m, 0));
        vector<int> col, row;
        if(n == 1) bfs(row, col, n, m, 1);
        else bfs(row, col, n, m, 2);
        for(int i = 0; i < m; i++) {
            ans[0][i] = row[i];
            if(i > 0) erase(ans[0][i - 1], ans[0][i]);
        }
        for(int i = 1; i < n; i++) {
            ans[i][0] = col[i];
            erase(ans[i - 1][0], ans[i][0]);
        }
        for(int j = 1; j < m; j++) {
            for(int i = 1; i < n; i++) {
                // 用左边的元素确定当前格子填什么
                int c = *graph[ans[i][j - 1]].begin();
                ans[i][j] = c;
                erase(c, ans[i][j - 1]), erase(c, ans[i - 1][j]);
            }
        }
        return ans;
    }

    void erase(int v, int w) {
        graph[v].erase(w);
        graph[w].erase(v);
    }

    void bfs(vector<int>& row, vector<int>& col, int n, int m, int td) {
        queue<int> queue;
        vector<int> marked(total, 0), f(total, -1);
        queue.push(s), marked[s] = 1;
        int step = 0;
        while(step <= m - 1) {
            int sz = queue.size();
            while(sz-- > 0) {
                int v = queue.front(); queue.pop();
                // 行数 <= 列数 按bfs走 一定是先找到第一列
                if((step == n - 1 || step == m - 1) && graph[v].size() == td) {
                    if(col.empty()) get_path(col, f, v);
                    else get_path(row, f, v);
                }
                for(int w : graph[v]) {
                    if(marked[w] || graph[w].size() > td + 1) continue;
                    f[w] = v, marked[w] = 1, queue.push(w);
                }
            }
            step++;
        }
    }

    void get_path(vector<int>& arr, vector<int>& f, int v) {
        while(v != -1) {
            arr.push_back(v);
            v = f[v];
        }
        reverse(arr.begin(), arr.end());
    }
    // 题目说明了一定有解 因此可以根据结点的度数判断矩阵有几行几列
    int init() {
        vector<int> degree(5, 0);
        for(int i = 0; i < total; i++) {
            int c = graph[i].size();
            if(c == 1) {
                s = i;
                return 1;
            }
            degree[c]++;
            if(c == 2) s = i;
        }
        for(int n = 2; n < total; n++) {
            if(total % n != 0) continue;
            int m = total / n;
            if(2 * m + 2 * n - 8 == degree[3] && total - degree[3] - 4 == degree[4])
                return n;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}