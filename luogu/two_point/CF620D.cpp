/**
 * @Time : 2024/3/28-9:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 用sa、sb分别表示数组a和b一开始的和
 * 1.交换一次的情况 直接枚举a和b的每一个数即可
 * 2.交换两次的情况 a[i], a[j], b[k], b[l]进行交换
 * 2.1 存在下标相同，比如 k=l，两次交换b数组的同一个位置 swap(a[i], b[k]), swap(b[k], a[j])
 * 只是相当于a[j]换到b中，b[k]换到了a中 就是只交换一次的情况。
 * 这种特殊情况算出来的答案 是交换一次时候算过的 不会更新最终答案
 * 2.2 i j k l都不相同。交换后 a数组的和为 sa - a[i] - a[j] + b[k] + b[l]
 * b数组的和为 sb - b[k] - b[l] + a[i] + a[j]
 * 因此相减为 sa - sb - 2(ai - aj) + 2(bk + bl)
 * 要使这个式子绝对值最小 就是希望  sa - sb - 2(ai - aj) + 2(bk + bl) = 0
 * 也就是 2(bk + bl) = sb - sa + 2(ai - aj)
 * 枚举ai - aj，随着ai - aj增大bk + bl也会增大 要找等式的临界值 可以使用双指针
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2005, mod = 1e9 + 7;
int n, m, a[N], b[N];

vector<vector<ll>> two_sum(int *arr, int t) {
    vector<vector<ll>> ans;
    for (int i = 1; i <= t; i++) {
        for (int j = i + 1; j <= t; j++)
            ans.push_back({arr[i] + arr[j], i, j});
    }
    sort(ans.begin(), ans.end());
    return ans;
};

void solve() {
    ll sa = accumulate(a + 1, a + n + 1, 0ll), sb = accumulate(b + 1, b + m + 1, 0ll);
    ll ans = abs(sa - sb); // 不做交换的情况
    vector<vector<ll>> ope;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ll d = a[i] - b[j];
            if (ans > abs(sa - sb - 2 * d)) { // 交换一次的情况
                ans = abs(sa - sb - 2 * d), ope = {};
                ope.push_back({i, j});
            }
        }
    }
    function<void(vector<ll> &, vector<ll> &, ll)> comp = [&](vector<ll> &p1, vector<ll> &p2, ll val) -> void {
        if (abs(val - 2 * p2[0]) < ans) {
            ans = abs(val - 2 * p2[0]), ope = {};
            ope.push_back({p1[1], p2[1]});
            ope.push_back({p1[2], p2[2]});
        }
    };
    vector<vector<ll>> at = two_sum(a, n), bt = two_sum(b, m);
    for (int i = 0, j = 0, sz = bt.size(); i < at.size(); i++) {
        vector<ll> &p1 = at[i];
        ll val = sb - sa + p1[0] * 2;
        while (j < sz && 2 * bt[j][0] <= val) j++;
        if(j > 0) comp(p1, bt[j - 1], val);
        if(j < sz) comp(p1, bt[j], val);
    }
    cout << ans << "\n";
    cout << ope.size() << "\n";
    for (auto &p: ope)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    solve();
};