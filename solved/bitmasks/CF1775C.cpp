/**
 * @Time : 2024/2/5-3:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * x的二进制为 xd, n的二进制为nd
 * 如果xd中有1的地方 nd中没有 那一定没法完成。因为n参与位与 必然导致这一位为0
 * 如果xd中为0的地方 但是nd中是1 说明需要通过[n, m]序列中但某一个数num该位出现0
 * 因为序列是连续的 实际上要位与到num，相当于要将n不断+1 最终通过进位操作让该位变为0
 * 但是
 * 1.进位的过程中 会导致低位全都出现0 xd的低位中有1 那就一定没法完成
 * 2.进位过程中 也可能导致nd中高位变为0，如果xd的这些高位中有1 也一定没法完成
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1e5 + 5;
ll T, n, x;
// 检查高位中nd变为0时，相应的xd中是否有1
bool check(bitset<64>& xd, bitset<64>& nd, int i) {
    while(i < 64 && nd[i] == 1) {
        if(xd[i]) return false;
        i++;
    }
    return true;
}

ll solve() {
    bitset<64> xd(x), nd(n);
    ll flag = 0, add = 0;
    for(int i = 0; i < 64; i++) {
        if(xd[i] == 1) flag = 1;
        if(xd[i] == 1 && nd[i] == 0) return -1;
        if(xd[i] == 0 && nd[i] == 1) {
            if(flag || !check(xd, nd, i + 1)) return -1;
            add = 1ll << (i + 1);
        }
    }
    return x + add;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> x;
        cout <<  solve() << "\n";
    }
};