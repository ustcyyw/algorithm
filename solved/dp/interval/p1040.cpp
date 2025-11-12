/**
 * @Time : 2023/10/14-12:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int n, nodes[N];

// 前序遍历
void dfs(vector<vector<int>>& mid, int lo, int hi) {
    if(hi < lo) return;
    if(hi == lo) {
        cout << hi << " ";
        return;
    }
    int k = mid[lo][hi];
    cout << k << " ";
    dfs(mid, lo, k - 1);
    dfs(mid, k + 1, hi);
}

void solve() {
    vector<vector<int>> mid(n + 1, vector(n + 1, -1));
    vector<vector<long>> dp(n + 1, vector(n + 1, 0l));
    for(int i = 1; i <= n; i++)
        dp[i][i] = nodes[i];
    for(int l = 2; l <= n; l++) {
        for(int lo = 1; lo + l - 1 <= n; lo++) {
            int hi = lo + l - 1;
            for(int k = lo; k <= hi; k++) { // 枚举k是根结点 左子树[lo,k-1]，右子树[k+1,hi]
                long left = k - 1 >= lo ? dp[lo][k - 1] : 1;
                long right = k + 1 <= hi ? dp[k + 1][hi] : 1;
                long t = nodes[k] + left * right;
                if(t > dp[lo][hi])
                    dp[lo][hi] = t, mid[lo][hi] = k;
            }
        }
    }
    cout << dp[1][n] << endl;
    dfs(mid, 1, n);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> nodes[i];
    }
    solve();
}