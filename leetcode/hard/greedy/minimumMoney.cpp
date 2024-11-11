/**
 * @Time : 2022/9/17-10:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的二维整数数组 transactions，其中transactions[i] = [costi, cashbacki] 。

数组描述了若干笔交易。其中每笔交易必须以 某种顺序 恰好完成一次。在任意一个时刻，你有一定数目的钱 money ，为了完成交易 i ，money >= costi 这个条件必须为真。执行交易后，你的钱数 money 变成 money - costi + cashbacki 。

请你返回 任意一种 交易顺序下，你都能完成所有交易的最少钱数 money 是多少。

 

示例 1：

输入：transactions = [[2,1],[5,0],[4,2]]
输出：10
解释：
刚开始 money = 10 ，交易可以以任意顺序进行。
可以证明如果 money < 10 ，那么某些交易无法进行。
示例 2：

输入：transactions = [[3,0],[0,3]]
输出：3
解释：
- 如果交易执行的顺序是 [[3,0],[0,3]] ，完成所有交易需要的最少钱数是 3 。
- 如果交易执行的顺序是 [[0,3],[3,0]] ，完成所有交易需要的最少钱数是 0 。
所以，刚开始钱数为 3 ，任意顺序下交易都可以全部完成。
 

提示：

1 <= transactions.length <= 105
transactions[i].length == 2
0 <= costi, cashbacki <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-money-required-before-transactions
 */
class Solution {
public:
    /**
     * 一共有n比交易，对于某一种顺序，当前要完成的交易为t[i]
     * 要能完成交易的条件就是
     * money - (c[0] - back[0]) - (c[1] - back[1]) - ... - (c[i - 1] - back[i - 1]) >= c[i]
     * money >= c[i] + (c[0] - back[0]) + (c[1] - back[1]) + ... + (c[i - 1] - back[i - 1])
     * 要保证任意顺序都能使交易完成
     * money 就需要大于右边表达式的最大值
     * 枚举c[i]的时候，就只需要保证式子a：
     * (c[0] - back[0]) + (c[1] - back[1]) + ... + (c[i - 1] - back[i - 1])
     * 最大
     * 贪心地思考，要让这个式子最大，考虑的前置交易就是全部 c[j] > back[j]的交易
     */
    long long minimumMoney(vector<vector<int>>& transactions) {
        long long reduce = 0, res = 0;
        for(auto& t : transactions)
            if(t[0] > t[1]) reduce +=  t[0] - t[1];
        for(auto& t : transactions){
            // reduce - (t[0] - t[1]) + t[0]。- (t[0] - t[1])表示当前枚举的交易在式子a中的贡献，要扣除
            if(t[0] > t[1]) res = max(res, reduce + t[1]);
            else res = max(res, reduce + t[0]);
        }
        return res;
    }
};

int main(){
    Solution s;
    cout << 0 << endl;
}