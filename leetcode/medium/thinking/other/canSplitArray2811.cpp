/**
 * @Time : 2023/8/8-11:25 AM
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
     * 如果有某个元素大于等于m 就以这个元素为中心 陆续将其左边/右边的元素分开
     *
     * 同样的 如果有相邻的两个元素之和>=m
     * 就以这两个元素为中心 陆续将其左边/右边的元素分开
     * 最后将这两个元素分开即可
     *
     * 如果任意相邻两个元素之和<m
     * 对于序列数组 a b c d
     * 因为a + b < m, 那么想把a单独分出去，一定是在 a b c 或者 a b c d 这个数组中拆分出去a
     * 那么剩下的b c d，因为b + c < m，想把b单独分出去，一定是在 b c d 这个数组中拆分出去b
     * 但是c + d < m 不运行进行上述拆分
     * 因此整个拆分完成不了。
     */
    bool canSplitArray(vector<int>& nums, int m) {
        int n = nums.size();
        if(n == 1 || n == 2) return true;
        for(int i = 0; i < n - 1; i++)
            if(nums[i] + nums[i + 1] >= m) return true;
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}