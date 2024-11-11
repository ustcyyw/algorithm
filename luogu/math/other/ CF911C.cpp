/**
 * @Time : 2024/4/20-1:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 具有周期性 先以最小的两个k来确定一个周期 m
 * 然后看两个周期内 用k3的周期是否可以填满所有的空位
 * 先根据k1和k2将两个周期内亮点的地方都标记起来
 * 然后再把相邻未标记的位置的距离算出来，这个就表示k3得是这个距离的一个因子 这样才能把两个空都标记上
 * 可能有多个相邻未标记的位置，因此k3得是他们的最大公约数的一个因子
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 50;
int n, k[4], k1, k2, k3, marked[N];

void light(int s, int kk, int r) {
    for(int i = s; i <= r; i += kk) {
        marked[i] = 1;
    }
}

int zero_gap(int r) {
    int num = -1;
    for(int i = 1, pre = -1; i <= r; i++) {
        if(marked[i] == 0) {
            if(pre == -1) pre = i;
            else {
                int gap = i - pre;
                num = num == -1 ? gap : gcd(num, gap);
            }
        }
    }
    return num;
}

bool solve() {
    sort(k, k + 3);
    k1 = k[0], k2 = k[1], k3 = k[2];
    if(k1 == 1) return true;
    int m = lcm(k1, k2) * 2 + 2;
    light(1, k1, m), light(2, k2, m);
    int num = zero_gap(m);
    if(num == -1) return true;
    return num % k3 == 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> k[0] >> k[1] >> k[2];
    cout << (solve() ? "YES" : "NO");
};