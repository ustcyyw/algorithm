/**
 * @Time : 2025/11/5-13:02
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3649 1715 数学 双指针
 */
 /*
  * 令 a = nums[i]，b = nums[j]。那么：
min(|a - b|, |a + b|) <= min(|a|, |b|)
max(|a - b|, |a + b|) >= max(|a|, |b|)

第二个等式一定成立
都是0，左边右两边都是0 成立
其中一个是0 abs(b) >= abs(b) 或者 abs(a) >= abs(a) 成立
同号的情况 abs(a + b) > max(abs(a), abs(b))
异号的情况 abs(a - b) > max(abs(a), abs(b))
所以实际上只用管第一个 等式即可

假设枚举的是绝对值更小的数a
min(|a - b|, |a + b|) <= abs(a)
同号 abs(a - b) <= abs(a)
b - a <= a, a >= b / 2

abs(b) <= 2 * abs(a)

异号 abs(a + b) <= abs(a)
b - abs(a) <= abs(a)
abs(b) - abs(a) <= abs(a)

abs(b) <= 2 * abs(a)
  */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        unordered_map<int, int> map;
        for(int num : nums)
            map[abs(num)]++;
        vector<vector<int>> arr;
        for(auto& p : map)
            arr.push_back({p.first, p.second});
        sort(arr.begin(), arr.end());
        int n = arr.size();
        vector<ll> sum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + arr[i - 1][1];
        ll ans = 0;
        for(int i = 0, j = 0; i < n; i++) {
            while(j < n && arr[j][0] <= 2 * arr[i][0]) j++;
            ans += (sum[j] - sum[i + 1]) * arr[i][1];
            ans += (ll)arr[i][1] * (arr[i][1] - 1) / 2;
        }
        return ans;
    }
};