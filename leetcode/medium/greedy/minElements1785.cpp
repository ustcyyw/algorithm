/**
 * @Time : 2022/12/28-3:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        long sum = accumulate(nums.begin(), nums.end(), 0l);
        long diff = abs(sum - goal);
        return diff % limit == 0 ? diff / limit : diff / limit + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}