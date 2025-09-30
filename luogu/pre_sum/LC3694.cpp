/**
 * @Time : 2025/9/29-15:22
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3694 1678 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, T = 1e9;
unordered_map<char, int> mp = {{'U',0}, {'D',1}, {'L',2}, {'R',3}};

class Solution {
public:
    int distinctPoints(string s, int k) {
        int n = s.size();
        vector<vector<int>> sum(4, vector(n + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 4; j++)
                sum[j][i] = sum[j][i - 1];
            sum[mp[s[i - 1]]][i]++;
        }
        unordered_set<ll> st;
        for(int i = 0; i + k - 1 < n; i++) {
            int hi = i + k - 1;
            ll c1 = sum[0][hi + 1] - sum[0][i] - (sum[1][hi + 1] - sum[1][i]);
            ll c2 = sum[2][hi + 1] - sum[2][i] - (sum[3][hi + 1] - sum[3][i]);
            st.insert(c1 * T + c2);
        }
        return st.size();
    }
};
