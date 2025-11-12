/**
 * @Time : 2024/12/10-9:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3376 记忆化搜索
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMinimumTime(vector<int>& strength, int k) {
        int n = strength.size(), full = (1 << n) - 1;
        vector<int> cache(full + 1, -1);
        function<int(int)> dfs = [&](int s) -> int {
            if(s == 0) return 0;
            if(cache[s] != -1) return cache[s];
            int m = n - __builtin_popcount(s), x = 1 + k * m;
            int ans = INT_MAX;
            for(int i = 0; i < n; i++) {
                if((1 << i) & s) {
                    int num = strength[i], t = num / x;
                    int dt = num % x == 0 ? t : t + 1;
                    ans = min(ans, dfs(s ^ (1 << i)) + dt);
                }
            }
            return cache[s] = ans;
        };
        return dfs(full);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}