/**
 * @Time : 2024/12/6-10:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2050F 1713 数学 数论 数据结构 st表
 */
 /*
  * a % m = b % m
  * a % m - b % m = 0
  * (a - b) % m = 0
  * 也就是说m应该取各个元素差值的gcd
  * 又涉及到区间查询 gcd刚好是一个可以用于静态查询的问题 于是确定要使用st表
  *
  * 题目中特别说了 如果m可以无限大 输出0
  * 什么时候m可以无限大 就是所有数都相同的时候 次数相邻两个数的差都是0
  * st表中要求 f(a,a) = a, 不妨定义f(0,a) = a，并且这样定义也使得f具有传递性
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, q, nums[N];
vector<int> diff;

class STable {
    int n, m;
    vector<vector<int>> dp;

    int f(int num1, int num2) {
        // 可以替换为其它函数
        if(num1 == 0) return num2;
        if(num2 == 0) return num1;
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> q;
        diff = {};
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            if(i > 1) diff.push_back(abs(nums[i] - nums[i - 1]));
        }
        if(diff.empty()) diff.push_back(-1);
        STable st(diff);
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            if(n == 1 || l == r) cout << 0 << " ";
            else cout << st.search(l - 1, r - 2) << " ";
        }
        cout << "\n";
    };
};