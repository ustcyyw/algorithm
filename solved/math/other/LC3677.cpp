/**
 * @Time : 2025/10/20-22:33
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3677 2223 数学 找规律
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 1100101 7位二进制数
     * 取6位二进制数 一定不会大于它 1xxxx1 中间还有4 / 2位可以任意选的
     * 取5位二进制数 1xxx1 中间还有 （3 + 1）/ 2 位可以任选
     * ...
     * 3位二进制数 1x1 中间还有（1 + 1） / 2位可以任选
     * 2位二进制数 11
     * 1位二进制数 0/1
     *
     * 然后考虑7位二进制数的情况 首位肯定要相同
     * n第2位是0，那么k也只能取0
     * n第2位是1
     *  k第2位可以取0,然后其它位任取
     *  k第2位继续取1，前两位都相同 看第三位...
     */
    int countBinaryPalindromes(long long n) {
        if(n <= 1) return n + 1;
        bitset<64> num(n);
        int d = 63, ans = 2; // 0和1两个数一定是答案
        while(d >= 0 && !num[d])
            d--;
        for(int i = d; i > 1; i--) // 最高位索引d，那么一共有d+1位，计算不满d+1位的情况
            ans += 1 << ((i - 1) / 2);
        for(int i = d - 1; i >= (d + 1) / 2; i--) {
            if(num[i] == 0) continue;
            // 当前位n是1，那么k也可以取0，高位一共d-i+1，算上对应的低位共用了2*(d-i+1)
            // 还剩d+1-2*(d-i+1) = 2i - d - 1位，那么可以自由填数的位是(2i - d) / 2
            ans += 1 << ((2 * i - d) / 2);
        }
        // 还要考虑前半部分数位全部一致，对应的回文二进制数是否 <= n
        for(int hi = d, lo = 0; hi > lo; hi--, lo++)
            num[lo] = num[hi];
        cout << num.to_ullong() << "\n";
        return ans + (num.to_ullong() <= n);
    }
};