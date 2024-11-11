/**
 * @Time : 2024/3/17-2:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛389 t4
 */

/*
 * 假设选定了index
 * 组合操作：在index左边或者右边的0使用一次操作1，再使用一次操作2 一共两个次操作可以获得1个1
 * 只有index的左边或者右边就有1时 直接使用操作2一次能更优
 * 如果选好的index的左边或者右边没有1了，就应该使用组合操作 但是有限制次数
 *
 * 在index-1，index，index+1三个位置的1已经拿走后，一直使用组合操作 直到操作1达到限制次数m
 * 剩下还需要的1为cnt个，那么就应该找离index最近的cnt个1来计算
 * 先考虑index-1，index，index+1三个特殊位置，有可能为000，010，110（011），111
 *
 * 1.如果存在111，即3个连续的1，将index选在中间 用2次操作2拿到3个1后
 * 还剩k - 3个1，如果m >= k - 3，那就不用找额外的1，再使用k-3次组合操作就是最优的
 * 总操作次数为 2 + 2 * (k - 3) = 2k - 4
 * 否则 还需要再找 k - 3 - m个1，使用操作2来获取，连带着先拿走的3个1
 * 实际上还是找来k-m个1，通过操作2来拿；然后使用来m次组合操作
 * 2.如果存在011，即2个连续的1，将index选在中间 用1次操作2拿到2个1后
 * 还剩k - 2个1，如果m >= k - 2，那就不用找额外的1，再使用k-2次组合操作就是最优的
 * 总操作次数为 1 + 2 * (k - 2) = 2k - 3 小于上一种情况，也就是说上一种情况成立 不必考虑此情况
 * 否则 还需要再找 k - 2 - m个1，使用操作2来获取，连带着先拿走的2个1
 * 实际上还是找来k-m个1，通过操作2来拿；然后使用来m次组合操作
 * 3.如果存在010类似上述分析
 * 4.以上都不存在 说明整个数组都是0 那么就只能使用m次组合操作了 答案就是 k * 2
 * 另外，注意到上述分析中 涉及到111和011 如果k=2，压根就用不到111，如果k=1则111和011都用不到
 * 所以先特殊判断 如果k=1和k=2 具体看注释
 *
 * 在特判没有找到答案的情况下，问题变成了枚举index找最接近index的k-m个1，计算他们到index的最小距离
 * 随着index的变化，最接近它的k-m个1，左、右边界都在右移动
 * 这个过程实际上也是枚举了最接近的k-m个1这样的序列，要让他们都某个点的距离最短 中位数贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    ll special(vector<int>& nums, int k, int m) {
        int n = nums.size(), one = 0, two = 0, three = 0;
        for(int i = 0; i < n; i++) {
            if(nums[i]) one = 1;
            if(i < n - 1 && nums[i] && nums[i + 1]) two = 1;
            if(i < n - 2 && nums[i] && nums[i + 1] && nums[i + 2]) three = 1;
        }
        if(k == 1) return one ? 0 : 2; // k = 1，但凡数组中存在1直接index放在那，否则就只能通过1次组合操作
        if(k == 2) {
            if(two) return 1; // 存在011，将index放在该处 1次操作2即可
            if(!one) return 4; // 不存在任何1，只能通过2次组合操作
        }
        // k >= 3的情况
        if(three && m >= k - 3) return 2 + (k - 3) * 2;
        if(two && m >= k - 2) return 1 + (k - 2) * 2;
        if(one && m >= k - 1) return (k - 1) * 2;
        if(m >= k) return k * 2;
        return -1;
    }

    long long minimumMoves(vector<int>& nums, int k, int m) {
        ll t = special(nums, k, m);
        if(t != -1) return t;
        vector<ll> aux;
        for(int i = 0; i < nums.size(); i++)
            if(nums[i]) aux.push_back(i);
        int n = aux.size();
        vector<ll> sum(n + 1, 0ll);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + aux[i - 1];
        ll ans = LONG_LONG_MAX;
        // 中位数贪心求最短距离 也就是最少操作2的使用次数
        int lo = 0, hi = k - m - 1, mid = (lo + hi) / 2, lc = mid - lo + 1, rc = hi - mid;
        while(hi < n) {
            ll ld = sum[mid + 1] - sum[lo], rd = sum[hi + 1] - sum[mid + 1];
            ll temp = m * 2 + aux[mid] * lc - ld + rd - aux[mid] * rc; // 别忘了m次组合操作
            ans = min(temp, ans);
            lo++, hi++, mid++;
        }
        return ans;
    }
};
