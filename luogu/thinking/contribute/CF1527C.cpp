/**
 * @Time : 2024/3/22-8:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 贡献法 考虑每一对相等对pair能够出现在多少个子数组中
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, V = 1e6 + 5, MOD = 1e9 + 7;
int T, n;
map<int, vector<int>> mp;

void solve() {
    ll ans = 0;
    for(auto& p : mp) {
        vector<int>& arr = p.second;
        ll sum = arr[0], m = arr.size();
        for(int i = 1; i < m; i++) {
            ans += (ll)sum * (n + 1 - arr[i]);
            sum += arr[i];
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        mp = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            mp[num].push_back(i);
        }
        solve();
    }
};