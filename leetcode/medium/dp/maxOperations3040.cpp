/**
 * @Time : 2024/2/29-9:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums) {
        vector<vector<int>> cache;
        function<int(int, int, int)> dfs = [&](int lo, int hi, int val) -> int {
            if(lo >= hi) return 0;
            if(cache[lo][hi] != -1) return cache[lo][hi];
            int res = 0;
            if(nums[lo] + nums[lo + 1] == val) res = dfs(lo + 2, hi, val) + 1;
            if(nums[hi] + nums[hi - 1] == val) res = max(res, dfs(lo, hi - 2, val) + 1);
            if(nums[lo] + nums[hi] == val) res = max(res, dfs(lo + 1, hi - 1, val) + 1);
            cache[lo][hi] = res;
            return res;
        };
        int n = nums.size(), res = 0;
        cache.assign(n, vector(n, -1));
        res = dfs(2, n - 1, nums[0] + nums[1]);
        cache.assign(n, vector(n, -1));
        res = max(res, dfs(0, n - 3, nums[n - 1] + nums[n - 2]));
        cache.assign(n, vector(n, -1));
        res = max(res, dfs(1, n - 2, nums[0] + nums[n - 1]));
        return res + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}