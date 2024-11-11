/**
 * @Time : 2022/5/23-11:13 PM
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
     * 执行用时：8 ms, 在所有 C++ 提交中击败了87.42%的用户
     * 内存消耗：10.5 MB, 在所有 C++ 提交中击败了79.90%的用户
     *
     * 假如选定统一的数为key，小于key的数有a个，大于key的数有b个
     * 那么统一的数变为key + 1，所需要的操作次数变化量为
     * a - b (a个数要多+1，b个数少-1)
     * 因此如果a > b 这个操作会让次数变多，因此应该key - 1 定为基准
     * 如果 a < b 这个操作会让次数变少，因此就应该是key + 1
     * 于是发现key的变化方向应该是尽可能的让a = b
     *
     * 那么直接取key为数组中排序为中间的数即可保证，a尽可能的等于b
     */
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int key = nums.size() / 2, res = 0;
        for(int& num : nums)
            res += abs(num - key);
        return res;
    }
};

int main(){

}