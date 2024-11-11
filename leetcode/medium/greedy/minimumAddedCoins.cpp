/**
 * @Time : 2023/12/3-3:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛374 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 是lc330的原题
     * 假如硬币中最小的不是1，为了表示出1，就得添加1进去。
     * 然后可以表示的面值就是 [1,1]
     * 想要表示出2,可以添加面值为2的硬币，这样能表示的范围就扩展成[1,3]
     *
     * 假设当前能表示的范围是[1,k]，为了表示出k+1
     * 首先看coins[i] 如果coins[i] <= k, 通过和前面已经可以表示的面值一结合 就能表示出k+1
     * 并且将可以表示的范围扩展为[1,k] 并 [1 + coins[i], k + coins[i]]
     * 但是如果 coins[i] > k, 集合[1,k] 和 [1 + coins[i], k + coins[i]] 中间就会有漏掉的
     * 这时为了尽最大可能扩展可表示的集合 就将k+1，添加进行
     * [1,k] 并 [k + 1, 2 * k + 1]
     */
    int minimumAddedCoins(vector<int>& coins, int target) {
        sort(coins.begin(), coins.end());
        int n = coins.size(), cnt = 0;
        for(int i = 0, k = 0; k < target; ) {
            if(i < n && coins[i] <= k + 1)
                k = k + coins[i++];
            else {
                k = 2 * k + 1;
                cnt++;
            }
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}