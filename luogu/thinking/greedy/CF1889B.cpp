/**
 * @Time : 2024/6/1-5:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1889B 思维 贪心
 */
/*
 * si + sj >= i * j * c
 *
 * 要达成这个不等式 考虑右边怎么样比较小 取i=1
 * 假设有
 * s1 + sj < j * c
 * s1 + sk < k * c
 * 也就是i和j、k都没法直接连通
 * 那么j和k是否可以连通呢? 把上面两个不等式相加
 * sj + sk + 2s1 < (j + k) * c <= j * k * c
 * j * k * c 和(j + k) * c的大小： j * k >= (j + k)， 在j, k > 1的情况下
 *
 * 因此以无法和s1链接的两个点 也没法链接 应该先考虑和s1的链接
 * s1 >= j * c - sj 保存 j * c - sj的值 优先从小的开始
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, c, nums[N];

struct cmp{
    bool operator()(pair<ll, ll>& a, pair<ll, ll>& b){
        return a.first > b.first;
    }
};
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, cmp> pq;

void solve() {
    for(ll i = 2; i <= n; i++)
        pq.push({i * c - nums[i], nums[i]});
    ll sum = nums[1];
    while(!pq.empty() && sum >= pq.top().first) {
        sum += pq.top().second;
        pq.pop();
    }
    cout << (pq.empty() ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> c;
        pq = {};
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};