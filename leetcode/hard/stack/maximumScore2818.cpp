/**
 * @Time : 2023/8/14-11:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 给你一个长度为 n 的正整数数组 nums 和一个整数 k 。

一开始，你的分数为 1 。你可以进行以下操作至多 k 次，目标是使你的分数最大：

选择一个之前没有选过的 非空 子数组 nums[l, ..., r] 。
从 nums[l, ..., r] 里面选择一个 质数分数 最高的元素 x 。如果多个元素质数分数相同且最高，选择下标最小的一个。
将你的分数乘以 x 。
nums[l, ..., r] 表示 nums 中起始下标为 l ，结束下标为 r 的子数组，两个端点都包含。

一个整数的 质数分数 等于 x 不同质因子的数目。比方说， 300 的质数分数为 3 ，因为 300 = 2 * 2 * 3 * 5 * 5 。

请你返回进行至多 k 次操作后，可以得到的 最大分数 。

由于答案可能很大，请你将结果对 109 + 7 取余后返回。



示例 1：

输入：nums = [8,3,9,3,8], k = 2
输出：81
解释：进行以下操作可以得到分数 81 ：
- 选择子数组 nums[2, ..., 2] 。nums[2] 是子数组中唯一的元素。所以我们将分数乘以 nums[2] ，分数变为 1 * 9 = 9 。
- 选择子数组 nums[2, ..., 3] 。nums[2] 和 nums[3] 质数分数都为 1 ，但是 nums[2] 下标更小。所以我们将分数乘以 nums[2] ，分数变为 9 * 9 = 81 。
81 是可以得到的最高得分。
示例 2：

输入：nums = [19,12,14,6,10,18], k = 3
输出：4788
解释：进行以下操作可以得到分数 4788 ：
- 选择子数组 nums[0, ..., 0] 。nums[0] 是子数组中唯一的元素。所以我们将分数乘以 nums[0] ，分数变为 1 * 19 = 19 。
- 选择子数组 nums[5, ..., 5] 。nums[5] 是子数组中唯一的元素。所以我们将分数乘以 nums[5] ，分数变为 19 * 18 = 342 。
- 选择子数组 nums[2, ..., 3] 。nums[2] 和 nums[3] 质数分数都为 2，但是 nums[2] 下标更小。所以我们将分数乘以 nums[2] ，分数变为  342 * 14 = 4788 。
4788 是可以得到的最高的分。


提示：

1 <= nums.length == n <= 105
1 <= nums[i] <= 105
1 <= k <= min(n * (n + 1) / 2, 109)
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1, mod = 1e9 + 7;
int cnt[N + 1] = {0};
int init = []() {
    vector<int> isPrime(N + 1, 1);
    for(int i = 2; i <= N; i++){
        if(isPrime[i] == 0 || (long)i * i >= LONG_LONG_MAX) continue; // 不是素数 跳过
        cnt[i] = 1;
        for(int j = i + i; j <= N; j += i) {
            isPrime[j] = 0;
            cnt[j]++;
        }
    }
    return 0;
}();
class Solution {
public:
    /*
     * 贪心的想 应该尽可能挑选x大的区间
     * 首先去看nums中最大的数能在多少个区间中被pick成x，优先选这些区间，然后看次大的数
     * 根据题目定义 就需要知道某个数
     * 其左边，截止到哪个位置它都是质数分数严格最高的（相等也不行）
     * 其右边，截止到哪个位置它都是质数分数最高的（相等可以）
     */
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> infos;
        vector<int> count(n), left(n), right(n);
        for(int i = 0; i < n; i++) {
            count[i] = cnt[nums[i]];
            infos.push_back({nums[i], i});
        }
        init_left(count, left, n), init_right(count, right, n);
        sort(infos.begin(), infos.end());
        long long res = 1;
        for(int i = n - 1; i >= 0 && k > 0; i--) {
            int x = infos[i][0], j = infos[i][1];
            long t = min((long)k, (long)(j - left[j]) * (right[j] - j));
            res = res * quickPower(x, t) % mod;
            k -= t;
        }
        return res;
    }

    void init_left(vector<int>& count, vector<int>& arr, int n) {
        stack<int> stack;
        for(int i = 0; i < n; i++) {
            while (!stack.empty() && count[stack.top()] < count[i])
                stack.pop();
            arr[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
    }

    void init_right(vector<int>& count, vector<int>& arr, int n) {
        stack<int> stack;
        for(int i = n - 1; i >= 0; i--) {
            while (!stack.empty() && count[stack.top()] <= count[i])
                stack.pop();
            arr[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
    }

    int quickPower(int a, int b){
        long res = 1, temp = a;
        while (b != 0){
            if((b & 1) == 1) res = res * temp % mod;
            temp = temp * temp % mod;
            b >>= 1;
        }
        return (int)res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}