/**
 * @Time : 2024/3/3-3:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛125 t4
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
class Solution {
public:
    /*
     * 定义 dfs(v, f, flag)
     * dfs(v, f, 0): 表示父亲节点f没有操作 v初始阶段没有进行操作时，v子树价值和的最大值
     * dfs(v, f, 1): 表示因父亲节点f操作 使v初始阶段就进行1次操作时，v子树价值和的最大值
     * 在计算子树和时 可以默认v-w的每一条边都进行了操作 t1 = dfs(w, v, true)，累加 sum += t1
     * 同时计算 v-w每一条边都不操作 t2 = dfs(w, v, false)
     * 记录 t2 - t1 表示v-w不操作比操作带来的价值和的增量
     *
     * 但是还有v的价值要计算，(边的操作次数 + flag)的奇偶性影响v的价值
     * 因此要考虑 边的操作次数 + flag 为奇数、偶数两种情况。
     * 已经默认以v-w每一条边都进行操作，要调整边的操作次数 就应当优先选择 t2 - t1 最大的边
     * 因此要对 t2 - t1 的集合进行排序，然后枚举有多少条边不变
     * 根据flag与多少条边进行操作，确定v是否要和k异或
     *
     * 答案是 dfs(0, -1, false) 因为根结点没有父亲结点，也就不会被父亲结点操作影响 初始阶段没有进行操作
     */
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> graph(n, vector(0, 0));
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        vector<vector<ll>> cache(n, vector(2, -1ll));
        function<ll(int, int, bool)> dfs = [&](int v, int f, bool flag) -> ll {
            if(cache[v][flag] != -1) return cache[v][flag];
            ll sum = 0;
            vector<ll> arr;
            for(int w : graph[v]) {
                if(w == f) continue;
                ll t1 = dfs(w, v, true), t2 = dfs(w, v, false);
                sum += t1;
                arr.push_back(t2 - t1);
            }
            if(arr.empty()) return flag ? nums[v] ^ k : nums[v];
            sort(arr.begin(), arr.end());
            ll res = sum + ((flag + arr.size()) % 2 == 0 ? nums[v] : nums[v] ^ k);
            for(int i = arr.size() - 1; i >= 0; i--) {
                int time = i + flag;
                ll temp = time % 2 == 0 ? nums[v] : nums[v] ^ k;
                sum += arr[i];
                res = max(res, sum + temp);
            }
            cache[v][flag] = res;
            return res;
        };
        return dfs(0, -1, false);
    }

    /*
     * 关键1：任意两个点都可以同时被异或 同时不影响其它点
     * 题目给定一颗树 任意两点之间都有路径 将这条路径的所有边都进行一次操作
     * 那么除了路径的两个端点只与k异或一次；其它中间点都与k异或2次，没有变化
     *
     * 关键2：异或了k的点 是偶数个
     * 初始时候与k异或的点的数量是0。其它情况下，考虑选择了x和y两个点进行异或
     * 如果x和y都没和k异或，那么操作之后 异或的点数量+2
     * 如果x和y都和k异或过，那么操作之后 异或的点数量-2
     * 如果x和y一个和k异或过，一个没有，那么操作之后 异或的点数量不变
     *
     * 因此题目实际上求的是 从nums中挑选偶数个数与k异或 求操作后的最大和
     * dp[i][0]: 截止第i个元素 有偶数个数与k异或的最大和
     * dp[i][1]: 截止第i个元素 有奇数个数与k异或的最大和
     */
    long long maximumValueSum2(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<long long>> dp(n + 1, vector(2, 0ll));
        dp[0][0] = 0, dp[0][1] = -1e10;
        for(int i = 1; i <= n; i++) {
            ll temp = nums[i - 1] ^ k;
            dp[i][0] = max(dp[i - 1][0] + nums[i - 1], temp + dp[i - 1][1]);
            dp[i][1] = max(dp[i - 1][1] + nums[i - 1], temp + dp[i - 1][0]);
        }
        return dp[n][0];
    };
};