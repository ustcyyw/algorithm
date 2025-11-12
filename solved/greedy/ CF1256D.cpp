/**
 * @Time : 2024/5/23-10:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1256D 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000 + 5, mod = 998244353;
ll T, n, k;
string s;

void solve() {
    vector<int> arr;
    for(int i = 0; i < n; i++)
        if(s[i] == '0') arr.push_back(i);
    for(int i = 0, one = 0; i < arr.size() && k; i++) {
        ll diff = arr[i] - one, t = min(diff, k);
        swap(s[arr[i]], s[arr[i] - t]);
        k -= t;
        one++;
    }
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        cin >> s;
        solve();
    }
};