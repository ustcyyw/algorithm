/**
 * @Time : 2025/10/27-11:10
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3659 1439 模拟 结论题
 */
 /*
  * 总共n个元素，k个一组，总共有m组
  * 那么只要有数字出现次数超过m，就至少有一个组中 该元素重复出现
  * 反之，所有数字的出现次数均 <= m，就可以按如下方法完成分配
  * 依次分配每类相同数字，总是找当前数字最少的组放入数字
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        if(nums.size() % k != 0) return false;
        int m = nums.size() / k;
        unordered_map<int, int> map;
        for(int num : nums) {
            map[num]++;
            if(map[num] > m) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}