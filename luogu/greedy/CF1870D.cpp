/**
 * @Time : 2025/1/6-9:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1870D 1800 贪心 单调栈 二分查找 试填法
 */
 /*
  * 如果c[j] <= c[i]且j > i 那么c[i]是一点用都没有的
  * 所以可能选择的c[i] 一定是一个递增的序列 先用单调栈预处理
  *
  * 对于每个c[i]的选择 当然是优先保证前缀的值最大
  * 在前缀最大的情况下 尝试让下一个数也更大 可以用二分的方式来找这个最大值
  * 有点类似于位运算中的题目 从高位开始逐位填写答案 试填法
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, m, c[N], arr[N], cnt[N];

void init() {
    stack<int> stack;
    for(int i = 1; i <= n; i++) {
        while(!stack.empty() && c[stack.top()] >= c[i])
            stack.pop();
        stack.push(i);
    }
    m = stack.size();
    for(int i = m; i > 0; i--) {
        arr[i] = stack.top();
        stack.pop();
    }
}

bool check(int idx, int cc) {
    ll sum = c[arr[idx]] * cc;
    for(int i = idx - 1; i > 0; i--) {
        ll add = (ll)(cnt[i] - cc) * c[arr[i]];
        sum += add, cc = cnt[i];
        if(sum > k) return false;
    }
    return true;
}

int cal(int idx) {
    int lo = 0, hi = min(k / c[arr[idx]], cnt[idx - 1]);
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(idx, mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

void solve() {
    init();
    cnt[0] = INT_MAX;
    for(int i = 1; i <= m; i++)
        cnt[i] = cal(i);
    int i = 1, j = 1;
    while(i <= n) {
        int cc = j <= m ? cnt[j] : 0;
        while(i <= arr[j]) {
            cout << cc << " ";
            i++;
        }
        j++;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> c[i];
        cin >> k;
        solve();
    }
};