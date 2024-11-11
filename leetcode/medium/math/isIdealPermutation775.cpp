/**
 * @Time : 2022/11/17-3:25 PM
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
     * 任何一个局部倒置都是一个全局倒置
     * 因此只要找到一个全局倒置不是局部倒置，就能保证数量不相等
     *
     * 因为nums中的数字是从0到n-1的。
     * 如果一个数字i不在索引i，在索引j处
     * 如果 abs(j - i) >= 2，比如 j = i + 2
     * 那么相较于完全排序的数组，该数字左边会被塞入更多2个数字
     * 尽可能的保证不出现倒置，其左边原本就都放入比它小的数字，现在加2个进去，就必然更大
     * 就出现了全局倒置（最好情况下，其中一个可能是局部倒置）
     * 于是就不满足相等的情况了。
     *
     * abs(j - i) == 1，这种情况，全局倒置可能就是局部倒置，不能断定不想等
     */
    bool isIdealPermutation(vector<int>& nums) {
        for(int i = 0; i < nums.size(); i++)
            if(abs(i - nums[i]) > 1) return false;
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}