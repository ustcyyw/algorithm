/**
 * @Time : 2022/11/8-4:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<int> degree(n + 1, 0);
        vector<vector<bool>> con(n + 1, vector(n + 1, false));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            degree[v]++, degree[w]++;
            con[v][w] = con[w][v] = true;
        }
        int res = INT_MAX;
        for(int i = 1; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(!con[i][j]) continue;
                for(int k = j + 1; k < n; k++){
                    if(con[i][k] && con[j][k])
                        res = min(res, degree[i] + degree[j] + degree[k]);
                }
            }
        }
        return res == INT_MAX ? -1 : res - 6;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}