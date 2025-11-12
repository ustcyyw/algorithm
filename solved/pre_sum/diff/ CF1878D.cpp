/**
 * @Time : 2024/9/22-11:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1878D 差分 观察性质
 */
 /*
  * 随便举几个具体的例子发现 要翻转的区间都是在x对应的子区间上关于中点对称的
  * 于是只需要关注某一对点一共被翻转了多少次 可以使用差分
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, l[N], r[N], q, diff[N];
vector<int> arr;
string s;

void solve() {
    for(int i = 1, x; i <= q; i++) {
        cin >> x;
        int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int a = min(x, l[idx] + r[idx] - x);
        diff[a]++;
    }
    for(int i = 1; i <= k; i++) {
        int lo = l[i], hi = r[i], mid = (lo + hi) >> 1;
        for(int j1 = lo, j2 = hi, sum = 0; j1 <= mid; j1++, j2--) {
            sum += diff[j1];
            if(sum % 2 == 1) swap(s[j1], s[j2]);
        }
    }
    cout << s.substr(1) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k >> s;
        fill(diff, diff + n + 1, 0);
        arr = {0}, s = '.' + s;
        for(int i = 1; i <= k; i++)
            cin >> l[i];
        for(int i = 1; i <= k; i++) {
            cin >> r[i];
            arr.push_back(r[i]);
        }
        cin >> q;
        solve();
    };
};