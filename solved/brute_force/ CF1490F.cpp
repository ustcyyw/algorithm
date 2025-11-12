/**
 * @Time : 2024/7/9-10:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1490F 枚举
 */
 /*
  * 枚举相同的次数
  * 高于这个次数的数 削减
  * 低于这个次数的数 全部删除
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n;
map<int, int> mp;

void solve() {
    vector<int> arr;
    for(auto& p : mp)
        arr.push_back(p.second);
    sort(arr.begin(), arr.end());
    int ans = INT_MAX;
    for(int i = arr.size() - 1, cnt = 0, sum = 0; i >= 0; i--) {
        sum += arr[i], cnt++;
        int temp = sum - cnt * arr[i] + (n - sum);
        ans = min(ans, temp);
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
            mp[num]++;
        }
        solve();
    }
};