/**
 * @Time : 2024/6/9-1:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * bitset优化dp 常见于状态定义是true/false （1/0）的dp优化中
  * 可以优化掉常数 在总计算量上除以32
  *
  * 思想与状态压缩有类似的地方 就是用一个二进制位表示某个信息
  * 只不过集合情况巨多时，没法用整型数来简单表示，那就使用bitset表示
  * bitset中从二进制位低到高第j位为1表示 f[j] = true（实际题目中的意义可能是背包中的重量可以为j）
  * 为0则表示 f[j] = false
  *
  * 以 0/1 背包为例子
  * 要确定某一个值是否能够取得 当前数为v
  * f[i][j] = f[i-1][j] || f[i - 1][j - v]
  * 对于任意j 都是j位置和j-v位置的二进制进行位或运算
  * f[j, v]上的值都和f[j - v, 0]相应位置进行或运算
  * （背包优化中正常都可以优化掉i维度 这里首先省略了i维度）
  * 于是相当于将f中左移动v位得到f1（高位自动溢出），用 f1 和 f 进行位或运算
  *
  * 例题 lc周赛401 t4
  * https://leetcode.cn/problems/maximum-total-reward-using-operations-ii/description/
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;

class Solution {
public:
    /*
     * 周赛401 t4
     *
     * 假设最大的数是v1，第二大的数是v2
     * 如果最终答案是 v2 + preSum, 那显然有 v2 > perSum
     * 那么也有 v1 > perSum, 那为何不直接取答案为v1 + preSum
     * 因此 最终答案中一定要取最大数。那么前面所能取到的和最大为 v1 - 1
     *
     * 另外 两个相同的数 至多拿一个。因为拿了一个后 前置的和至少 >= 当前数值了
     * 就没法再拿当前数值第二次。
     */
    int maxTotalReward(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        int n = arr.size(), mv = arr.back();
        bitset<N> f, g;
        f.set(0); // 将0这一位设置为1 相当于dp状态定义中f[0] = true
        for(int i = 0; i < n - 1; i++) {
            // 可取的值为j，如果要选择当前元素 那么前置元素为 j - v，需要满足j - v < v
            // 也就是说用于位或的元素处于二进制的[0,v-1]位 要获取这些位 可以将f左移动N-v位
            // 这样就将[v, N]上的位都移除了 然后再右移动N-v位将其复位
            // 然后用[0,v-1]位上的信息进行位或(f[j] || f[j - v])
            // 需要再左移动v位 这样能将处于j-v位的移至j位
            int v = arr[i], t = N - v;
            g = (f << t) >> t;
            f |= g << v;
        }
        for(int s = mv - 1; s >= 0; s--) {
            if(f[s]) return s + mv;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}