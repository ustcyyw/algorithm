/**
 * @Time : 2023/2/22-11:42 AM
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
     * 摩尔投票：选出出现次数大于数组长度一半的元素
     * 遇到不同的元素就将累计次数（的票数）-1，相同元素就将累计次数（的票数）+1
     * 如果当前累计次数是0，就让当前元素成为候选人，然后累计次数改为1
     *
     * 正确性的保证：该元素出现次数超过数组长度的一半
     * 比如数组长度为9，那么该元素得出现至少5次; 数组长度为8，那么该元素得出现至少5次
     * 摩尔投票类比投票中的pk，两个人各得1票，等于这两个人还是0票
     * 极端情况下除了最高票的人，其余人都和最高票pk，由于最高票的人超过半数，他还是获胜
     *
     * 但如果出现次数没有超过一半，使用摩尔投票就不一定找到最高票了。
     *
     * 也就是说在不知道数组中有没有元素超过数组长度一半的情况下
     * 使用摩尔投票这个算法得出的结果：
     * 1.该元素没有超过一半，那么也不可能有别的元素超过一半
     * 2.该元素超过了一半，就是正确答案
     */
    int moer_vote(vector<int>& nums){
        int vote = 0, candidate = -1;
        for(int num : nums){
            if(vote == 0) candidate = num;
            if(num == candidate) vote++;
            else vote--;
        }
        return candidate;
    }
    /*
     * 利用摩尔投票 pk，抵消这个思路
     * 如果有两群人，得票最多分别是a和b，获得票数分别是av和bv
     * av > bv 则说明a是最有可能在两群人合并后 得票超过一半的，如果a不是，那么这群人就不可能有得票超过一半的
     * bv > av 则相反
     */
    // LC1157题运用了这个思路
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}