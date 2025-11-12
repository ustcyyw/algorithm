/**
 * @Time : 2025/3/11-9:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF212D 2500 贡献法 单调栈 数学 差分算法
 */
/*
  * 题目要求所有长度为k = b[i]的子数组的最小值的均值
  * 子数组长度为k，那么一共有这样的子数组 n - k + 1 个，还需要求得这些子数组的最小值之和
  * 想到贡献法 以nums[i]为最小值的子数组 所以先用单调栈找到以nums[i]为最小值的子数组范围
  * 为了去重，单调栈有一边要选择 >, 另外一边选择 >=
  *
  * 对于nums[i], 其有贡献的范围是，子数组左边界[lo, i], 右边界[i, hi]
  * 对于长度为k的子数组来说，nums[i]能贡献cnt个
  * 通过确定左边界l的范围[j1,j2]，还是右边界r的范围[r1,r2]来计算cnt 结果都一样
  * 为了方便确定范围，总是选择[lo, i]或者[i, hi]中较小的那一边来计算
  * 这样只要满足单边的情况，另一边一定不会超出边界 lo或者hi
  * 因此计两个区间中短的长度为L, 长的长度为R。在短的那一侧考虑 就假设短的一侧在左边
  *
  * 用sum[k]表示长度为k的子区间的最小值之和
  * 当k <= L时, 左端点可以取 i-k+1,...i-1,i
  * nums[i]能给k个长度为k子区间贡献和 sum[k] += k * nums[i]
  * 当k属于[L + 1, R], 左端点可以取 i-L+1,...i-1,i
  * nums[i]能给L个长度为k子区间贡献和 sum[k] += L * nums[i]
  * 当 k > R时, 左端点可以取 i-L+1,...,i+R-k
  * nums[i]能给L+R-k个长度为k子区间贡献和
  * sum[k] += (L+R-k) * nums[i] = (L + R) * nums[i] - k * nums[i]
  * 所以sum[k]的计算有两个部分 一种是定值 L * nums[i]， (L + R) * nums[i]
  * 另外一种是与k相关的 k * nums[i]，- k * nums[i]
  * 定值的部分 对于一系列的k 做一个区间加法即可 将这部分写为s1
  * 与k相关的部分 求和之后相当于是 k * sum{sign * nums[i]}
  * 系数k是确定的 那么只要累加sign * nums[i]，这部分写为s2
  * 可以看出s1和s2都可以用差分预处理 最终 sum[k] = s1[k] + k * s2[k]
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 5, P = 13331;
int n, m, nums[N], pre[N], nxt[N];
ll s1[N], s2[N];

void init_pre() {
    stack<int> stack;
    for(int i = 1; i <= n; i++) {
        while(!stack.empty() && nums[stack.top()] > nums[i])
            stack.pop();
        pre[i] = stack.empty() ? 1 : stack.top() + 1;
        stack.push(i);
    }
}

void init_next() {
    stack<int> stack;
    for(int i = n; i >= 1; i--) {
        while(!stack.empty() && nums[stack.top()] >= nums[i])
            stack.pop();
        nxt[i] = stack.empty() ? n : stack.top() - 1;
        stack.push(i);
    }
}

void init() {
    init_pre(), init_next();
    for(int i = 1; i <= n; i++) {
        int lo = pre[i], hi = nxt[i], len = hi - lo + 1;
        ll L = i - lo + 1, R = hi - i + 1, num = nums[i];
        if(L > R) swap(L, R);
        // 当k <= L时 sum[k] += k * nums[i]，只计算到s2中
        s2[1] += num, s2[L + 1] -= num;
        // 当k属于[L + 1, R] sum[k] += L * nums[i]，只计算到s1中
        s1[L + 1] += L * num, s1[R + 1] -= L * num;
        // 当 k > R时 sum[k] += (L + R) * nums[i] - k * nums[i]
        s1[R + 1] += (L + R) * nums[i], s1[len + 1] -= (L + R) * nums[i];
        s2[R + 1] += -num, s2[len + 1] -= -num;
    }
    for(int i = 1; i <= n; i++) {
        s1[i] += s1[i - 1];
        s2[i] += s2[i - 1];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    init();
    cin >> m;
    for(int i = 1, k; i <= m; i++) {
        cin >> k;
        int cnt = n - k + 1;
        long double ans = (s1[k] + k * s2[k]) * (long double)1.0 / cnt;
        printf("%.10Lf\n", ans);
    }
}