/**
 * @Time : 2023/7/17-3:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int m = 3e5 + 5;
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        int res = 0;
        vector<int> diff(m, 0);
        for(int num : nums)
            diff[num]++, diff[num + 2 * k + 1]--;
        for(int i = 0, sum = 0; i < m; i++) {
            sum += diff[i];
            res = max(res, sum);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}