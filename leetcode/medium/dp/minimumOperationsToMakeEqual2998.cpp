/**
 * @Time : 2024/1/9-9:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 15;
class Solution {
public:
    /*
     * 1. 如果y >= x 那么x只能通过+操作得到y
     * 2. x > y 可以直接一系列的-操作得到y 共需要 x - y次
     * 2. x > y 可以通过调整x为5或者11的倍数 通过除法 快速减小x
     *    比如 x - x % 11, 就是通过(x % 11)次-操作 得到11的倍数
     *        x + (11 - x % 11)， 就是通过(11 - x % 11)次+操作 得到11的倍数
     *    假设 x - x % 11 后是11的t倍。
     *    先通过-操作得到11的t-1倍 需要 11 + x % 11 + 1 次操作得到t-1
     *    但是通过-操作得到11的t倍 需要x % 11 + 1 次操作得到t-1
     *    因此要得到一个更小的数 尽可能地少用+和-操作，凑成11或者5的倍数即可
     *
     */
    int minimumOperationsToMakeEqual(int x, int y) {
        unordered_map<int, int> cache;
        function<int(int, int)> dfs = [&](int x, int y) -> int {
            if(x <= y) return y - x;
            int key = x * N + y;
            if(cache[key] != 0) return cache[key];
            int t1 = x % 11 + dfs(x / 11, y) + 1; // x减去(x % 11)次1，成为11的倍数
            int t2 = 11 - x % 11 + dfs(x / 11 + 1, y) + 1; // x加上(11 - x % 11)次1 成为1的倍数
            int t3 = x % 5 + dfs(x / 5, y) + 1;
            int t4 = 5 - x % 5 + dfs(x / 5 + 1, y) + 1;
            int res = min({x - y, t1, t2, t3, t4});
            return cache[key] = res;
        };
        return dfs(x, y);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}