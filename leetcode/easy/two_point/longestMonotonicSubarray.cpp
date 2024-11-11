/**
 * @Time : 2024/4/7-12:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛392 t1
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = nums.size();
        function<int(int)> find = [&](int sign) -> int {
            int res = 1;
            for(int i = 0, j = 0; i < n - 1; ) {
                j = i;
                while(j < n - 1 && nums[j] * sign < nums[j + 1] * sign) j++;
                res = max(res, j - i + 1);
                i = j + 1;
            }
            return res;
        };
        return max(find(1), find(-1));
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}