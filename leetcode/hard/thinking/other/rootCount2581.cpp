/**
 * @Time : 2023/3/4-11:02 PM
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
     *
     */
    vector<vector<int>> graph;
    vector<vector<int>> cache;
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        graph = vector(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cache = vector(n, vector(2, 0));
        vector<unordered_set<int>> map;
        map.assign(n, {});
        for(auto& guess : guesses)
            map[guess[0]].insert(guess[1]);
        int total = dfs(0, map, 0, 0, -1), res = 0;
        for(int i = 0; i < n; i++)
            if(total - cache[i][0] + cache[i][1] >= k) res++;
        return res;
    }

    int dfs(int v, vector<unordered_set<int>>& map, int cnt1, int cnt2, int father){
        cache[v] = {cnt1, cnt2};
        int sum = 0;
        for(int w : graph[v]){
            if(w == father) continue;
            if(!map[v].count(w) && !map[w].count(v))
                sum += dfs(w, map, cnt1, cnt2, v);
            if(map[v].count(w) && map[w].count(v))
                sum += dfs(w, map, cnt1 + 1, cnt2 + 1, v) + 1;
            if(map[v].count(w) && !map[w].count(v))
                sum += dfs(w, map, cnt1 + 1, cnt2, v) + 1;
            if(!map[v].count(w) && map[w].count(v))
                sum += dfs(w, map, cnt1, cnt2 + 1, v);
        }
        return sum;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr1 = {{0,1},{1,2},{1,3},{4,2}};
    vector<vector<int>> arr2 = {{0,1},{1,3},{1,0},{2,4}};
    s.rootCount(arr1, arr2, 3);
    cout << 0 << endl;
}