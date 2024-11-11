/**
 * @Time : 2023/9/27-5:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
     * 定义 dp[l][r] 表示区间[l,r]上的最大值，采用区间dp的方式找分割点
     * 容易发现对于序列 aba 就无法得到最优解 因为没有考虑到把中间的b移除的情况
     * 需要考虑后续相同元素连成片的情况
     * 因此可以定义 dp[l][r][k] 表示 区间[l,r]后续又紧跟k个 a = boxes[r] 的最大值
     * 后续又紧跟k个a，意味着原本的序列可能是 b.a.accada 取l = 0, r = 4 后续的cc和d已经被移除了
     * 实质上是序列 b.a.aaa
     * 那么
     * 1.dp[l][r][k] 的一种取法就是 连同 boxes[r] 和 后面的k个a一次移除，共有 k + 1个a
     * 还剩区间[l,r-1]因为boxes[r]和后面的k个a被移除了, r-1的右边已经没有元素 不可能还又等于boxes[r-1]的元素
     * 因此移除[l,r-1]获得的值就是 dp[l][r-1][0]
     * dp[l][r][k] = (k + 1) ^ 2 + dp[l][r-1][0]
     *
     * 2.另外的取法 考虑[l,r]上的元素boxes[p]=a, 且p != r
     * 将[l,r]分成3个部分 [l,p]、[p + 1,r-1]、[r,r]
     * 考虑将boxes[r]和[l,p]看作一个整体，因为r右边是k个a
     * 想着把这k个a与boxes[r]一起（共k+1个）与boxes[p]连在一起
     * 这样boxes[p]后面就有k+1个a和它自身相同了，要移除他们的值就是 dp[l][p][k+1]
     * 那么对于[p + 1,r-1]这个区间，要能使上述想法成立，就得先将区间[p+1,r-1]移除
     * 这样才能使boxes[r]和boxes[p]相邻
     * 移除区间[p+1,r-1]，boxes[r-1]的右边所有元素都拿去和[l,p]相邻了，没有其它元素了
     * 因此移除此区间的值为 dp[p+1][r-1][0]
     *
     * dp[l][r][k] = max({(k + 1) ^ 2 + dp[l][r-1][0],
     * dp[p+1][r-1][0] + dp[l][p][k+1], for boxes[p] = boxes[r]})
     *
     * 边界条件 if r < l， return 0
     * 答案 dp[0][n-1][0]，因为boxes[n-1]的后面没有任何元素了，等于boxes[n-1]的元素个数就是0
     */
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        vector<vector<vector<int>>> dp(n, vector(n, vector(n, 0)));
        function<int(int,int,int)> dfs = [&](int l, int r, int k) -> int {
            if(r < l) return 0;
            if(dp[l][r][k] > 0) return dp[l][r][k];
            int res = (k + 1) * (k + 1) + dfs(l, r - 1, 0);
            for(int i = l; i < r; i++) {
                if(boxes[i] == boxes[r])
                    res = max(res, dfs(l, i, k + 1) + dfs(i + 1, r - 1, 0));
            }
            dp[l][r][k] = res;
            return res;
        };
        return dfs(0, n - 1, 0);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}