/**
 * @Time : 2024/1/21-4:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛122 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 如果用一个小的数 mod 一个大的数 小的数将剩下来
     * 因此原操作有一种直接的效果 就是用小的数将大的数踢掉
     *
     * 反过来 如果用大的数 mod 小的数 将可能产生一个更小的数
     * 如果产生的更小的数v < mv， 且v不为0。其中mv是nums数组中最小的数
     * 那么我们可以只生成一个v，然后用v踢掉原数组中所有数 数组长度就变为1
     * 如果没法生成 < mv的数，就说明其它数mod mv后都为0
     * 不如用mv将其它大的数踢掉后，然后互相取mod
     */
    int minimumArrayLength(vector<int>& nums) {
        int mv = INT_MAX, cnt = 0;
        for(int num : nums)
            mv = min(mv, num);
        for(int num : nums) {
            if(num % mv) return 1;
            if(num == mv) cnt++;
        }
        return (cnt + 1) / 2;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}