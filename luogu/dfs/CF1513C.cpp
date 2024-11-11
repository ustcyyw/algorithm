/**
 * @Time : 2024/3/14-9:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
ll T, n, m, cache[10][N] = {0};

ll dfs(int num, int k) {
    if(num < 10 && k < 10) return num + k >= 10 ? 2 : 1;
    if(num < 10 && cache[num][k] != 0) return cache[num][k];
    ll ans = 0, temp = num;
    if(num < 10) ans = (dfs(1, k - (10 - num)) + dfs(0, k - (10 - num))) % MOD;
    else {
        while(temp) {
            int digit = temp % 10;
            ans = (ans + dfs(digit, k)) % MOD, temp /= 10;
        }
    }
    if(num < 10) cache[num][k] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        cout << dfs(n, m) << "\n";
    }
};