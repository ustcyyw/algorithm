#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 5e4 + 5, MIN_VAL = -2e9;

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

int main() {
    vector<vector<int>> arr1 = {{0,1},{0,2},{1,3},{2,3}};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,3},{1,2},{1,4},{2,3},{2,5},{4,5},{4,7},{5,6},{6,7}};
    Solution s;
    s.constructGridLayout(4, arr1);
}
