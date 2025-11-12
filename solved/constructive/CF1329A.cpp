/**
 * @Time : 2025/1/20-5:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1329A 1800 构造 贪心
 */
 /*
  * 染色区间是[p,li + p - 1] 染色的区间长度都是li，可以染的区间的左端点是任意取的
  * 加起来的区间长度不足n 肯定不行
  * 刚好是n，那按顺序排即可
  * 超过n 就有一些位置会被重复染色
  *
  * 假设现在染色i，那么前面有i-1个颜色 他们至少要有i-1个格子
  * 如果当前染色占用完格子后 不足i-1个格子 就会有颜色没法最终留下来 这种情况也没法完成染色
  *
  * 如果当前涂色 从第i个格子开始（就是前面i-1种颜色都分别占1个格子）
  * 后续的染色也能顺着当前染色的结尾开始染 然后填满 就这样做
  * 如果不能 说明当前染色要从更靠后的位置开始染
  * 那就直接从后往前安排，不进行颜色的覆盖 直到第i+1次染色 会将一部分i颜色覆盖
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7, R = 26;
ll T, n, m, l[N], sum[N], ans[N];

bool check() {
    if(sum[1] < n) return false;
    for(int i = 1; i <= m; i++) { // 以最紧凑的安排方式 还是有颜色被完全覆盖
        if(n - l[i] < i - 1) return false;
    }
    return true;
}

void solve() {
    int i = 1;
    for(; i <= m; i++) {
        if(sum[i + 1] >= n - (i - 1 + l[i])) ans[i] = i;
        else break;
    }
    for(int j = m; j >= i; j--)
        ans[j] = n - sum[j] + 1;
    for(int j = 1; j <= m; j++)
        cout << ans[j] << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= m; i++)
            cin >> l[i];
        sum[m] = l[m];
        for(int i = m - 1; i >= 1; i--)
            sum[i] = l[i] + sum[i + 1];
        if(!check()) cout << "-1";
        else solve();
    }
};