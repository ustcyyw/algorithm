/**
 * @Time : 2025/10/13-23:47
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3713 1436 前缀和 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31, N = 1e5 + 5;
int sum[26][N];

class Solution {
public:
    int longestBalanced(string s) {
        s = '.' + s;
        int n = s.size();
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < 26; j++)
                sum[j][i] = sum[j][i - 1];
            sum[s[i] - 'a'][i]++;
        }
        for(int len = n - 1; len > 1; len--) {
            for(int i = 1, j = i + len - 1; j < n; i++, j++)
                if(check(i, j)) return len;
        }
        return 1;
    }

    bool check(int l, int r) {
        int val = -1;
        for(int j = 0; j < 26; j++) {
            int v = sum[j][r] - sum[j][l - 1];
            if(v == 0) continue;
            if(val == -1) val = v;
            else if(val != v) return false;
        }
        return true;
    }
};