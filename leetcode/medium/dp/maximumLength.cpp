/**
 * @Time : 2024/6/30-3:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛404 t3 动态规划
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // dp[i][j]: 以i结尾的元素 并且mod值是j的最长子序列
    // 因为本题中只有长度为2的序列才能定义取mod的值，因此长度为1的序列可以认为其mod值为任意值均可
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        vector<int> last(k, -1);
        vector<vector<int>> dp(n, vector(k, 1));
        for(int i = 0; i < n; i++) {
            int m = nums[i] % k;
            for(int j = 0; j < k; j++) {
                int pre = j >= m ? j - m : j + k - m;
                if(last[pre] != -1) dp[i][j] = dp[last[pre]][j] + 1;
                ans = max(ans, dp[i][j]);
            }
            last[m] = i;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}