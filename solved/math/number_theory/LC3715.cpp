/**
 * @Time : 2025/10/13-12:29
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3715 2252 数学 数论 暴力枚举 回溯
 */
 /*
  * num1 = a^2 * b * c^3
  * 那么num2 = f * 完全平方数, 其中f = b * c
  *
  * 先因式分解 得到每个数的奇数次幂因子
  * 然后再枚举完全平方数t 看祖先节点的值有多少为 t * f
  * 1e5的范围内大约有330个完全平方数
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31, N = 1e5 + 5;
int factor[N], cnt[N] = {0};

vector<int> prime, isPrime(N + 1, 1);
int cal_factor(int num) {
    int ans = 1;
    for(int i = 0; i < prime.size() && !isPrime[num]; i++) {
        int count = 0;
        while(num > 1 && num % prime[i] == 0)
            num /= prime[i], count++;
        if(count % 2 == 1) ans *= prime[i];
    }
    return ans * num;
}

int init1 = []() {
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    // 获取质因子后 对每个数预处理其奇数次质因子的乘积
    for(int i = 1; i < N; i++)
        factor[i] = cal_factor(i);
    return 0;
}();

class Solution {
public:
    ll ans = 0;
    vector<vector<int>> graph;
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
        graph.assign(n, {});
        for(auto& edge : edges)
            graph[edge[0]].push_back(edge[1]), graph[edge[1]].push_back(edge[0]);
        dfs(nums, 0, -1);
        return ans;
    }

    void dfs(vector<int>& nums, int v, int f) {
        int num = nums[v];
        for(int i = 1; i * i * factor[num] < N; i++)
            ans += cnt[i * i * factor[num]];
        cnt[num]++;
        for(int w : graph[v]) {
            if(w == f) continue;
            dfs(nums, w, v);
        }
        cnt[num]--;
    }
};