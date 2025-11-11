/**
 * @Time : 2025/11/10-09:54
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3644 1744 思维题 脑筋急转弯
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int num = -1;
        for(int i = 0; i < nums.size(); i++) {
            if(i == nums[i]) continue;
            if(num == -1) num = nums[i];
            else num &= nums[i];
        }
        return num == -1 ? 0 : num;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}