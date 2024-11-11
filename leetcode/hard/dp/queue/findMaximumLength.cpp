/**
 * @Time : 2023/11/26-10:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛 118 t4
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 借鉴lis二分优化的思路 结尾数字越小越好
     * 定义dp[i]表示截止nums[i]，非递减序列末尾元素的最小值
     * 末尾元素越小 越利于接下来数组变得更长
     *
     * 末尾元素越小，前面的元素也会更小
     * 每一个元素都对应的是原数组nums的一段区间上的和(sum[hi] - sum[lo])
     * 每个元素尽可能小，就意味着加和得到这个元素的区间尽可能短 那么就会使构造出来的非递减序列尽可能长
     * 求出dp，也就唯一地对应了最长非递减序列
     * 因此 也对应地定义f[i]是截止nums[i]，非递减序列的最大长度
     *
     * 要使末尾元素尽可能小，那么就应该找到满足条件 dp[j] <= sum[i] - sum[j] 的最大的j
     * （从j = i - 1开始 还不满足dp[j] <= sum[i] - sum[j]就左移动j，
     * 也就是满足sum[i] - sum[j] < dp[j]就左移j）
     * 因为j越大sum[i] - sum[j](表示[j+1,i]上的元素之和)越小
     *
     * 确定了j之后
     * dp[i] = sum[i] - sum[j]
     * f[i] = f[j] + 1
     *
     * 时间复杂度O(n^2)
     */
    int findMaximumLength(vector<int>& nums) {
        int n = nums.size();
        vector<long long> sum(n + 1, 0ll), dp(n + 1, 0ll);
        vector<int> f(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        for(int i = 1, j; i <= n; i++) {
            j = i - 1;
            while(j >= 0 && sum[i] - sum[j] < dp[j])
                j--;
            dp[i] = sum[i] - sum[j];
            f[i] = f[j] + 1;
        }
        return f[n];
    }

    /*
     * 上述方法答案正确 但是需要优化
     * dp优化的原则就是 先把暴力的思路写出来
     * 然后不改变代码结构 看整个计算过程真正有效的计算是哪些 是否可以快速拿到那个有效的转移项
     * 可能需要整理代码
     * 重点：一个整理的原则是将下标相同的放在同一项里面 这样才利于维护
     *
     * 比如本题 要找使得sum[i] - sum[j] >= dp[j]的最大j
     * 将条件整理为 sum[i] >= sum[j] + dp[j]
     * 令val[j] = sum[j] + dp[j], 条件即 sum[i] >= val[j]
     *
     * 那么如果有 k < j, 并且val[k] >= val[j]
     * 就意味着 但凡 sum[i] >= val[j], 就压根不会去检查k，因为k更靠左
     * 或者 sum[i] < val[j], 那么 sum[i] < val[k], k不可能是要找的答案
     * 两种情况下 k 都是没有用的。这很符合单调数据结构排除无用项的思路
     * 使用单调队列
     * 1.在计算出dp[i]后，将所有队尾 val[t] >= val[i]都排除
     * 2.可以看出 队头到队尾维护着的val[j]和下标j都是 逐渐增大的
     * 3.那么找最大的j满足时，应该从队头开始找 因为队头的元素对应的val[j]小
     *   如果 sum[i] >= val[j] 就不断弹出队头元素
     *   直到已经不满足这个条件，那么上一个弹出的j就是要找的最大j
     *   并且使用完后 还要将这个j放回队头，因为对于后续计算 仍然可能是这个j
     */
    /*
     * 单调队列优化的三个步骤
     * 1.将队首无用的数据剔除
     * 2.拿出队首元素 用它来转移
     * 3.用当前的值 剔除队尾无用数据 然后将当前值入队
     */
    int findMaximumLength2(vector<int>& nums) {
        int n = nums.size();
        vector<long long> sum(n + 1, 0ll), dp(n + 1, 0ll);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        vector<int> f(n + 1, 0);
        deque<int> queue; // 存放下标
        queue.push_back(0);
        for(int i = 1; i <= n; i++) {
            int j = 0;
            while(queue.size() && sum[i] >= sum[queue.front()] + dp[queue.front()]) {
                j = queue.front();
                queue.pop_front();
            }
            queue.push_front(j);
            dp[i] = sum[i] - sum[j];
            f[i] = f[j] + 1;
            while(queue.size() && sum[i] + dp[i] <= sum[queue.back()] + dp[queue.back()])
                queue.pop_back();
            queue.push_back(i);
        }
        return f[n];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}