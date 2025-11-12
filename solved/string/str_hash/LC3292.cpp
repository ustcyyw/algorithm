/**
 * @Time : 2025/1/31-11:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3292 字符串哈希 动态规划 二分 贪心
 */
 /*
  * 要用words中的word前缀拼凑t
  * 假设已经拼了t[0,lo - 1]，现在要从t[lo]开始拼接
  * 假设t[lo,j1], t[lo,j2]都是某个前缀 且j1 < j2
  * 显然只要t[lo,j2]是前缀，那么所有的i <= j2, t[lo,i]都是word的前缀
  * 所有的 i <= j2, t[0,i]都可以在t[0,lo - 1]的基础上再+1就能拼出来
  * 那么考虑t[lo,j1]就无意义了 因此我们只用考虑最长前缀（字符串hash + 二分可求）
  *
  * 令dp[i]: 拼接到t[0,i]的最小拼接次数
  * 已知 dp[0,lo-1]并且以t[lo]开头的word中最长前缀截止j
  * 那么所有的dp[lo, j] = min(dp[lo, j], dp[0,lo-1] + 1)
  * 注意计算方式是从左到右刷表，已经刷过的值显然会小于dp[0,lo-1] + 1
  * 所以状态转移的过程用一个变量记录已经刷过的位置的右边界
  * 每次可以更新值时 都从没有值的位置开始更新即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 5e4 + 5, P = 13331;
ull x[N];
int init = []() -> bool {
    x[0] = 1;
    for (int i = 1; i < N; i++)
        x[i] = x[i - 1] * P;
    return 0;
}();

vector<ull> str_hash(string &s) {
    int n = s.size();
    vector<ull> h(n + 1, 0);
    for (int i = 1; i <= n; i++)
        h[i] = h[i - 1] * P + s[i - 1];
    return h;
}

ull get_hash(vector<ull> &h, int l, int r) {
    return h[r + 1] - h[l] * x[r - l + 1];
}

class Solution {
public:
    unordered_set<ull> set;
    int minValidStrings(vector<string>& words, string target) {
        for(string& word : words) {
            vector<ull> h = str_hash(word);
            for(int len = 1; len <= word.size(); len++)
                set.insert(get_hash(h, 0, len - 1));
        }
        vector<ull> h = str_hash(target);
        int n = target.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int lo = 1, hi = 0; lo <= n; lo++) {
            if(dp[lo - 1] == INT_MAX) break;
            int j = search(h, lo - 1) + 1;
            for(int k = hi + 1; k <= j; k++)
                dp[k] = dp[lo - 1] + 1;
            hi = max(hi, j);
        }
        return dp[n] == INT_MAX ? -1 : dp[n];
    }

    int search(vector<ull>& h, int start) {
        int lo = start - 1, hi = h.size() - 2; // target长度是h.size() - 1，索引最大为h.size() - 2
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            ull code = get_hash(h, start, mid);
            if(set.count(code)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};