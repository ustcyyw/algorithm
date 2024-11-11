/**
 * @Time : 2023/2/28-10:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 51;
class Solution {
public:
    vector<vector<int>> graph;
    vector<vector<pair<int, int>>> aux; // num -> list of node id and layer in path
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        graph = vector(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        aux.assign(N, {});
        vector<int> ans(n, -1);
        dfs(ans, nums, 0, 0, -1);
        return ans;
    }

    void dfs(vector<int>& ans, vector<int>& nums, int v, int layer, int father){
        int num = nums[v], len = INT_MAX, res = -1;
        for(int i = 1; i < N; i++){
            if(aux[i].empty() || gcd(i, num) > 1) continue;
            int t = layer - aux[i].back().second;
            if(t < len) {
                len = t;
                res = aux[i].back().first;
            }
        }
        ans[v] = res;
        aux[num].push_back(make_pair(v, layer));
        for(int w : graph[v]){
            if(w == father) continue;
            dfs(ans, nums, w, layer + 1, v);
        }
        aux[num].pop_back();
    }
};

int main(){
    Solution s;
    vector<int> arr = {2,3,3,2};
    vector<vector<int>> edge = {{0,1},{1,2},{1,3}};
    s.getCoprimes(arr, edge);
    cout << 0 << endl;
}