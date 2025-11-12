/**
 * @Time : 2025/1/28-2:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3303 字符串 字符串hash
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;
ull x[N];
int init = []() -> int {
    x[0] = 1;
    for (int i = 1; i < N; i++)
        x[i] = x[i - 1] * P;
    return 0;
}();

vector<ull> str_hash(string &s) {
    int n = s.size();
    vector<ull> h(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * P + s[i - 1];
    }
    return h;
}

ull get_hash(vector<ull> &h, int l, int r) {
    return h[r + 1] - h[l] * x[r - l + 1];
}

ull replace(vector<ull> &h, int i, char oc, char c) {
    ull temp = h.back();
    int n = h.size() - 1;
    return temp - oc * x[n - 1 - i] + c * x[n - 1 - i];
}

class Solution {
public:
    int minStartingIndex(string s, string pattern) {
        vector<ull> code1 = str_hash(s), code2 = str_hash(pattern);
        unordered_map<ull, int> map;
        int n = s.size(), m = pattern.size();
        for(int i = 0; i + m - 1 < n; i++) {
            ull temp = get_hash(code1, i, i + m - 1);
            if(!map.count(temp)) map[temp] = i;
        }
        int ans = INT_MAX;
        for(int i = 0; i < m; i++) {
            for(char c = 'a'; c <= 'z'; c++) {
                ull temp = replace(code2, i, pattern[i], c);
                if(map.count(temp)) ans = min(ans, map[temp]);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};