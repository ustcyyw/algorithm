/**
 * @Time : 2023/7/24-3:44 PM
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
     * 本题猜结论 只需要考虑选择1行或者2行
     * 为什么
     * 1.考虑1行，显然改行的所有元素都是0
     * 2.考虑2行，那么这2行的各列之和至多为1，每一列元素进行与运算都是0
     * 3.考虑3行，注意向下取整，3行要求这3行的各列之和至多为1
     * 如果真的可以做到，那3行中任选2行都可以，直接考虑2行即可，所以3行的情况完全不用管
     * （实际上奇数行，除了1行的情况都是如此）
     * 4.考虑4行
     *      首先，到考虑4行的情况，一定是1行2行的情况都失效了
     *      也就是说任意两行拿出来都会有至少一列的和为2（不然这就是2行能找到的答案了）
     *      那么，4行的答案中任取2行，一共有6种取法，那么就会出现6个列之和为2（可能是相同列，也可能不同）
     *      但是题目规定 n <= 5，也就是说无论怎样，至少会有2个2在同一列，那么这一列的和至少为3，也就不行了
     * 5.同理 所有大于2的偶数行都不可取。
     *
     * 具体做法：总共有5列 可以使用二进制表示某一行的情况
     * 某两行的二进制表示相同时，二者相同，只选其中一行纳入考虑即可
     */
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        unordered_map<int, int> map; // status -> line id
        for(int i = 0; i < m; i++) {
            int s = 0;
            for(int j = 0; j < n; j++)
                s |= grid[i][j] << j;
            if(s == 0) return {i};
            map[s] = i;
        }
        for(auto& p1 : map) {
            for(auto& p2 : map)
                if(!(p1.first & p2.first)) {
                    vector<int> res = {p1.second, p2.second};
                    sort(res.begin(), res.end());
                    return res;
                }
        }
        return {};
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}