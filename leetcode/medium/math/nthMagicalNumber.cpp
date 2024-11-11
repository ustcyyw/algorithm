/**
 * @Time : 2022/4/29-12:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 找规律：a和b的最小公倍数为minMul，通过最小公倍数可以将a 和 b分成多个组
     * [0, minMul], [minMul, 2 * minMul],...
     * 每一组有 count = minMul / a + minMul / b - 1个数
     * 那么用 n / count，就知道答案落在哪一组，再找它是组内哪一个数即可
     *
     * 执行用时：4 ms, 在所有 C++ 提交中击败了5.41%的用户
     * 内存消耗：5.8 MB, 在所有 C++ 提交中击败了69.59%的用户
     */
    int MOD = 1000000007;
    int nthMagicalNumber(int n, int a, int b) {
        if(a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        if(b % a == 0) return (int)((long long)a * (long long)n % MOD);
        int minMul = a * b / get_gcb(b, a), count = minMul / a + minMul / b - 1;
        int groupIndex = n / count, flag = n % count;
        long long base = (long long)groupIndex * (long long)minMul;
        if(flag == 0) return (int)(base % MOD);
        return (int)((addition(flag, a, b) + base) % MOD);
    }

    long long addition(int n, long long a, long long b){
        long long res = 0;
        for(int k = 0, i = 1, j = 1; k < n; k++){
            if(a * i < b * j) res = a * i++;
            else res = b * j++;
        }
        return res;
    }

    int get_gcb(int x, int y){
        return y == 0 ? x : get_gcb(y, x % y);
    }

    int nthMagicalNumber2(int n, int a, int b) {
        if(a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        int lcm = a * b / get_gcb(b, a);
        long long lo = a, hi = (long long)a * (long long)n;
        while (lo < hi){ // 要找整除个数能大于等于n的最小值，最小值就刚好有n个能整除的数，就是答案
            long long mid = (lo + hi) / 2;
            if(check(n, lcm, a, b, mid)) hi = mid;
            else lo = mid + 1;
        }
        return (int)(lo % MOD);
    }

    bool check(int n, int lcm, int a, int b, long long num){
        long long count = num / a + num / b - num / lcm; // 最后这项是因为公倍数被重复计算了
        return count >= n;
    }
};

int main(){
    Solution s;
    cout << s.nthMagicalNumber2(4, 2, 3) << endl;
}