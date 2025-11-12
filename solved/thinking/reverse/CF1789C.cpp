/**
 * @Time : 2025/1/11-2:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1789C 1500 思维 正难则反 贡献法
 */
/*
  * 考虑每个值贡献的次数 正难则反
  * m次修改操作 A0,A1...Am。一共有 m * (m + 1) / 2 组数组对
  * 共 total = m * (m + 1) 个数组，如果这些数组的元素都不重复 那么不重复元素的个数和为 total * n
  * 答案还要减去重复的元素的个数
  * 对于元素v，如果其在A[0,m]中出现了cnt >= 2次
  * 那么任选两个数组(Ai,Aj)，有可能两个数组中都有v
  * 此时Ai+Aj中的v按原本默认元素不重复的计算，是多算了一次的，要-1
  * 共有C(cnt, 2)个(Ai,Aj)中v重复，因此一共要减去C(cnt, 2)
  *
  * 在修改的过程中 用idx[v]表示v上一次存在是哪一次操作
  * 每次修改 原本的元素消失，新的元素出现
  * 要更新原本元素的出现次数 记录新元素的这次存在
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, m, nums[N], cnt[N * 2], idx[2 * N];

void solve() {
    for(int i = 1, j, v; i <= m; i++) {
        cin >> j >> v;
        int pre = nums[j];
        cnt[pre] += i - idx[pre];
        idx[pre] = -1;
        idx[v] = i, nums[j] = v;
    }
    ll ans = m * (m + 1) * n;
    for(int i = 1; i <= n + m; i++) {
        if(idx[i] != -1) cnt[i] += m - idx[i] + 1;
        if(cnt[i] >= 2)
            ans -= cnt[i] * (cnt[i] - 1) / 2;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        fill(cnt, cnt + m + n + 1, 0);
        fill(idx, idx + m + n + 1, -1);
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            idx[nums[i]] = 0;
        }
        solve();
    }
};