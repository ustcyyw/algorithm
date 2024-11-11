/**
 * @Time : 2024/6/30-3:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛404 t2 贪心 分类讨论
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 奇数序列、偶数序列、奇数和偶数交替出现的序列
    int maximumLength(vector<int>& nums) {
        int n = nums.size(), odd = 0, even = 0, cc = 0;
        for(int i = 0, flag = -1; i < n; i++) {
            int t = nums[i] % 2;
            if(t != flag) cc++, flag = t;
            if(t == 0) even++;
            else odd++;
        }
        return max({odd, even, cc});
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}