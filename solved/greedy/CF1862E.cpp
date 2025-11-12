/**
 * @Time : 2024/3/9-5:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 假设选择了i1,i2,i3...im这几天去看电影 快乐值为
  * a[i1] - (i1 - 0)d + a[i2] - (i2 - i1)d + a[i3] - (i3 - i2)d + ... + a[im] - (im - i[m-1])d
  * = a[i1] + a[i2] + a[i3] + ... + a[im]
  * + 0 - i1d + i1d - i2d + i2d - i3d + ... + i[m-1]d - imd
  * = (a[i1] + a[i2] + a[i3] + a[i[m-1]]) + a[im]  - imd
  * 因此 下标的影响只取决与最后一个元素 那么可以枚举最后一个元素 前面的元素尽可能取大的
  * 注意 是最多看m场电影 可以不足m，另外电影的影响可能是负的 对于负的压根就不去看 直接跳过计算
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
int T, n, m, d;

void solve() {
    priority_queue<int, vector<int>, greater<>> pq;
    ll res = 0, sum = 0;
    // 枚举最后一个元素的下标
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        if(num < 0) continue;
        sum += num;
        res = max(res, sum - (ll)d * i);
        pq.push(num);
        if(pq.size() == m) {
            sum -= pq.top();
            pq.pop();
        }
    }
    cout << res << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> d;
        solve();
    }
};