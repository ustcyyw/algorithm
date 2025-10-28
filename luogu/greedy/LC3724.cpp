/**
 * @Time : 2025/10/27-20:50
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3724 1740 暴力枚举 贪心
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2) {
        ll sum = 1, mv = INT_MAX;
        for(int i = 0, last = nums2.back(); i < nums1.size(); i++) {
            int n1 = nums1[i], n2 = nums2[i];
            sum += abs(n1 - n2);
            ll l = min(n1, n2), r = max(n1, n2);
            if(last >= l && last <= r) mv = 0;
            else if(last < l) mv = min(mv, l - last);
            else mv = min(mv, last - r);
        }
        return sum + mv;
    }
};