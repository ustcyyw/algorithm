/**
 * @Time : 2022/8/10-9:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的 二进制 字符串 floor ，它表示地板上砖块的颜色。

floor[i] = '0' 表示地板上第 i 块砖块的颜色是 黑色 。
floor[i] = '1' 表示地板上第 i 块砖块的颜色是 白色 。
同时给你 numCarpets 和 carpetLen 。你有 numCarpets 条 黑色 的地毯，每一条 黑色 的地毯长度都为 carpetLen 块砖块。请你使用这些地毯去覆盖砖块，使得未被覆盖的剩余 白色 砖块的数目 最小 。地毯相互之间可以覆盖。

请你返回没被覆盖的白色砖块的 最少 数目。

 

示例 1：



输入：floor = "10110101", numCarpets = 2, carpetLen = 2
输出：2
解释：
上图展示了剩余 2 块白色砖块的方案。
没有其他方案可以使未被覆盖的白色砖块少于 2 块。
示例 2：



输入：floor = "11111", numCarpets = 2, carpetLen = 3
输出：0
解释：
上图展示了所有白色砖块都被覆盖的一种方案。
注意，地毯相互之间可以覆盖。
 

提示：

1 <= carpetLen <= floor.length <= 1000
floor[i] 要么是 '0' ，要么是 '1' 。
1 <= numCarpets <= 1000

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-white-tiles-after-covering-with-carpets
 */
class Solution {
public:
    /**
     * dp[i][j]表示区间[0,i]上使用j块地毯能覆盖的白色瓷砖最大数目
     * dp[i][j] = max(dp[i - 1][j], dp[i - l][j - 1] + sum[i + 1] - sum[i - l + 1])
     * 第二项如果i-l < 0,就退化为sum[i + 1]，表示[0,i]可以被全覆盖
     */
    int minimumWhiteTiles(string floor, int numCarpets, int l) {
        int n = floor.size();
        vector<int> sum = vector(n + 1, 0); // 白色瓷砖数目的前缀和
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + (floor[i - 1] - '0');
        if(l * numCarpets >= n) return 0;
        vector<vector<int>> dp = vector(n, vector(numCarpets + 1, 0));
        for(int i = 1; i <= numCarpets; i++)
            dp[0][i] = sum[1];
        for(int i = 1; i < n; i++){
            for(int j = 1; j <= numCarpets; j++){
                int temp = i - l >= 0 ? dp[i - l][j - 1] + sum[i + 1] - sum[i - l + 1] : sum[i + 1];
                dp[i][j] = max(dp[i - 1][j], temp);
            }
        }
        return sum[n] - dp[n - 1][numCarpets];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}