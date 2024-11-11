/**
 * @Time : 2022/8/12-5:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m, dx[5] = {0,0,0,1,-1}, dy[5] = {0,1,-1,0,0};
    unordered_map<int, int> cache;
    unordered_set<int> onStack; // 标识某个状态是否在调用栈中
    int minFlips(vector<vector<int>>& mat) {
        n = mat.size(), m = mat[0].size();
        int state = 0;
        for(int k = 0; k < m * n; k++){
            int i = k / m, j = k % m;
            if(mat[i][j] == 1) state = state | (1 << k);
        }
        return minStep(state);
    }

    int minStep(int state){
        if(state == 0) return 0;
        if(cache.count(state)) return cache[state];
        onStack.insert(state);
        int step = -1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int ns = changeState(state, i, j);
                if(onStack.count(ns)) continue; // 在调用栈中的状态，再改回去，说明走了回头路，一定不是最少步骤
                int temp = minStep(ns);
                if(temp != -1) step = step == -1 ? temp : min(step, temp);
            }
        }
        if(step != -1) step++;
        cache[state] = step;
        onStack.erase(state);
        return step;
    }

    int changeState(int state, int x, int y){
        for(int i = 0; i < 5; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            int k = nx * m + ny;
            state ^= 1 << k;
        }
        return state;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}