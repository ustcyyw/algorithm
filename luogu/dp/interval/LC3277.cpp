/**
 * @Time : 2025/1/8-9:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3277 动态规划 区间dp
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * val[i][j]：按定义计算出的子数组[i,j]的异或和，这个定义并不是常规意义上的 注意
     * mv[i][j]: 左端点为i，右端点截止j的子数组的最大xor值
     * 也就是 max{val(i,i), val(i,i+1), .. val(i, j)}
     * 那么对于询问l,r 求的就是 max{mv[l][r], mv[l+1][r], mv[l+2][r]...mv[r][r]}
     * 所以还可以预处理 pre[l][r]来表示 max{mv[l][r], mv[l+1][r], mv[l+2][r]...mv[r][r]}
     * 值需要枚举r的时候 不断左移动l进行计算即可
     *
     * 关键是如何求val[i][j]
     * 玩一些例子可以发现 val[i][j] = val[i][j - 1] ^ val[i + 1][j];
     *
     * 另外这题就是CF983B
     * https://codeforces.com/contest/983/problem/B
     */
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> val = init(nums, n);
        vector<vector<int>> mv(n, vector(n, 0)), pre(n, vector(n, 0));
        for(int i = 0; i < n; i++) {
            for(int j = i, v = 0; j < n; j++) {
                mv[i][j] = j == i ? val[i][j] : max(val[i][j], mv[i][j - 1]);
            }
        }
        for(int r = n - 1; r >= 0; r--) {
            for(int l = r, v = 0; l >= 0; l--) {
                v = max(v, mv[l][r]);
                pre[l][r] = v;
            }
        }
        vector<int> ans;
        for(auto& q : queries)
            ans.push_back(pre[q[0]][q[1]]);
        return ans;
    }

    vector<vector<int>> init(vector<int>& nums, int n) {
        vector<vector<int>> val(n, vector(n, 0));
        for(int i = 0; i < n; i++)
            val[i][i] = nums[i];
        for(int len = 2; len <= n; len++) {
            for(int i = 0, j = i + len - 1; j < n; i++, j++) {
                val[i][j] = val[i][j - 1] ^ val[i + 1][j];
            }
        }
        return val;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}