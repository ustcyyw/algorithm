/**
 * @Time : 2024/2/3-9:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5 + 5;
int T, n, nums[N], dp[N];

bool solve() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        int j = nums[i];
        if(i + j <= n && dp[i - 1])
            dp[i + j] = 1;
        if(i - j - 1 >= 0) dp[i] = dp[i] || dp[i - j - 1];
        if(dp[n]) return true;
    }
    return false;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};