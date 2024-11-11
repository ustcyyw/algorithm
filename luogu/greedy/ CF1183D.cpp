/**
 * @Time : 2024/5/15-11:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1183D 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n;
map<int, int> cnt;

void solve() {
    vector<int> arr;
    for(auto& p : cnt)
        arr.push_back(p.second);
    sort(arr.begin(), arr.end());
    ll ans = 0;
    set<int> set;
    for(int i = 1; i <= arr.back(); i++)
        set.insert(i);
    for(int num : arr) {
        if(set.empty()) break;
        auto it = set.upper_bound(num);
        if(it == set.begin()) continue;
        int val = *(--it);
        ans += val, set.erase(set.find(val));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cnt.clear();
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            cnt[num]++;
        }
        solve();
    }
};