/**
 * @Time : 2023/12/1-5:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * dp[i][k]: nums[1, i]上分k个子数组的最大值
 * dp[i][k] = max{dp[j][k-1] + cnt[j + 1][i], for j in [k-1, i-1]}
 * 其中 cnt[j + 1][i]: 是子数组nums[j+1,i]上不同元素的个数
 * 1.计算分组k的时候，k-1分组的所有状态已经算出来了 dp[j][k-1] 这一项在区间上的值容易处理
 * 2.子数组不同元素个数，涉及到dp递推（i维度的计算），想到使用last[i]记录当前元素上次出现的索引
 * 根据这个边界为分界，[1,last[i]]上cnt不会因为nums[i]而改变，但是[last[i] + 1, i]上的cnt都要+1
 * 因此cnt[j+1][i]这一项也可以通过区间+1的操作进行维护
 * 3.区间找最大值是对j的区间查找， dp[j][k-1] + cnt[j + 1][i]下标不统一，可以令a[j][i] = cnt[j + 1][i]
 * 那么 dp[i][k] = max{dp[j][k-1] + a[j][i], for j in [k-1, i-1]} 转移方程就是找区间上的最大值
 * 4.因此使用线段树进行优化：
 * 先用dp[j][k-1]建树 进行单点修改操作；
 * 计算i的时候使用区间加操作更新a[j][i] = cnt[j + 1][i]
 * 对于cnt而言，是区间[last[i] + 1, i] 加1，那么对于a而言是在区间[last[i], i - 1]上加1
 */

#include<bits/stdc++.h>
# define ls x << 1
# define rs (x << 1) | 1

using namespace std;
const int N = 3.5e4 + 5;
int nums[N], mp[N], last[N], n, K;

vector<int> val, tag;

void init() {
    val = vector(4 * (n + 5), 0);
    tag = vector(4 * (n + 5), 0);
}

void add(int x, int l, int r, int pos, int v) {
    if(l == r) {
        val[x] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, pos, v);
    else add(rs, mid + 1, r, pos, v);
    val[x] = max(val[ls], val[rs]);
}

void down(int x) {
    if(tag[x] == 0) return;
    tag[ls] += tag[x], tag[rs] += tag[x];
    val[ls] += tag[x], val[rs] += tag[x];
    tag[x] = 0;
}

void change(int x, int l, int r, int a, int b, int v) {
    if(a <= l && r <= b) {
        tag[x] += v;
        val[x] += v;
        return;
    }
    down(x);
    int mid = (l + r) >> 1;
    if(a <= mid) change(ls, l, mid, a, b, v);
    if(b > mid) change(rs, mid + 1, r, a, b, v);
    val[x] = max(val[ls], val[rs]);
}

int search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return val[x];
    down(x);
    int mid = (l + r) >> 1, res = 0;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) res = max(res, search(rs, mid + 1, r, a, b));
    return res;
}

int main() {
    cin >> n >> K;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    memset(mp, 0, sizeof(mp)), memset(last, 0, sizeof(last));
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        last[i] = mp[num];
        mp[num] = i;
    }
    vector<vector<int>> dp(K + 1, vector(n + 1, 0));
    for(int k = 1; k <= K; k++) {
        init();
        for(int j = 1; j <= n; j++)
            add(1, 0, n, j, dp[k - 1][j]);
        for(int i = k; i <= n; i++) {
            change(1, 0, n, last[i], i - 1, 1);
            dp[k][i] = search(1, 0, n, k - 1, i - 1);
        }
    }
    cout << dp[K][n] << endl;
    return 0;
}