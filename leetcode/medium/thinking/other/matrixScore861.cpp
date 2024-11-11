/**
 * @Time : 2023/3/3-11:03 PM
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
     * 二进制最高位是1，一定比其它位都是1，但是最高位是0的数要大
     * 因此我们要保证第一列都是1才能获得最大值
     * 有两种方案：
     * 1.将第一列不是1的整行翻转
     * 2.将第一列是1的整行翻转，最后将第一列翻转成1
     * 两种方案对应两个矩阵
     * 然后从第二列开始，就只对列进行变换，因此此时对行变换就会破坏我们一开始调整好的最高位
     * 对列进行变换的时候，就统计1个数量，计算0的数量。1多就不翻转，0多就翻转这样就得到了尽可能大的值
     */
    int n, m;
    int matrixScore(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        vector<vector<int>> aux = grid;
        for(int i = 0; i < n; i++){
            if(grid[i][0] == 0)
                for(int j = 0; j < m; j++) grid[i][j] = !grid[i][j];
            else
                for(int j = 0; j < m; j++) aux[i][j] = !aux[i][j];
        }
        return max(max_point(aux), max_point(grid)) + n * (1 << (m - 1));
    }

    int max_point(vector<vector<int>>& grid){
        int res = 0;
        for(int i = 1; i < m; i++){
            int cnt = 0;
            for(int j = 0; j < n; j++)
                cnt += grid[j][i];
            res += max(cnt, n - cnt) * (1 << (m - i - 1));
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr = {{0,0,1,1},{1,0,1,0},{1,1,0,0}};
    s.matrixScore(arr);
    cout << 0 << endl;
}