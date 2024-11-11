/**
 * @Time : 2022/8/16-3:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 rows x cols 大小的矩形披萨和一个整数 k ，矩形包含两种字符： 'A' （表示苹果）和 '.' （表示空白格子）。你需要切披萨 k-1 次，得到 k 块披萨并送给别人。

切披萨的每一刀，先要选择是向垂直还是水平方向切，再在矩形的边界上选一个切的位置，将披萨一分为二。如果垂直地切披萨，那么需要把左边的部分送给一个人，如果水平地切，那么需要把上面的部分送给一个人。在切完最后一刀后，需要把剩下来的一块送给最后一个人。

请你返回确保每一块披萨包含 至少 一个苹果的切披萨方案数。由于答案可能是个很大的数字，请你返回它对 10^9 + 7 取余的结果。

 

示例 1：



输入：pizza = ["A..","AAA","..."], k = 3
输出：3
解释：上图展示了三种切披萨的方案。注意每一块披萨都至少包含一个苹果。
示例 2：

输入：pizza = ["A..","AA.","..."], k = 3
输出：1
示例 3：

输入：pizza = ["A..","A..","..."], k = 1
输出：1
 

提示：

1 <= rows, cols <= 50
rows == pizza.length
cols == pizza[i].length
1 <= k <= 10
pizza 只包含字符 'A' 和 '.' 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/number-of-ways-of-cutting-a-pizza
 */
class Solution {
public:
    /**
     * 执行用时：44 ms, 在所有 C++ 提交中击败了26.89%的用户
     * 内存消耗：8.1 MB, 在所有 C++ 提交中击败了51.26%的用户
     */
    int n, m, mod = 1e9 + 7;
    vector<vector<int>> sum;
    //cache[i][j][k] 表示二维区间[i,n-1]*[j,m-1]上切k刀能有多少满足要求的切法
    vector<vector<vector<int>>> cache;
    int ways(vector<string>& pizza, int k) {
        n = pizza.size(), m = pizza[0].size();
        if(m + n - 2 < k - 1) return 0;
        sum.assign(n + 1, vector(m + 1, 0));
        for(int i = 1; i <= n; i++){
            for(int j = 1, line_sum = 0; j <= m; j++){
                line_sum += pizza[i - 1][j - 1] == 'A' ? 1 : 0;
                sum[i][j] = line_sum + sum[i - 1][j];
            }
        }
        cache.assign(n, vector(m, vector(k, -1)));
        return (int)countWay(0, 0, k - 1);
    }

    // 左上角顶点，右下角顶点 围成的矩形区域是否含有苹果
    bool hasApple(int l, int u, int r, int d){
        int cur_sum = sum[d + 1][r + 1] + sum[u][l] - sum[d + 1][l] - sum[u][r + 1];
        return cur_sum > 0;
    }

    long countWay(int l, int u, int k){
        if(cache[u][l][k] != -1) return cache[u][l][k];
        if(k == 0) return 1; // 在切之前就验证了切之后剩的部分含有苹果
        long res = 0;
        // [u-i]为一块,[i + 1, n - 1]一块。
        // 切了之后，最多还能切的次数 n - 1 - (i + 1) + m - 1 - l = n + m - i - l - 3 >= k - 1
        for(int i = u; i < n - 1 && n + m - i - l - 2 >= k; i++){
            if(!hasApple(l, i + 1, m - 1, n - 1)) // 剩下的[i + 1, n - 1]行中无苹果
                break;
            if(hasApple(l, u, m - 1, i))
                res = (res + countWay(l, i + 1, k - 1)) % mod;
        }
        // [l-i]为一块,[i + 1, m - 1]一块
        // 切了之后，最多还能切的次数 m - 1 - (i + 1) + n - 1 - u = n + m - i - u - 3 >= k - 1
        for(int i = l; i < m - 1 && n + m - i - u - 2 >= k; i++){
            if(!hasApple(i + 1, u, m - 1, n - 1))
                break;
            if(hasApple(l, u, i, n - 1))
                res = (res + countWay(i + 1, u, k - 1)) % mod;
        }
        cache[u][l][k] = res;
        return res;
    }
};

int main(){
    Solution s;
    vector<string> p = {".A","AA","A."};
    s.ways(p, 3);
    cout << 0 << endl;
}