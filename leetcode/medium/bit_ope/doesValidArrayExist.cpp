/**
 * @Time : 2023/5/14-4:13 PM
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
     * d[0] = nums[0] ^ nums[1]
     * d[0] ^ nums[0] = nums[1]
     *
     * d[1] = nums[1] ^ nums[2]
     * d[1] ^ nums[1] = nums[2]
     * -> d[1] ^ (d[0] ^ nums[0]) = nums[2]
     * -> nums[0] ^ d[0] ^ d[1] = nums[2]
     *
     * d[2] = nums[2] ^ nums[3]
     * d[2] ^ nums[2] = nums[3]
     * -> d[2] ^ (nums[0] ^ d[0] ^ d[1]) = nums[3]
     * nums[0] ^ d[0] ^ d[1] ^ d[2] = nums[3]
     *
     * nums[0] ^ d[0] ^ d[1] ^ ... ^ d[n - 2] = nums[n - 1]
     * 两边同时异或nums[0]
     * d[0] ^ d[1] ^ ... ^ d[n - 2] = d[n - 1]
     * 两边再异或 d[n - 1]
     * d[0] ^ d[1] ^ ... ^ d[n - 2] ^ d[n - 1] = 0
     * 满足这个等式，说明有一个原数组可以得到derived
     */
    bool doesValidArrayExist(vector<int>& derived) {
        int res = 0;
        for(int num : derived)
            res ^= num;
        return res == 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}