/**
 * @Time : 2024/3/3-4:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 1;
        unordered_map<int, int> f;
        for(int num : nums) {
            f[num + 1] = f[num] + 1;
            f[num] = f[num - 1] + 1;
            res = max(res, max(f[num + 1], f[num]));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}