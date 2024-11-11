/**
 * @Time : 2024/3/7-9:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : hashmap计数套路题
 */
 /*
  * 区间[i, j]上的和 sum[j] - sum[i - 1]
  * 区间长度为 j - i + 1
  * sum[j] - sum[i - 1] = j - i + 1
  * sum[j] - j = sum[i - 1] - (i - 1)
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
int T, n;
string s;

void solve() {
    ll cnt = 0;
    unordered_map<int, int> map;
    map[0] = 1;
    for(int i = 1, sum = 0; i <= n; i++) {
        sum += s[i] - '0';
        cnt += map[sum - i];
        map[sum - i]++;
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cin >> s;
        s = '.' + s;
        solve();
    }
};