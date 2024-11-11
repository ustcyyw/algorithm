/**
 * @Time : 2024/2/28-9:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛385 t4
 */

/*
 * 字符串hash找相同的前缀和后缀
 * 注意 所有words[i]的长度之和不超过5e5，所以可以枚举每个字符串的每个前缀、后缀长度
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int p[2] = {29, 31}, mod[2] = {int(1e9 + 9), 998244353}, N = 1e5 + 5;
ll x[2][N];
int init = []() -> int {
    x[0][0] = x[1][0] = 1;
    for(int k = 0; k < 2; k++) {
        for (int i = 1; i < N; i++) {
            x[k][i] = 1ll * x[k][i - 1] * p[k] % mod[k];
        }
    }
    return 0;
}();
class Solution {
public:
    vector<vector<ll>> str_hash2(string &s) {
        int n = s.size();
        vector<vector<ll>> h(2, vector(n + 1, 0ll));
        for(int k = 0; k < 2; k++) {
            for (int i = 1; i <= n; i++) {
                h[k][i] = (1ll * h[k][i - 1] * p[k] + s[i - 1]) % mod[k];
            }
        }
        return h;
    }

    ll get_hash2(vector<vector<ll>> &h, int l, int r) {
        vector<ll> res(2, 0ull);
        for (int k = 0; k < 2; k++) {
            ll t = (h[k][r + 1] - 1ll * h[k][l] * x[k][r - l + 1]) % mod[k];
            res[k] = (t + mod[k]) % mod[k];
        }
        return 1ll * res[0] * 1e6 + res[1];
    }

    long long countPrefixSuffixPairs(vector<string>& words) {
        long long res = 0;
        unordered_map<ll, int> map;
        for(int i = words.size() - 1; i >= 0; i--) {
            vector<vector<ll>> h = str_hash2(words[i]);
            int n = words[i].size();
            res += map[get_hash2(h, 0, n - 1)];
            for(int l = 1; l <= n; l++) {
                ll h1 = get_hash2(h, 0, l - 1), h2 = get_hash2(h, n - l, n - 1);
                if(h1 == h2) map[h1]++;
            }
        }
        return res;
    }
};