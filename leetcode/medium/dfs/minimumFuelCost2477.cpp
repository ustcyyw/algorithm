/**
 * @Time : 2022/11/23-10:35 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int seat;
    long long res = 0;
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size() + 1;
        this->seat = seats;
        vector<vector<int>> graph(n, vector(0, 0));
        for(auto& road : roads){
            int v = road[0], w = road[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        traversal(graph, 0, -1);
        return res;
    }

    int traversal(vector<vector<int>>& graph, int v, int from){
        int cnt = 1;
        for(int w : graph[v]){
            if(w == from) continue;
            cnt += traversal(graph, w, v);
        }
        if(v != 0) res += cnt % seat == 0 ? cnt / seat : cnt / seat + 1;
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}