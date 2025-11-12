/**
 * @Time : 2024/9/23-12:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1878E st表 二分
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, q;
vector<int> arr;

class STable {
    int n, m;
    vector<vector<int>> dp;

    int f(int num1, int num2) {
        // 可以替换为其它函数
        return num1 & num2;
    }

public:
    STable(vector<int>& nums) {
        n = nums.size(), m = log2(n);
        dp.assign(n, vector(m + 1, 0));
        for(int i = 0; i < n; i++)
            dp[i][0] = nums[i];
        for(int j = 1; j <= m; j++) {
            int pj = 1 << (j - 1);
            for(int i = 0; i + pj < n; i++) {
                dp[i][j] = f(dp[i][j - 1], dp[i + pj][j - 1]);
            }
        }
    }

    int search(int l, int r) {
        int len = r - l + 1, j = log2(len);
        return f(dp[l][j], dp[r - (1 << j) + 1][j]);
    }
};

int solve(STable& st, int l, int k) {
    if(arr[l] < k) return -1;
    int lo = l, hi = n;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(st.search(l, mid) >= k) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        arr.assign(n + 1, 0);
        for(int i = 1; i <= n; i++)
            cin >> arr[i];
        STable st(arr);
        cin >> q;
        for(int i = 1, l, k; i <= q; i++) {
            cin >> l >> k;
            cout << solve(st, l, k) << " ";
        }
        cout << "\n";
    }
};