/**
 * @Time : 2024/6/18-3:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1283C 构造 模拟
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, m, f[N], ans[N], in[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<int> zero, need;
    for(int i = 1; i <= n; i++) {
        cin >> f[i];
        if(f[i] > 0) ans[i] = f[i], in[f[i]] = 1;
        else zero.push_back(i);
    }
    for(int i = 1; i <= n; i++)
        if(in[i] == 0) need.push_back(i);
    for(int i = 0; i < zero.size(); i++) {
        if(zero[i] == need[i]) {
            if(i == 0) swap(need[i], need[i + 1]);
            else {
                swap(need[i], need[i - 1]);
                ans[zero[i - 1]] = need[i - 1];
            }
        }
        ans[zero[i]] = need[i];
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
};