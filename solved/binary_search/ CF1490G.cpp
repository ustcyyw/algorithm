/**
 * @Time : 2024/7/8-8:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1490G 二分查找
 */
 /*
  * 通过二分确定要走多少完整的圈
  * 通过二分确定最后一圈（不完整的圈）至少得走到哪个位置
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, m, maxV, sum;
int idx[N];
vector<ll> arr;
vector<vector<ll>> infos;

ll cal(int x) {
    if(sum <= 0 && x > maxV) return -1;
    ll lo = 0, hi = x / sum + 1;
    if(sum > 0) {
        while(lo < hi) {
            ll mid = (lo + hi) >> 1;
            if(mid * sum + maxV >= x) hi = mid;
            else lo = mid + 1;
        }
    }
    ll need = x - sum * lo, ans = lo * n;
    if(need == 0) return ans - 1;
    int i = lower_bound(arr.begin(), arr.end(), need) - arr.begin();
    return ans + idx[i];
}

void solve() {
    sort(infos.begin(), infos.end());
    sort(arr.begin(), arr.end());
    idx[n - 1] = infos[n - 1][1];
    for(int i = n - 2; i >= 0; i--) {
        idx[i] = min((int)infos[i][1], idx[i + 1]);
    }
    for(int i = 1, x; i <= m; i++) {
        cin >> x;
        cout << cal(x) << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        infos = {}, arr = {};
        sum = 0, maxV = LONG_LONG_MIN;
        for(int i = 0, num; i < n; i++) {
            cin >> num;
            sum += num, maxV = max(maxV, sum);
            infos.push_back({sum, i}), arr.push_back(sum);
        }
        solve();
    }
};