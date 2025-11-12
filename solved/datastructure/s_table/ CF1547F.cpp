/**
 * @Time : 2024/7/11-9:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1547F st表 二分答案
 */
 /*
  * a1           a2            a3            a4
  * 1轮 gcd(a1, a2)  gcd(a2, a3)   gcd(a3, a4)   gcd(a4, a1)
  * 2轮 gcd(a1,a2,a3)  gcd(a2,a3,a4)  gcd(a3,a4,a1),  gcd(a4,a1,a2)
  * 3轮 gcd(a[1,4])  gcd(a[1,4])  gcd(a[1,4]),  gcd(a[1,4])
  *
  * 可以发现每一轮只是扩展了子数组中的元素 都是求子数组的gcd
  * 因此gcd会单调递减 所以 可以二分答案
  * 静态求区间的gcd使用st表
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 4e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n;
vector<int> nums;

class STable {
    int n, m;
    vector<vector<int>> dp;

    int f(int num1, int num2) {
        // 可以替换为其它函数
        return gcd(num1, num2);
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

bool check(int len, STable& st) {
    for(int i = 1, val = st.search(0, 0 + len - 1); i < n; i++) {
        if(st.search(i, i + len - 1) != val)
            return false;
    }
    return true;
}

void solve() {
    STable st(nums);
    int lo = 0, hi = n - 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid + 1, st)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        nums = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            nums.push_back(num);
        }
        for(int i = 0; i < n; i++)
            nums.push_back(nums[i]);
        solve();
    }
};