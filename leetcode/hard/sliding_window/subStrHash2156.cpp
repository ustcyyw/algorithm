/**
 * @Time : 2022/12/6-8:04 PM
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
     * 固定长度为k的子串
     * 并且要计算的值是连续的 类似于和 可以考虑滑动窗口
     * 记p = pow(power, k - 1)，窗口中维护的值为hash
     * 从左往右，窗口移动的时候
     * hash先减去v(s[i - k])，再除以power, 最后加上v(s[i]) * p
     * 这个过程中有除法 因而取模就得用逆元或者无法算出逆元。因此不太方便
     *
     * 考虑从右往左滑动，窗口移动的时候
     * hash先减去v(s[i + k]) * p, 然后乘power，然后加v(s[i])
     */
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        long long p = 1, hash = 0;
        for(int i = 0; i < k - 1; i++)
            p = (p * power) % modulo;
        int n = s.size(), ans = n;
        for(int lo = n - 1, hi = n - 1; lo >= 0; lo--){
            if(hi - lo + 1 > k){
                hash = (hash - p * (s[hi] - 'a' + 1) + modulo) % modulo;
                hi--;
            }
            hash = (hash * power + s[lo] - 'a' + 1) % modulo;
            if(hi - lo + 1 == k && hash == hashValue) ans = lo;
        }
        return s.substr(ans, k);
    }
};

int main(){
    Solution s;
    s.subStrHash("algorithm", 7, 20, 2, 0);
    cout << 0 << endl;
}