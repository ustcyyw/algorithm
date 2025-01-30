/**
 * @Time : 2025/1/29-9:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF27C 1900 贪心 前后缀分解
 */
 /*
  * 非有序序列 也就是得在递增和递减之间至少切换一次 要求最短序列
  * 那么就没必要切换多次 切换一次即可
  * 以递增切换递减为例 只要能找到一个非有序序列 那么其最小长度一定为3
  * 如果长度大于3 而且是递增切换递减的序列 那么一定存在一个最大值 并且这个最大值不是第一个、最后一个元素
  * 只要保留这个最大值 两边各取一个更小的元素即可
  * 因此进行前后缀分解 找前缀和后缀的最小值 枚举中间值即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353, M = 31;
int T, n, nums[N];
vector<int> ans;

void check() {
    vector<int> suf(n + 1, -1);
    for(int i = n, j = n; i >= 1; i--) {
        if(nums[i] < nums[j]) j = i;
        suf[i] = j;
    }
    for(int i = 1, j = 1; i < n; i++) {
        if(nums[i] < nums[j]) j = i;
        if(nums[i] > nums[j] && nums[i] > nums[suf[i + 1]]) {
            ans = {j, i, suf[i + 1]};
        }
    }
}

void solve() {
    check();
    if(!ans.empty()) {
        cout << "3\n" << ans[0] << " " << ans[1] << " " << ans[2];
        return;
    }
    for(int i = 1; i <= n; i++)
        nums[i] *= -1;
    check();
    if(!ans.empty())
        cout << "3\n" << ans[0] << " " << ans[1] << " " << ans[2];
    else cout << 0;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >>nums[i];
        solve();
    }
};