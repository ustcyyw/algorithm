/**
 * @Time : 2024/4/10-1:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N = 2e5 + 5, T = 2e9 + 1;
int n, nums[N];
map<int, int> dp; // dp[i]: 以i结尾的子序列最大长度

void solve() {
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        dp[num] = max({dp[num], 1, dp[num - 1] + 1});
    }
    int len = -1, num = -1;
    for(auto& [v, l] : dp) {
        if(l > len)
            len = l, num = v;
    }
    cout << len << "\n";
    for(int i = 1; i <= n; i++) {
        if(nums[i] == num - len + 1) {
            cout << i << " ";
            len--;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    solve();
};