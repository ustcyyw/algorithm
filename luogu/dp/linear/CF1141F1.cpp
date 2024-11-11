/**
 * @Time : 2024/5/7-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1505, T = 1e9 + 1;
int n, nums[N];
unordered_map<int, int> dp[N], info[N], lb[N];

void solve() {
    int val = 0, idx = -1, s = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = i, sum = 0; j >= 1; j--) {
            sum += nums[j];
            for(int k = j - 1; k >= 0; k--) {
                if(1 + dp[k][sum] > dp[i][sum]) {
                    dp[i][sum] = 1 + dp[k][sum];
                    info[i][sum] = k;
                    lb[i][sum] = j;
                }
            }
            if(dp[i][sum] > val)
                val = dp[i][sum], idx = i, s = sum;
        }
    }
    cout << val << "\n";
    while(dp[idx][s] != 0) {
        int t = info[idx][s];
        cout << lb[idx][s] << " " << idx << "\n";
        idx = t;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};