/**
 * @Time : 2024/5/20-11:26 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1213D2 枚举-相等的数 贪心-优先队列
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
ll T, n, k, sum[N], ans = LONG_LONG_MAX;
priority_queue<int> pq[N];

void add(priority_queue<int>& cq, int num, int cnt) {
    cq.push(cnt), sum[num] += cnt;
    if(cq.size() > k) {
        sum[num] -= cq.top();
        cq.pop();
    }
    if(cq.size() == k) ans = min(ans, sum[num]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        int cnt = 0;
        while(num > 0) {
            add(pq[num], num, cnt);
            cnt++, num /= 2;
        }
        add(pq[num], 0, cnt);
    }
    cout << ans;
};