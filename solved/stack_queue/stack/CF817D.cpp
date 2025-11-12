/**
 * @Time : 2025/4/3-12:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF817D 1900 贡献法 单调栈
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 15, M = 30;
int n, nums[N], pre[N], nxt[N];

void init_pre() {
    stack<int> stack;
    for(int i = 1; i <= n; i++) {
        while(!stack.empty() && nums[stack.top()] < nums[i])
            stack.pop();
        pre[i] = stack.empty() ? 1 : stack.top() + 1;
        stack.push(i);
    }
}

void init_nxt() {
    stack<int> stack;
    for(int i = n; i >= 1; i--) {
        while(!stack.empty() && nums[stack.top()] <= nums[i])
            stack.pop();
        nxt[i] = stack.empty() ? n : stack.top() - 1;
        stack.push(i);
    }
}

ll cal() {
    init_pre(), init_nxt();
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += (ll)nums[i] * (i - pre[i] + 1) * (nxt[i] - i + 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    ll ans = cal();
    for(int i = 1; i <= n; i++)
        nums[i] = -nums[i];
    cout << ans + cal();
}