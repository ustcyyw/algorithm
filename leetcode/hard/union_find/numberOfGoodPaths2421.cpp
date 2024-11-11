/**
 * @Time : 2022/11/23-3:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> ids;
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size(), ans = n;
        for(int i = 0; i < n; i++)
            ids.push_back(i);
        vector<vector<int>> graph(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        vector<vector<int>> nodes(1e5 + 1, vector(0, 0)); // val -> id
        for(int i = 0; i < n; i++)
            nodes[vals[i]].push_back(i);
        for(int val = 0; val < nodes.size(); val++){
            for(int v : nodes[val]){ // 值为val的所有结点编号，将其与临接的且值小于等于val的结点union
                for(int w : graph[v])
                    if(vals[w] <= val) connect(v, w);
            }
            // 计算当前值为端点的好路径数目
            ans += count_path(nodes[val], val);
        }
        return ans;
    }

    int count_path(vector<int>& nodes, int val){
        unordered_map<int, int> map; // id -> num of nodes
        int ans = 0;
        for(int node : nodes){
            int id = find(node);
            if(map.count(id)){
                ans += map[id];
                map[id]++;
            } else map[id] = 1;
        }
        return ans;
    }

    int find(int p){
        if(ids[p] == p) return p;
        ids[p] = find(ids[p]);
        return ids[p];
    }

    void connect(int p, int q){
        p = find(p), q = find(q);
        ids[p] = q;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}