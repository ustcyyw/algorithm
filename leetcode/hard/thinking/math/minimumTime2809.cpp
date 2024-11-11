/**
 * @Time : 2023/8/9-10:20 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 消除操作 主要是为了抹除nums1的影响
     * 假设有两种策略
     * 1.某一秒已经消除了第i列，间隔2秒这两秒内消除了a和b列 再次消除第i列
     * 2.先消除了a和b列，最后消除第i列
     * 上述两种情况 最终i列都是0，但是a和b列多出了nums2[a] + nums2[b] 并且由于1多用了1秒，其它列更多
     * 因此可以说明，某一列最多只能消除一次，消除多次的情况一定更差
     * 那么最多就只能操作n次，最多将每一列都消除一次
     *
     * 可以考虑枚举操作的次数 t
     * 假设时间经过t秒，但是没有进行任何消除操作，那么和为 sum(nums1) + t * sum(nums2)
     * 要尽可能的在这个基础上减少更多的值
     * 如果已经知道最终答案选择了哪些列，比如i,j,k三列
     * 最终nums1[i] + nums1[j] + nums1[k] = 0，只有nums2的附加值会影响答案了
     * 贪心的想，肯定是将nums2大的那一列最后消除，nums2最小的那列优先消除 这样附加的少一些，减少的就多一些
     * （排序不等式可以证明）
     *
     * 因此，如果按nums2进行排序，并且枚举操作的次数 t
     * 那么就是选择t列，然后从前往后分别在第1,2,...,t秒进行消除
     * 如何让消除的值最大
     * 动态规划 dp[i][j] 截止第i列 操作了j次 消除的最大值
     * dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + nums1[i] + j * nums2[i])
     */
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        int n = nums1.size();
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0), sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        if(sum1 <= x) return 0;
        vector<vector<int>> aux;
        for(int i = 0; i < n; i++)
            aux.push_back({nums1[i], nums2[i]});
        sort(aux.begin(), aux.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
        vector<int> dp(n + 1); // dp二维优化为一维
        for(int i = 1; i <= n; i++) {
            for(int j = i; j >= 1; j--) // dp二维优化为一维 这里计算方向要注意
                dp[j] = max(dp[j], dp[j - 1] + aux[i - 1][0] + j * aux[i - 1][1]);
        }
        for(int t = 1; t <= n; t++) {
            int val = sum1 + t * sum2 - dp[t];
            if(val <= x) return t;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}