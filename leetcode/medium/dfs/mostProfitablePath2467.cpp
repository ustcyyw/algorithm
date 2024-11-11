/**
 * @Time : 2022/11/21-12:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> time;
    vector<vector<int>> graph;
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = edges.size() + 1;
        graph = vector(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        time = vector(n, INT_MAX);
        time[bob] = 0;
        bobPath(0, bob, -1);
        return alicePoint(amount, 0, 0, -1);
    }

    int bobPath(int v, int bob, int from){
        if(v == bob) return 0;
        for(int w : graph[v]){
            if(w == from) continue;
            int t = bobPath(w, bob, v);
            if(t != INT_MAX) time[v] = t + 1;
        }
        return time[v];
    }

    int alicePoint(vector<int>& amount, int v, int curTime, int from){
        int base = curTime > time[v] ? 0 : (curTime == time[v] ? amount[v] / 2 : amount[v]);
        int point = INT_MIN;
        if(v != 0 && graph[v].size() == 1) return base;
        for(int w : graph[v]){
            if(w == from) continue;
            point = max(point, alicePoint(amount, w, curTime + 1, v));
        }
        return point + base;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}