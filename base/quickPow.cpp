/**
 * @Time : 2023/1/5-10:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

struct kx {
public:ll k, x;
};

class Solution {
public:
    /*
     * a ^ b 对mod取摸
     */
    ll qp(ll a, ll b) {
        ll res = 1;
        while (b != 0){
            if((b & 1) == 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    /* 快速幂可以用于求逆元 但是取mod会出现0的情况 要特殊处理
     * 可以使用二元结构 {k, x}
     * 取计算结果的时候 k大于0则说明计算结果为0，否则为x，即 k > 0 ? 0 : x
    */
    kx add1(kx p) { // 加1操作
        if (p.k > 0) return kx{0, 1};
        if (p.x == mod - 1) return kx{1, 1};
        return kx{0, p.x + 1};
    }

    kx mul(kx p, kx q) { // 乘法
        return kx{p.k + q.k, p.x * q.x % mod};
    }

    kx div(kx p, kx q) { // 除法
        return kx{p.k - q.k, p.x * qp(q.x, mod - 2) % mod};
    }

};

int main(){
    Solution s;
    
    cout << 0 << endl;
}