/**
 * @Time : 2023/4/18-9:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
     * 车从静止开始向前走的距离，与起点位置无关，与前进方向也无关。
     * 可以定义 dp[i]：车从静止开始，向前走的距离为i，所用的最短步骤
     * 特殊地，我们发现
     * i = 0，用了0个步骤； i = 1，用了1个步骤（A）
     * i = 3，用了2个步骤（AA）； i = 7，用了3个步骤（AAA）
     * ...
     * 走到s[k] = 2 ^ k - 1位置，总共用k个步骤即可。
     * 要计算dp[target]，如果target刚好是特殊位置，直接就有答案
     * 否则 target 一定在某个s[k]和s[k-1]之间    s[k-1] < target < s[k]
     * 1.target从s[k]退回来
     * 通过一次R，停在点s[k]，然后以s[k]为起点，向当前方向前方行走s[k]-target的长度
     * 走到s[k]花费的步骤是k,有一次R操作，步骤再+1
     * 向当前方向前方行走s[k]-target的长度，根据定义就是dp[s[k]-target]
     *
     * 2.target从s[k-1]到达
     * 如果s[k-1]不做任何操作，就向前走，一步就到达s[k]了，就成了第一种情况。
     * 因此只需要考虑在s[k-1]这个点先进行一次R操作的情况，即先退回到某个点，再掉头来到target
     * 到达s[k-1]花费的步骤是k-1，进行两次R操作，步骤再+2
     * 假设回退的距离为back，那么从退回点到target的距离为 back + target - s[k - 1]
     * 步骤 + dp[back + target - s[k - 1]]。
     * 退回到哪个点，并不知道，只能进行枚举。
     * back = s[j]，其中j = 0,1,2,...,k - 2 保证 back < s[k - 1]。退back的距离 步骤 + j
     * (因为如果back = s[k - 1]，就是回到起点 没有任何意义)
     *
     * s[k]-target的说明:
     * s[k-1] * 2 + 1 = s[k] 且 target > s[k-1]
     * --> target + s[k-1] + 1 > s[k-1] * 2 + 1 = s[k]
     * --> s[k] - target < s[k-1] + 1
     * --> s[k] - target <= s[k-1] < target
     * 因此计算target时，要把比target小的位置先算出来
     *
     * back + target - s[k - 1]的说明
     * 从s[k - 1]往回退，back != s[k - 1]，否则回到起点 没有任何意义
     * back < s[k - 1]
     * back - s[k - 1] + target < target
     * 因此计算target时，要把比target小的位置先算出来
     *
     * 综上 计算方向从小到大
     */
vector<int> dp(1e4 + 5, 0);
int init = []() {
    // s1 s2 分别代表s[k - 1],s[k]
    for(int i = 1, k = 1, s1 = 0, s2 = 0; i < dp.size(); i++){
        if(i == (1 << k) - 1){
            dp[i] = k;
            s1 = (1 << k) - 1, s2 = (1 << (k + 1)) - 1;
            k++;
            continue;
        }
        dp[i] = k + 1 + dp[s2 - i];
        for(int j = 0; (1 << j) - 1 < s1; j++)
            dp[i] = min(dp[i], k + 1 + dp[(1 << j) - 1 + i - s1] + j);
    }
    return 0;
}();
class Solution {
public:
    int racecar(int target) {
        return dp[target];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}