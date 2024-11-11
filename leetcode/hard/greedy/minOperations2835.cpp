/**
 * @Time : 2023/9/6-10:02 AM
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
     * 要得到2 可以用4变一次，或者用8变两次
     * 如果还需要4，前面用4变成2，那么还需要用8变一次为4，总共2次操作；或者4不变，8连续操作两次
     * 如果不需要4，用8操作两次得到2，用4只需要一次
     * 因此 要得到 2 ^ i, 用2 ^ (i+1) 来变，好于或者等于用2^(i+2) 来变
     *
     * 从target二进制下的低位开始考虑
     * 如果该位为1，nums中有2^i，就直接使用，并且用了一个2^i后，其余应该相加，以备target中更高位使用
     * 为什么不是操作一次变2^(i-1)呢，因为低位已经被我们处理完毕了
     * 没有2^i的话，就依次去看有没有2^(i+1),2^(i+2),用最解决的来进行操作是最优的
     */
    int minOperations(vector<int>& nums, int target) {
        long long sum = accumulate(nums.begin(), nums.end(), 0ll);
        if(sum < target) return -1;
        vector<int> cnt(32, 0);
        for(int num : nums) {
            for(int i = 0; i < 32; i++) {
                if((1 << i) & num) {
                    cnt[i]++;
                    break;
                }
            }
        }
        int res = 0;
        for(int i = 0; i < 31; i++) {
            if((1 << i) & target) {
                int j = i;
                while (cnt[j] == 0) j++; // 找到第一个可以用来贡献target当前位的数
                cnt[j]--; // 使用了2^j来贡献，那么2^j数量减少1
                if(j != i) { // 如果 j > i 那么从2^i到2^(j-1)的的数量都会增加1 并且要操作j - i次
                    res += j - i;
                    while (j > i) cnt[--j] += 1;
                }
            }
            cnt[i + 1] += cnt[i] / 2;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}