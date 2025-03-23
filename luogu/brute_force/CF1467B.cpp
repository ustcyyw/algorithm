/**
 * @Time : 2025/3/21-10:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1467B 1700 暴力枚举 前后缀分解
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 15, mod = 1e9 + 7;
int T, n, nums[N], pre[N], suf[N];

bool check(int i) {
    if(i <= 1 || i >= n) return false;
    return (nums[i - 1] > nums[i] && nums[i + 1] > nums[i]) ||
           (nums[i - 1] < nums[i] && nums[i + 1] < nums[i]);
}

int solve() {
    if(n <= 2) return 0;
    int ans = pre[n - 1];
    if(check(2) || check(n - 1)) ans--; // 修改第一个元素或者最后一个元素破坏最后一个峰或者谷
    for(int i = 2; i < n; i++) {
        int om = nums[i], p = nums[i - 1], nxt = nums[i + 1];
        int m1 = max(p, nxt), m2 = min(p, nxt), base = pre[i - 2] + suf[i + 2];
        for(int num : {m1 + 1, m1 - 1, m2 - 1, nxt, p}) {
            nums[i] = num;
            int temp = check(i) + check(i - 1) + check(i + 1) + base;
            ans = min(ans, temp);
        }
        nums[i] = om;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        suf[n] = suf[n + 1] = 0;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        for(int i = 2; i < n; i++)
            pre[i] = pre[i - 1] + check(i);
        for(int i = n - 1; i > 1; i--)
            suf[i] = suf[i + 1] + check(i);
        cout << solve() << "\n";
    }
}