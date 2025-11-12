/**
 * @Time : 2024/9/20-3:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1872E 异或性质
 */
/*
 * 利用异或的性质 令base为数组所有元素的异或和
 * one为初始时候s[i]='1'对应的元素的异或和
 * zero:
 * zero = base ^ one
 * 因此只要维护one即可。考虑一次变化操作带来的影响
 * 1. s中原本是0的元素变为1 应该异或到one中
 * 2. s中原本是1的元素变为0 应该从one中剔除 one中原本异或了这个数 再异或一次就消除了
 * 因此无论s中是1还是0 对one的影响都是将元素异或到one上
 * 那么就只需要将xor[l,r]异或到one上即可 xor[l,r]可以通过异或的前缀和快速计算
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, q, nums[N], x[N], one, base;
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            x[i] = x[i - 1] ^ nums[i];
        }
        cin >> s >> q;
        base = 0, one = 0;
        for(int i = 1; i <= n; i++) {
            base ^= nums[i];
            if(s[i - 1] == '1') one ^= nums[i];
        }
        for(int i = 1, t, l, r, g; i <= q; i++) {
            cin >> t;
            if(t == 1) {
                cin >> l >> r;
                one ^= x[r] ^ x[l - 1];
            } else {
                cin >> g;
                cout << (g == 1 ? one : base ^ one) << " ";
            }
        }
        cout << "\n";
    }
};