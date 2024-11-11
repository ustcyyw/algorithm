/**
 * @Time : 2023/12/26-8:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * a[n-1] = b[n - 1] ^ b[n]
 * a1 = b1 ^ b2, a2 = b2 ^ b3, a3 = b3 ^ b4
 *
 * a1 ^ a2 = b1 ^ b3, a1 ^ a2 ^ a3 = b1 ^ b4
 * 令fi = a1 ^ ... ^ ai,则有 f[n-1] = b1 ^ bn
 * 对于f序列 f1 = b1 ^ b2, f2 = b1 ^ b3 ... 是b1和b[2,n]分别异或得到的
 * 并且由a序列与b序列的关系可知，只要知道b1就能递推地将b序列算出来
 * 因此 猜想从b1入手
 *
 * 位运算有一个可以尝试的想法 就是拆位
 * 假如b1中某一位是0，那么b[2,n]上的n-1个数，在该位上有多少个1
 * b1与b[2,n]上的数分别异或后（f序列），在该位上依然有多少个1
 * 否则b1中的该位应该是1
 * 对于所有二进制位求出b1上该位是0还是1，就得出b1
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 20, M = 2e5 + 5;
int n, a[M], cntB[N], cntF[N];

void countBit(int num, int cnt[]) {
    for(int i = 0; i < N; i++) {
        if((1 << i) & num)
            cnt[i]++;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(cntB, 0, sizeof(cntB)), memset(cntF, 0, sizeof(cntF));
    cin >> n;
    for(int i = 1; i < n; i++)
        countBit(i, cntB);
    for(int i = 0, f = 0; i < n - 1; i++) {
        cin >> a[i];
        f ^= a[i];
        countBit(f, cntF);
    }
    int b = 0;
    for(int i = 0; i < N; i++) {
        if(cntB[i] != cntF[i])
            b |= 1 << i;
    }
    cout << b << " ";
    for(int i = 0; i < n - 1; i++) {
        b ^= a[i];
        cout << b << " ";
    }
}