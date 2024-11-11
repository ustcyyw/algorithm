/**
 * @Time : 2024/7/3-8:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1399D 贪心
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, ans[N], m;
string s;

void add(int i, vector<int>& arr, vector<int>& other) {
    if(other.empty()) {
        ans[i] = ++m;
        arr.push_back(m);
    } else {
        int t = other.back(); other.pop_back();
        ans[i] = t, arr.push_back(t);
    }
}

void solve() {
    vector<int> one, zero;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') add(i, zero, one);
        else add(i, one, zero);
    }
    cout << m << "\n";
    for(int i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        m = 0;
        solve();
    }
};