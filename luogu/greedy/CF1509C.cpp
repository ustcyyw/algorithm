/**
 * @Time : 2025/1/15-11:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1509C 1800 动态规划 贪心
 */
 /*
  * 对于位置n，无论放的数是多少d[n]都是数组最大值-数组最小值
  * 但是
  * 如果最后一个数选了最小值，那么前一个位置会变成 最大值-次小值
  * 如果最后一个数选了最大值，那么前一个位置会变成 次大值-最小值
  * 如果不选以上两个数，前一个位置还是 最大值-最小值
  * 因此最后一个位置应该放 最大值 or 最小值
  * 然后剩下n-1个数 又面临了上述问题 但依然是选现有但最大值 or 最小值
  * 定义dfs(lo, hi)：剩余的数为nums[lo...hi]上时 排列后 所求值的最小值
  * 无论是安排nums[lo]还是安排nums[hi]在当前的最后一个位置
  * 这个位置的d值都是nums[hi] - nums[lo]
  * 接下来是两个选择 dfs(lo + 1, hi), dfs(lo, hi - 1)
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, nums[N], ans[N];
vector<vector<ll>> cache;

ll dfs(int lo, int hi) {
    if(lo == hi) return 0;
    if(cache[lo][hi] != -1) return cache[lo][hi];
    ll t1 = dfs(lo + 1, hi), t2 = dfs(lo, hi - 1);
    return cache[lo][hi] = min(t1, t2) + nums[hi] - nums[lo];
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        cache = vector(n + 1, vector(n + 1, -1ll));
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        sort(nums, nums + n + 1);
        cout << dfs(1, n) << "\n";
    }
};