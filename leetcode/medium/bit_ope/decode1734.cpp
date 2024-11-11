/**
 * @Time : 2022/11/24-12:38 PM
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
     * 前 n 个正整数的排列
     *
     * e0 = p0 ^ p1, e1=p1 ^ p2, e2=p2 ^ p3, e[n - 2] = p[n - 2] ^ p[n - 1]
     * 令t1 = e0 = p0 ^ p1
     * t2 = t1 ^ e1 = p0 ^ p1 ^ p1 ^ p2 = p0 ^ p2
     * t3 = t2 ^ e2 = p0 ^ p2 ^ p2 ^ p3 = p0 ^ p3
     * ...
     * t[n-1] = t[n-2] ^ e[n - 2] = p0 ^ p[n-1]
     * 因为n为奇数，所以t的总项数 n - 1 为偶数，因此t1 ^ t2 ^ ... ^ t[n - 1]中，p0有偶数次异或，被消掉了
     * xorT = t1 ^ t2 ^ ... ^ t[n - 1] = p1 ^ p2 ^ ... ^ p[n-1]
     * 又因为知道p是1到n的整数的排列，可以求出 xorAll = p0 ^ p1 ^ p2 ^ ... ^ p[n-1]
     * 再将 xorAll ^ xorT = p0
     * 再递推出所有pi即可
     */
    vector<int> decode(vector<int>& encoded) {
        int xorAll = 0, xorT = 0, n = encoded.size();
        for(int i = 1; i <= n + 1; i++)
            xorAll ^= i;
        for(int i = 0, t = 0; i < n; i++){
            t ^= encoded[i];
            xorT ^= t;
        }
        vector<int> arr;
        arr.push_back(xorAll ^ xorT);
        for(int num : encoded)
            arr.push_back(arr.back() ^ num);
        return arr;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}