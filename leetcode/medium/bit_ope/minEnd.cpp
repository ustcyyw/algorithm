/**
 * @Time : 2024/4/28-10:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛395 t3 位运算：试填法
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * x中为1的位 所有数中该位一定是1。
 * x中为0的，假定在最后一个数确定（就是所求）的情况下
 * 一定存在某几个数数 能让这些为0的位通过与操作变为0
 * （因为其它数都小于最后一个数 因此他们在该取0的位取0满足大小关系）
 * 总是可以让其它数来保证与运算后为x
 * 采用试填法求最高位 试探某个高位是否可以填0 从63位开始
 * 如果该位填0 那么最大值该位都是0了 其它更小的数必然不能填1 所以这一位固定
 * 能否填0 就看这一位固定为0后 后面剩余的位能否构造出n个数
 */
class Solution {
public:
    int m = 63;
    long long minEnd(int n, int x) {
        int total = m - __builtin_popcount(x) + 1; // total表示还剩多少二进制位可以填数字 最高位是m
        long long res = 0;
        for(int i = m; i >= 0 && total > 0; i--) { // total = 0就已经没有可以试填的位 结束循环
            long long t = 1ll << (total - 1); // 当前位试填0 那么后续最多还能造出最多t个数
            if((1ll << i) & x) continue;
            if(t < n) { // 扣除当前位 能安排的数的数量不足n 那么当前位就需要填1
                res |= 1ll << i;
                // 当前位填1，其它未填的位暂时是0
                // 那么其它更小的数可以任意构造t个 还需的构造个数变化 n -= t
                n -= t;
            }
            total--;
        }
        return res | x;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}