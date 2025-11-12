/**
 * @Time : 2023/12/30-10:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 用一个最小优先队列 按雪人的当前体积排序
 * 记温度的前缀和为st, 第i天堆起来的雪人到第j天的体积情况如何
 * 1.如果没有融化完 其体积为 a[i] - (sum[j] - sum[i - 1])。这一天其融化的体积为 t[j]
 * 2.如果已经融化完 那么截止到第j-1天的时候 还没融化。因为已经融化的雪人 今天就不必考虑了
 *   截止第j-1天时，其体积还剩 a[i] - (sum[j - 1] - sum[i - 1])。
 *   第j天融化的体积就是a[i] - (sum[j - 1] - sum[i - 1])
 *
 * 表达式 a[i] - (sum[j] - sum[i - 1]) = a[i] + sum[i - 1] - sum[j]
 * 第j天没有融化完的条件等价于 sum[j] <= a[i] + sum[i - 1]
 * 这一天这个雪人的融化体积为t[j]
 * 否则这一天雪人融化的体积为 a[i] + sum[i - 1] - sum[j - 1]
 *
 * 在优先队列中存值 a[i] + sum[i - 1] 并且这个值最小排序
 * 就能快速定位有多少雪人今天融化完，并且将这些融化完的弹出队列 后面不再考虑
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, a[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    priority_queue<long long, vector<long long>, greater<>> pq;
    long long sumP = 0, sum = 0;
    for(int i = 1, t; i <= n; i++) {
        cin >> t;
        sum += t;
        pq.push(a[i] + sumP);
        long long ans = 0;
        while(!pq.empty() && pq.top() < sum) {
            ans += pq.top() - sumP;
            pq.pop();
        }
        ans += (long long)t * pq.size();
        cout << ans << " ";
        sumP = sum;
    }
}