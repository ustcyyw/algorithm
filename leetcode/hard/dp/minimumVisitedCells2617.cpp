/**
 * @Time : 2023/4/11-2:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

struct cmp{
    bool operator()(pair<int, int>& a, pair<int, int>& b){
        return a.second > b.second;
    }
};
class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        if(n == 1 && m == 1) return 1;
        vector<priority_queue<pair<int, int>, vector<pair<int, int>>, cmp>> rows(n), cols(m);
        rows[0].push(make_pair(grid[0][0], 1));
        cols[0].push(make_pair(grid[0][0], 1));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(i == 0 && j == 0) continue;
                clean(cols[j], i);
                clean(rows[i], j);
                int t1 = rows[i].empty() ? INT_MAX : rows[i].top().second;
                int t2 = cols[j].empty() ? INT_MAX : cols[j].top().second;
                int t = min(t1, t2);
                if(t != INT_MAX) {
                    t++;
                    rows[i].push(make_pair(grid[i][j] + j, t));
                    cols[j].push(make_pair(grid[i][j] + i, t));
                }
                if(i == n - 1 && j == m - 1) return t == INT_MAX ? -1 : t;
            }
        }
        return -1;
    }

    void clean(priority_queue<pair<int, int>, vector<pair<int, int>>, cmp>& pq, int t){
        while (!pq.empty() && pq.top().first < t)
            pq.pop();
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}