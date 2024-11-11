/**
 * @Time : 2022/7/17-1:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给你一个二维整数数组 stockPrices ，其中 stockPrices[i] = [dayi, pricei] 表示股票在 dayi 的价格为 pricei 。折线图 是一个二维平面上的若干个点组成的图，横坐标表示日期，纵坐标表示价格，折线图由相邻的点连接而成。比方说下图是一个例子：


请你返回要表示一个折线图所需要的 最少线段数 。

 

示例 1：



输入：stockPrices = [[1,7],[2,6],[3,5],[4,4],[5,4],[6,3],[7,2],[8,1]]
输出：3
解释：
上图为输入对应的图，横坐标表示日期，纵坐标表示价格。
以下 3 个线段可以表示折线图：
- 线段 1 （红色）从 (1,7) 到 (4,4) ，经过 (1,7) ，(2,6) ，(3,5) 和 (4,4) 。
- 线段 2 （蓝色）从 (4,4) 到 (5,4) 。
- 线段 3 （绿色）从 (5,4) 到 (8,1) ，经过 (5,4) ，(6,3) ，(7,2) 和 (8,1) 。
可以证明，无法用少于 3 条线段表示这个折线图。
示例 2：



输入：stockPrices = [[3,4],[1,2],[7,8],[2,3]]
输出：1
解释：
如上图所示，折线图可以用一条线段表示。
 

提示：

1 <= stockPrices.length <= 105
stockPrices[i].length == 2
1 <= dayi, pricei <= 109
所有 dayi 互不相同 。


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-lines-to-represent-a-line-chart
 */
class Solution {
public:
    int minimumLines(vector<vector<int>>& stockPrices) {
        sort(stockPrices.begin(), stockPrices.end(),
             [](const auto& a, const auto& b) -> bool {return a[0] < b[0];});
        int res = 0;
        long long a = 1e9 + 7, b = 1;
        for(int i = 1; i < stockPrices.size(); i++){
            int diffP = stockPrices[i][1] - stockPrices[i - 1][1];
            int diffDay = stockPrices[i][0] - stockPrices[i - 1][0];
            if(b * diffDay == a * diffP) continue;
            res++;
            a = diffDay, b = diffP;
        }
        return res;
    }

    int gcd(int a, int b){
        if(a < b) return gcd(b, a);
        if(b == 0) return a;
        return gcd(b, a % b);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}