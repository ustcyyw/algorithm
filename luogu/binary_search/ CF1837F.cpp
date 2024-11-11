/**
 * @Time : 2024/3/15-11:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 标准的二分答案的提问方式
 *
 * 假设要让前缀或者后缀的和都不超过val
 * 优先保证前缀不超过val，尽量多拿一些数，这样后缀就可以拿较少的数，更利于让后缀也不超过val
 * 假设枚举到nums[i], 前缀中已经有m个数字了
 * 如果这个时候从nums[i+1, n]上有一个序列其和 <= val，并且至少有k-m个数字
 * 将这两个序列拼接起来 就找到了一个满足题目要求 且所求值 <= val的序列了
 *
 * 于是发现 前缀和后缀找的东西都一样 都可以用优先队列来维护
 * 在队列元素和不超过val的情况下 将元素放进去 如果超了 贪心地弹出最大的一个元素
 * 第一遍正着处理 是前缀
 * 用cnt[i]记录nums[1,i]上和不超过val的序列中最多有多少个元素
 * 第二遍倒着处理 是后缀 查看两个序列元素之后是否 >= k
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 3e5 + 5;
int T, n, k, nums[N], cnt[N] = {0};

bool check(ll val) {
    priority_queue<int> pq;
    for(ll i = 1, sum = 0ll; i <= n; i++) {
        sum += nums[i], pq.push(nums[i]);
        if (sum > val) sum -= pq.top(), pq.pop();
        cnt[i] = (int)pq.size();
        if(cnt[i] >= k) return true;
    }
    pq = {};
    for(ll i = n, sum = 0ll; i >= 1; i--) {
        sum += nums[i], pq.push(nums[i]);
        if (sum > val) sum -= pq.top(), pq.pop();
        if(pq.size() + cnt[i - 1] >= k) return true;
    }
    return false;
}

void solve() {
    ll lo = 1, hi = 3e14;
    while(lo < hi) {
        ll mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};