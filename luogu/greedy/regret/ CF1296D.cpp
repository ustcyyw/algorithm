/**
 * @Time : 2024/6/20-4:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1296D 反悔贪心
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, T = 1e4;
typedef long long ll;
ll n, a, b, k;

int cal(ll num) {
    int mod = num % (a + b);
    if(mod == 0) mod = a + b;
    return mod % a == 0 ? mod / a - 1 : mod / a;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> a >> b >> k;
    priority_queue<int> pq;
    int sum = 0, ans = 0;
    for(ll i = 1, num; i <= n; i++) {
        cin >> num;
        int t = cal(num);
        pq.push(t), sum += t;
        while(sum > k) {
            sum -= pq.top();
            pq.pop();
        }
        ans = max(ans, (int)pq.size());
    }
    cout << ans;
};