/**
 * @Time : 2023/3/6-1:05 PM
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
     * 判断先手是否一定赢，一定输（后手一定输，一定赢）的题 优先想到博弈的方法
     * 解决问题的办法一般是：
     * 状态分析：根据题目给定的规则是判断「胜利」还是「失败」来决定优先分析「必胜态」还是「必败态」时具有何种性质
     * 然后证明性质是否可推广。
     *
     * 例如本题中说明：先手时如果所有数字的异或为0，则先手的人获胜
     * 因此我们分析 先手必胜的性质
     * 1.当前所有数字的异或为0，先手直接获胜
     * 2.反之，先手拿掉一个数字后，异或不为0，然后轮到后手，后手拿掉一个数字 回到1的情况，于是先手赢
     * 在2这种情况中，后手行动时的异或和记为 sum
     * 后手也是最优选择，如果能拿掉数字nums[i]，使得 nums[i] ^ sum != 0
     * （擦除一个数字，等价于在异或和上异或该数字）
     * 那么后手应该这样选择，于是就不会回到1这种状态
     * 也就是先手必胜的情况下，后手选择任何数字都会出现 nums[i] ^ sum == 0
     *
     * nums[0] ^ sum = nums[1] ^ sum = ... = nums[i] ^ sum = ... = nums[n - 1] ^ sum = 0
     * 注意：这是后手进行选择时的情况，n代表后手选择时的数字个数
     *
     * 将上述所有项进行异或
     * (nums[0] ^ sum) ^ (nums[1] ^ sum) ^ ... ^ (nums[i] ^ sum) ^ (nums[n - 1] ^ sum) = 0
     * 异或有交换律和结合律
     * (sum ^ sum ^ ... sum) ^ (nums[0] ^ nums[1] ^ ... nums[n - 1]) = 0
     * 后一项就是异或和 sum = nums[0] ^ nums[1] ^ ... nums[n - 1]
     * 前一项共有n个sum，那么共有 n + 1 个sum进行异或，并且等于0
     * 那么 n + 1就是偶数，也就是上一步，先手行动时，数字个数为偶数
     *
     * 因此我们得出 先手必胜的两个条件
     * 1.当前所有数字的异或为0; 2.先手行动时，数字个数为偶数
     */
    bool xorGame(vector<int>& nums) {
        if(nums.size() % 2 == 0) return true;
        int sum = 0;
        for(int num : nums)
            sum ^= num;
        return sum == 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}