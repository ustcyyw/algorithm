/**
 * @Time : 2023/1/4-9:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * odd 子序列元素个数为奇数时的最大交替和
     * even 子序列元素个数为偶数时的最大交替和
     */
    long long maxAlternatingSum(vector<int>& nums) {
        long long res = 0, even = 0, odd = 0;
        for(int num : nums){
            long long tempO = max(even + num, (long long)num), tempE = max(odd - num, 0ll);
            res = max(res, max(tempE, tempO));
            odd = max(odd, tempO), even = max(even, tempE);
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {6,2,1,2,4,5};
    s.maxAlternatingSum(arr);
    cout << 0 << endl;
}