/**
 * @Time : 2025/10/27-14:53
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3728 1908 哈希表计数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    long long countStableSubarrays(vector<int>& nums) {
        unordered_map<int, unordered_map<ll, int>> maps;
        ll sum = 0, ans = 0;
        for(int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            sum += num;
            ll ps = sum - 2 * num;
            if(maps.count(num))
                ans += maps[num][ps];
            maps[num][sum]++;
            if(i > 0 && num == 0 && nums[i - 1] == 0)
                ans--;
        }
        return ans;
    }
};