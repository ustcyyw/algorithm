/**
 * @Time : 2025/2/16-2:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3457 贪心
 */
 /*
  * 排序 一共吃了 n / 4 组 拿走 n / 4 个数
  * 奇数天m1天， 偶数天m2天
  * 奇数天的组 拿最大的就好
  * 偶数天的组 会有m2 * 2个数中 较大的一个被浪费
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        sort(pizzas.begin(), pizzas.end());
        int n = pizzas.size(), m = n / 4;
        int m1 = (m + 1) / 2, m2 = m - m1;
        long long ans = 0;
        for(int i = n - 1, cnt = 0; cnt < m1; i--, cnt++)
            ans += pizzas[i];
        for(int i = n - 1 - m1, cnt = 0; cnt < m2; i -= 2, cnt++)
            ans += pizzas[i - 1];
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}