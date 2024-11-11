/**
 * @Time : 2023/2/11-8:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<vector<int>> edges;
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        this->n = n, this->edges = edges;
        vector<int> res(n - 1, 0);
        int u = (1 << n) - 1;
        for(int s = u; s; s = (s - 1) & u){
            int len = treeLens(s);
            if(len > 0) res[len - 1]++;
        }
        return res;
    }
    // 找到状态s对应的树的直径, 如果给定的s无法构成一棵树，直接返回0
    int treeLens(int s){
        vector<bool> set(n + 1, false);
        int root = -1, len = 0, cnt = 0;
        for(int i = 0; i < n; i++){
            if((1 << i) & s){
                set[i + 1] = true;
                root = i + 1;
                cnt++;
            }
        }
        vector<vector<int>> graph = build(set);
        if(cnt != countTree(graph, root, -1)) return 0;
        dfs(graph, root, -1, len);
        return len;
    }
    // 单一路径上的结点个数
    int dfs(vector<vector<int>>& graph, int v, int father, int& len){
        int l1 = 0, l2 = 0;
        for(int w : graph[v]){
            if(w == father) continue;
            int t = dfs(graph, w, v, len);
            if(t >= l1){
                l2 = l1;
                l1 = t;
            } else if(t > l2)
                l2 = t;
        }
        len = max(len, l1 + l2); // 直径上共有 l1 + l2 + 1个结点，这个路径长为l1 + l2
        return l1 + 1;
    }

    int countTree(vector<vector<int>>& graph, int v, int father){
        int cnt = 1;
        for(int w : graph[v]){
            if(w == father) continue;
            cnt += countTree(graph, w, v);
        }
        return cnt;
    }

    vector<vector<int>> build(vector<bool>& set){
        vector<vector<int>> graph(n + 1, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            if(set[v] && set[w])
                graph[v].push_back(w), graph[w].push_back(v);
        }
        return graph;
    }
};

int main(){
    Solution s;
    vector<vector<int>> edge = {{1,2},{1,5},{2,4},{3,5}};
    s.countSubgraphsForEachDiameter(5, edge);
    cout << 0 << endl;
}