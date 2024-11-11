/**
 * @Time : 2024/3/19-9:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 拿了k个蘑菇 ，那么就有k-1个蘑菇值为0 还剩下 n - k + 1个蘑菇
  * n - k + 1 >= k, 2k <= n + 1 且k是整数，因此有k = (n + 1) / 2
  *
  * 一开始考虑拿最多的蘑菇 k = (n + 1) / 2
  * 那么从 p[k], p[k + 1], p[k + 2] ... p[n]对应的蘑菇可用，且全选
  * 再考虑拿k-1个蘑菇 那么p[k-1]对应的蘑菇可用了，将其放入可选集合中
  * 为了让答案最大 此时要将集合中最小的一部分剔除，直到集合的大小 = k - 1
  * 依次减小所拿蘑菇的数量 那么会不断有新的蘑菇加入可用集合 持续剔除最小的 让集合大小 = 所拿蘑菇数量
  * 优先队列 贪心
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, m, nums[N], p[N];

void solve() {
    ll k = (n + 1) / 2, sum = 0;
    priority_queue<ll, vector<ll>, greater<>> pq;
    for(int i = k + 1; i <= n; i++)
        sum += nums[p[i]], pq.push(nums[p[i]]);
    ll ans = 0, cnt = -1;
    for(int i = k; i >= 1; i--) { // 枚举拿多少个蘑菇
        pq.push(nums[p[i]]), sum += nums[p[i]];
        while(pq.size() > i) {
            sum -= pq.top();
            pq.pop();
        }
        ll temp = pq.top() * i;
        if(temp >= ans) ans = temp, cnt = i;
    }
    cout << ans << " " << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        for(int i = 1; i <= n; i++)
            cin >> p[i];
        solve();
    }
};