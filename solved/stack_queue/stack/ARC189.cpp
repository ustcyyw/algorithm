/**
 * @Time : 2025/1/10-11:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : ARC189 2009 单调栈 动态规划 离线思维
 */
/*
 * 对于a,上一个 >= a的元素在i，下一个 >= a的元素在j
a可以吃掉[i+1,j-1]中的数字，其值会变为sum[i+1,j-1]

最大值v1 只要不是左右两边都是v1 就能把所有人吃掉
次大值v2 只要不是左右两边都 >= V2
那可以吃的范围左右第一个v1 看这个区间和是否能超过v1 是则吃所有，否 答案就是区间和
v3可以吃的范围左右第一个v1、v2。 这个区间和 > left, 那就可以吃到左边边界的结果
                           区间和 > right, 可以吃到右边边界的结果


22 25 61  10 21 37  2 14  5 8   6 24
22 47 235 10 31 235   235 5 235 6 235
v1 = 61, 所有和为 235
v2 = 37, 其第一个区间和 > 61, 所以也可以吃说有
v3 = 25, 第一个区间和47 < 61, 没法继续吃
v4 = 24, sum1 > 37, 吃所有
v5 = 22
v6 = 21
v7 = 14, sum1 = 35 > 24, 吃所有
v8 = 8,  sum1 = 19 > 14, 吃所有
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5, mod = 998244353;
int T, n, nums[N], pre[N], nxt[N];
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
            if(nums[i - 1] >= v && v <= nums[i + 1]) {
                ans[i] = v;
                continue;
            }
            int l = pre[i], r = nxt[i];
            ll st = sum[r - 1] - sum[l];
            ans[i] = st;
            if(st > nums[l]) ans[i] = ans[l];
            if(st > nums[r]) ans[i] = max(ans[i], ans[r]);
        }
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            sum[i] = sum[i - 1] + nums[i];
            mp[nums[i]].push_back(i);
        }
        solve();
    }
};