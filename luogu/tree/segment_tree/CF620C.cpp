/**
 * @Time : 2023/12/16-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1

using namespace std;
const int N = 3e5 + 5;
int n, nums[N];
pair<int, int> infos[4 * N];

void add(int x, int l, int r, int v, int pos) {
    if(l == r) {
        infos[x] = {v, pos};
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, v, pos);
    else add(rs, mid + 1, r, v, pos);
    if(infos[ls].first > infos[rs].first) infos[x] = infos[ls];
    else infos[x] = infos[rs];
}

pair<int, int> search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return infos[x];
    pair<int, int> res = {-1, -1};
    int mid = (l + r) >> 1;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) {
        pair<int, int> t = search(rs, mid + 1, r, a, b);
        if(t.first > res.first) res = t;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    add(1, 0, n, 0, 0);
    map<int, int> last;
    vector<int> left(n + 1, 0), dp(n + 1, -1);
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        dp[i] = dp[i - 1], left[i] = left[i - 1]; // 考虑当前数字跟着前一个数字一组的情况
        if(last.count(num)) { // 当前数字可以做右边界 左边界最大为last[num] 分割成一个子数组
            pair<int, int> t = search(1, 0, n, 0, last[num] - 1);
            if(t.first + 1 > dp[i])
                dp[i] = t.first + 1, left[i] = t.second;
        }
        if(dp[i] <= 0) dp[i] = -1;
        add(1, 0, n, dp[i], i);
        last[num] = i;
    }
    if(dp[n] == -1) {
        cout << -1 << endl;
        return 0;
    }
    cout << dp[n] << endl;
    for(int i = n; i != 0; i = left[i])
        cout << left[i] + 1 << " " << i << "\n";
}