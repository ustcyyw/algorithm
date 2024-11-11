/**
 * @Time : 2022/9/3-2:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

每个孩子至少分配到 1 个糖果。
相邻两个孩子评分更高的孩子会获得更多的糖果。
请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。

 

示例 1：

输入：ratings = [1,0,2]
输出：5
解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
示例 2：

输入：ratings = [1,2,2]
输出：4
解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。
 

提示：

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/candy
 */
class Solution {
public:
    /**
     * 执行用时：12 ms, 在所有 C++ 提交中击败了97.09%的用户
     * 内存消耗：17.6 MB, 在所有 C++ 提交中击败了12.26%的用户
     */
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> forward(n, 0), back(n, 0);
        forward[0] = back[n - 1] = 1;
        for(int i = 1; i < n; i++){
            if(ratings[i] == ratings[i - 1]) forward[i] = forward[i - 1];
            else if(ratings[i] > ratings[i - 1]) forward[i] = forward[i - 1] + 1;
            else forward[i] = 1;
        }
        int res = 0;
        for(int i = n - 2; i >= 0; i--){
            if(ratings[i] == ratings[i + 1]) back[i] = back[i + 1];
            else if(ratings[i] > ratings[i + 1]) back[i] = back[i + 1] + 1;
            else back[i] = 1;
            res += max(forward[i], back[i]);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}