/**
 * @Time : 2022/8/16-8:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数 n ，请你返回所有 0 到 1 之间（不包括 0 和 1）满足分母小于等于  n 的 最简 分数 。分数可以以 任意 顺序返回。

 

示例 1：

输入：n = 2
输出：["1/2"]
解释："1/2" 是唯一一个分母小于等于 2 的最简分数。
示例 2：

输入：n = 3
输出：["1/2","1/3","2/3"]
示例 3：

输入：n = 4
输出：["1/2","1/3","1/4","2/3","3/4"]
解释："2/4" 不是最简分数，因为它可以化简为 "1/2" 。
示例 4：

输入：n = 1
输出：[]
 

提示：

1 <= n <= 100

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/simplified-fractions
 */
class Solution {
public:
    /**
     * 执行用时：52 ms, 在所有 C++ 提交中击败了72.46%的用户
     * 内存消耗：21.4 MB, 在所有 C++ 提交中击败了45.51%的用户
     */
    vector<string> simplifiedFractions(int n) {
        vector<string> res;
        for(int i = 2; i <= n; i++){
            for(int j = 1; j < i; j++){
                if(gcd(i, j) == 1)
                    res.push_back(to_string(j) + "/" + to_string(i));
            }
        }
        return res;
    }

    int get(int a, int b){
        if(b == 0) return a;
        return gcd(b, a % b);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}