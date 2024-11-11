/**
 * @Time : 2023/11/29-11:00 PM
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
     * target正负都一样 都是离起点的距离为abs(target)
     * 走的长度为1,2,3...n，最远也就能走到 n * (n + 1) / 2
     * 所以最少也需要走 sqrt(2 * target) 步
     * 假设现在走了i步 走的最远距离是 sum = i * (i + 1) / 2
     * 首先要求 sum >= target
     * 其次 如果走的过程中 有一些时候是往反方向走 影响是双重的
     * 不能对正向距离做贡献了，还要因为走方向而减少距离，因此 走到对位置是 sum - 2(a + b + ... + x)
     * 如果刚好走到target说明 2(a + b + ... + x) = sum - target
     * 也就是说 sum - target得是偶数
     * 能一定凑出来吗 因为走的步数是从1,2,3...n, 这个序列可以表示出任何偶数 所以一定能凑出来
     */
    int reachNumber(int target) {
        target = abs(target);
        for(int i = sqrt(2 * target); i < 1e9; i++) {
            long long sum = (long long) i * (i + 1) / 2;
            if(sum >= target && (sum - target) % 2 == 0)
                return i;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}