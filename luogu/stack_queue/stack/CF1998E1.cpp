/**
 * @Time : 2025/1/13-9:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1998E1 2200 单调栈 动态规划 离线思维 和ARC189可以算原题
 */
 /*
  * 与ARC189的对比
  * 虽然本题中的操作是选定l，然后确定r 看似不像ARC189中那样是左右吃邻居
  * 但实际上如果是考虑从i位置开始吃邻居
  * 那么对于其右边比nums[i]小的nums[j]，就选l = i，r = j 就是i吃了右边邻居
  * 对于其左边比nums[i]小的nums[j]，就选l = j, r = i, 还是相当于i吃了左边邻居
  * 因此本题也是不断吃邻居 增加自己的过程
  * 并且本题允许吃和自己相同值的邻居
  * 经过n-1次操作 最后剩下一个下标 问这样的下标共有多少个 就是问有多少个i能够吃完所有邻居
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 998244353;
int T, n, x, nums[N], pre[N], nxt[N];
ll sum[N], ans[N];
map<int, vector<int>> mp;

void init(int* arr, int sign) {
    stack<int> stack;
    int lo, b;
    if(sign == 1) b = 0, lo = 1;
    else b =  n + 1, lo = n;
    for(int i = lo; i <= n && i >= 1; i += sign) {
        while(!stack.empty() && nums[stack.top()] <= nums[i])
            stack.pop();
        arr[i] = stack.empty() ? b : stack.top();
        stack.push(i);
    }
}

void solve() {
    init(pre, 1), init(nxt, -1);
    nums[0] = nums[n + 1] = INT_MAX;
    ans[0] = ans[n + 1] = sum[n]; // 边界设置
    for(auto it = mp.rbegin(); it != mp.rend(); it++) {
        int v = it->first;
        for(int i : mp[v]) {
            if(nums[i - 1] > v && v < nums[i + 1]) {
                ans[i] = v;
                continue;
            }
            int l = pre[i], r = nxt[i];
            ll st = sum[r - 1] - sum[l];
            ans[i] = st;
            if(st >= nums[l]) ans[i] = ans[l];
            if(st >= nums[r]) ans[i] = max(ans[i], ans[r]);
        }
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++)
        if(ans[i] == sum[n]) cnt++;
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> x;
        mp = {};
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            sum[i] = sum[i - 1] + nums[i];
            mp[nums[i]].push_back(i);
        }
        solve();
    }
};