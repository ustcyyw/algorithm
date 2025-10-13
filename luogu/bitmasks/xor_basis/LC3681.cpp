/**
 * @Time : 2025/9/30-15:03
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3681 2025 位运算 异或线性基
 */
#include<bits/stdc++.h>
using namespace std;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31;
/*
 * 1. 两个子数组 相同的元素 就等于是没有任何作用
 * 2. 所以题目就是直接从数组中选择任意个元素 使得xor值最大
 */
class Solution {
public:
    int maxXorSubsequences(vector<int>& nums) {
        vector<int> basis(M + 1, 0);
        for(ll num : nums) {
            for(int i = M; i >= 0; i--) {
                if((num & (1ll << i)) == 0) continue;
                if(basis[i] == 0) {
                    basis[i] = num;
                    break;
                } else num ^= basis[i];
            }
        }
        ll val = 0;
        for(int i = M; i >= 0; i--) {
            val = max(val, basis[i] ^ val);
        }
        return val;
    }
};