/**
 * @Time : 2024/12/18-5:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1691D 1800 贡献法 st表 单调栈
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, nums[N], pre[N], suf[N];
vector<ll> sum1, sum2;


class STable {
    int n, m;
    vector<vector<ll>> dp;

    ll f(ll num1, ll num2) {
        // 可以替换为其它函数
        return max(num1, num2);
    }

public:
    STable(vector<ll>& nums) {
        n = nums.size(), m = log2(n);
        dp.assign(n, vector(m + 1, 0ll));
        for(int i = 0; i < n; i++)
            dp[i][0] = nums[i];
        for(int j = 1; j <= m; j++) {
            int pj = 1 << (j - 1);
            for(int i = 0; i + pj < n; i++) {
                dp[i][j] = f(dp[i][j - 1], dp[i + pj][j - 1]);
            }
        }
    }

    ll search(int l, int r) {
        int len = r - l + 1, j = log2(len);
        return f(dp[l][j], dp[r - (1 << j) + 1][j]);
    }
};

void init(int* arr, int flag) {
    stack<int> stack;
    int b = flag == 1 ? 1 : n;
    for(int i = b; i >= 1 && i <= n; i += flag) {
        while(!stack.empty() && nums[stack.top()] <= nums[i])
            stack.pop();
        arr[i] = stack.empty() ? b : stack.top() + flag;
        stack.push(i);
    }
}

bool solve() {
    init(pre, 1), init(suf, -1);
    for(int i = 1; i <= n; i++) {
        sum1[i] = sum1[i - 1] + nums[i];
        sum2[i] = -sum1[i];
    }
    STable st1(sum1), st2(sum2);
    for(int i = 1; i <= n; i++) {
        int l = pre[i], r = suf[i];
        ll v1 = st1.search(i, r), v2 = st2.search(l - 1, i - 1);
        if(v1 + v2 > nums[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        sum1.assign(n + 1, 0), sum2.assign(n + 1, 0);
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};