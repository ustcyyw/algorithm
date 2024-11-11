/**
 * @Time : 2024/5/23-9:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1256E 贪心 动态规划+线段树优化
 */
 /*
  * 肯定是排序后连续的一部分分在一组 因为有间隔的话
  * 总是可以调整让其中一组最大值变小 另外一组最小值变大 从而整体减小了差值
  *
  * dp[i]: 截止第i个人的最小差值
  * dp[i] = min{dp[j] + nums[i] - nums[j + 1], for i - j >= 3 (j <= i - 3)}
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, ans[N], dp[N], info[N][2];
vector<vector<int>> arr;

#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val, idx;
    // 单点修改
    void add(int x, int l, int r, int pos, int v, int i) {
        if(l == r) {
            val[x] = v, idx[x] = i;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v, i);
        else add(rs, mid + 1, r, pos, v, i);
        if(val[ls] < val[rs]) val[x] = val[ls], idx[x] = idx[ls];
        else val[x] = val[rs], idx[x] = idx[rs];
    }

    vector<int> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return {val[x], idx[x]};
        int mid = (l + r) >> 1;
        vector<int> res = {MAX_VAL, -1};
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) {
            vector<int> temp = search(rs, mid + 1, r, a, b);
            if(temp[0] < res[0]) res = temp;
        }
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
        idx = vector(4 * (n + 1), -1);
    }

    void add(int pos, int v, int i) {
        add(1, 0, n, pos, v, i);
    }

    vector<int> search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void solve() {
    sort(arr.begin(), arr.end());
    SegmentTree tree(n);
    tree.add(0, -arr[1][0], 0);
    for(int i = 3; i <= n; i++) {
        vector<int> temp = tree.search(0, i - 3);
        dp[i] = temp[0] + arr[i][0];
        info[i][0] = temp[1], info[i][1] = info[temp[1]][1] + 1;
        if(i + 1 <= n) tree.add(i, dp[i] - arr[i + 1][0], i);
    }
    cout << dp[n] << " " << info[n][1] << "\n";
    for(int i = n, j = info[n][0]; i > 0; ) {
        int id = info[i][1];
        while(i > j) {
            ans[arr[i][1]] = id;
            i--;
        }
        j = info[i][0];
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    arr.push_back({MIN_VAL, 0});
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        arr.push_back({num, i});
    }
    solve();
};