/**
 * @Time : 2024/1/9-1:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 位运算 想到拆位 按位来分析
     */
    int minOperations(vector<int>& nums, int k) {
        int t = 0, cnt = 0;
        for(int num : nums)
            t ^= num;
        for(int i = 0; i <= 30; i++) {
            int t1 = (1 << i) & t, t2 = (1 << i) & k;
            if(t1 != t2) cnt++;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}