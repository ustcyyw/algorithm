/**
 * @Time : 2025/3/10-10:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 异或空间线性基
 */
 /*
  * 异或空间线性基的定义：
  * 给定一个集合a 集合a中的元素相互异或（可以任意选择）得到集合c
  * 如果有另外一个集合b能通过元素之间相互异或得到c中的所有非0元素
  * 并且集合b的元素个数最少 那么b就是a的（异或空间）线性基
  * 换句话说 集合a的元素相互异或出的集合 与 集合b的元素相互异或出的集合 除0以外 完全等价
  *
  * 注意
  * 1.线性基是不可能异或出0的
  * 2.集合a可以有不同的线性基
  *
  * 例题
  * P3812 求异或最大值
  * P4570 对线性基概念 一般方法求线性基的理解
  * P3578 线性基一共可以表示出多少个异或值
  * CF845G/P4151 给定一个初始的数initV 求集合a中选数 与initV能异或出的最大值/最小值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 32;
ll basis[M + 1], zero = 0;
/*
 * 假设数位最高位是m (比如64位 32位)
 */

/*
 * 普通消元法求线性基
 * 数组basis[i]: 数位i的线性基，这里i是和数位对应
 * 用zero来标识原始集合a能否异或出0，注意是原始集合a而不是线性基
 * 遍历集合a中的所有元素 当前元素是num
 * 从m位开始往低位查看num，如果当前位i，num是1，就去查看basis[i]是否已经选了数
 * 如果没有选 就选择num
 * 如果已经选了 就令 num = num ^ basis[i]
 * 如果最终num = 0，就舍弃这个数 并且标识 zero = true
 *
 * 应用
 * 1. 集合a中选数 能异或出的值的个数，2 ^ cnt - 1, cnt是线性基的个数
 * 2. 集合a中选数 能异或出的最大值
 * 3. 给定一个初始的数initV 求集合a中选数 与initV能异或出的最大值/最小值
 * 从线性基的高位开始遍历基，将结果val与当前基异或 temp = val ^ basis[i]， 取val = max(val, temp)
 */
void init1(vector<ll>& a) {
    for(ll num : a) {
        for(int i = M; i >= 0; i--) {
            if((num & (1ll << i)) == 0) continue;
            if(basis[i] == 0) {
                basis[i] = num;
                break;
            } else num ^= basis[i];
        }
        if(num == 0) zero = 1;
    }
}

ll max_xor() {
    ll val = 0;
    for(int i = M; i >= 0; i--) {
        val = max(val, basis[i] ^ val);
    }
    return val;
}

/*
 * 高斯消元法求线性基
 * 数组basis[i]：第i个线性基础 这里i不代表数位 是选出来的编号 从左到右是减小的
 * 依旧是从高位开始 用lo标识待选区的起点下标
 * 针对第i位 从lo开始找到第一个该位上有1的数 交换到lo 如果没有找到 这一数位就跳过
 * 然后对其它所有数遍历查看i位是否有1 如果有 就进行异或
 * 最终线性基就是a中已选区的数
 *
 * 应用
 * 1.得到a集合第k小的非0异或值
 * 将线性基从小到底排列，从编号0开始，将k按二进制拆分 有1的位就取该编号的线性基异或
 * 比如k=10，就取编号3和1的线性基异或
 * 2.求第k小的异或和 考虑zero是否为0 转化为上一个问题
 */
int find(vector<ll>& a, int lo, int d) {
    for(int i = lo; i < a.size(); i++) {
        if(a[i] >> d == 1) return i;
    }
    return -1;
}
// 注意下标 板子是从0开始的
void init2(vector<ll>& a) {
    int lo = 0, n = a.size();
    for(int d = M; d >= 0; d--) {
        int j = find(a, lo, d);
        if(j == -1) continue;
        swap(a[j], a[lo]);
        for(int i = 0; i < n; i++) {
            if(i != lo && (a[i] >> d) == 1)
                a[i] ^= a[lo];
        }
        lo++;
    }
    for(int i = 0; i < lo; i++)
        basis[i] = a[i];
    zero = lo != n; // 基的数量不等于原始元素的个数
}

class Solution {
public:
    
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}