/**
 * @Time : 2023/3/22-10:04 PM
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
     * 题目划线排序 就是一个干扰项
     * 如果你需要某一个数字，完全就像插入排序那样
     * 将某个数字与其前面的数字比较，只要更小就能持续换到需要的位置
     * 并且在这个移动中，前置部分的数字相对位置是保持不变的
     *
     * 考虑当前正在使s[i] == t[i]，当前所需数字num = t[i]
     * 要将s[i, n - 1]中的一个num换到前面
     * 如果s[i, n - 1]中第一个num前面还有数字小于num，就无法完成交换
     * 否则可以将第一个num依次比较后交换到i位置，其它数字相对位置不变
     *
     * 为何选取第一个num而不是第二个第三个?
     * 因此 将第二个num换到前面，改变了未使用数字的相对位置
     * 并且如果num是0，1这样很小的数字，将后面的换到前面，就可能挡到别的数字的移动
     * 显然不会比移动第一个num好
     *
     * 判断是否可以移动数字到i位置，就是查看该数字前面有没有更小的数字
     * 根据数字分类记录下标，num的第一个位置在 nums[num].front()
     * 比num小的数字 0 ~ num - 1，他们最靠左的位置出现在 nums[num].front()左边，就挡住了num的移动
     * !nums[i].empty() && nums[i].front() < nums[num].front()
     */
    bool isTransformable(string s, string t) {
        int n = s.size();
        vector<queue<int>> nums(10);
        for(int i = 0; i < n; i++)
            nums[s[i] - '0'].push(i);
        for(int i = 0; i < n; i++){
            if(!check(nums, t[i] - '0')) return false;
            nums[t[i] - '0'].pop();
        }
        return true;
    }

    bool check(vector<queue<int>>& nums, int num){
        if(nums[num].empty()) return false;
        for(int i = 0; i < num; i++){
            if(!nums[i].empty() && nums[i].front() < nums[num].front())
                return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}