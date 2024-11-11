/**
 * @Time : 2023/5/5-12:27 PM
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
     * alice要让point(A) - point(B) 最大
     * bob要让point(A) - point(B) 最小，相当于也是 point(B) - point(A)
     * 两个人都是考虑如何选取石子，让自己与对方分数之差最大
     *
     * 取走x个石头后 换成价值=取走之和的一颗石头 放在最左边
     * 假定上一个人选择将截止原位置为i的石头拿走
     * 那么当前人，可以选择截止原位置为i+1，i+2,...,n-1的石头拿走，并且考虑拿哪个位置能获得最大差值
     *
     * 定义 diff(i) 为先手方选择石头范围[i, n - 1]能获得的最大差值
     * case1：选择截止石头i，当前获得分数sum[i]，并且放一个价值为sum[i]的石头在最左边
     * 那么对手可以选的范围就变为[i + 1, n - 1],对手也要获得最大差值diff(i+1)
     * 那么这种情况下，分数差为sum[i] - diff(i+1)
     * case2：选择截止石头i+1，当前获得分数sum[i+1]，对手可以选的范围就变为[i + 2, n - 1]
     * 那么这种情况下，分数差为sum[i+1] - diff(i+2)
     * ....
     * 所以有
     * diff(i) = max{sum[i] - diff(i+1), sum[i+1] - diff(i+2), ...,sum[n-2] - diff(n-1)}
     *         = max{ sum[i] - diff(i+1),
     *                max{sum[i+1] - diff(i+2), ...,sum[n-2] - diff(n-1)} }
     *         = max{sum[i] - diff(i+1), diff(i+1)}
     * 要求diff(i)，首先需要知道diff(i + 1)
     * diff(n - 1): 只剩一个石头可选，得分sum[n - 1]
     * 下一个选手没有可选的，游戏结束，因此分数差就是 sum[n - 1]
     *
     * 答案diff[1]，因为每一次至少要拿走两个石头，所以可选的范围是[1, n - 1]
     */
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> diff(n, 0), sum;
        sum.push_back(stones[0]);
        for(int i = 1; i < n; i++)
            sum.push_back(sum[i - 1] + stones[i]);
        diff[n - 1] = sum[n - 1];
        for(int i = n - 2; i >= 0; i--)
            diff[i] = max(diff[i + 1], sum[i] - diff[i + 1]);
        return diff[1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}