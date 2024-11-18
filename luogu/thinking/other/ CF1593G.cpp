/**
 * @Time : 2024/7/17-9:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1593G 思维题 结论题
 */
/*
 * 括号的方向没有意义 因为0花费就可调 括号的种类才会影响括号是否匹配
 *
 * 子区间有0个中括号 花费是0 调整小括号方向
 * 子区间有1个中括号 花费是1 将其调整为小括号
 *
 * 子区间有2个中括号 形如x[x]x 因为匹配的括号一定是偶数长度
 * 两个中括号之间长度为偶数（下标一奇一偶） 那么其中间一定匹配 再将这两个中括号调整为闭合的方向
 * 剔除[x]这个长度为偶数的子匹配括号 剩下的左右两边通过调整方向一定可以匹配 花费为0
 * 两个中括号之间长度为奇数（下标同奇偶） 那中间一定没法匹配 必须得改动两个中括号为小括号
 *
 * 子区间有3个中括号 形如x[x[x[x 至少得消费1将一个中括号变为小括号
 * 如果有其中一对 下标一奇一偶 那么将这一对调整闭合
 * 如果没有一对下标一奇一偶（下标全都是奇数/偶数） 那就需要花费3 全变小括号
 *
 * 子区间有4个中括号
 * 刚好两奇数两偶的话 奇偶奇偶 奇奇偶偶 偶偶奇奇 偶奇偶奇 四种情况
 * {奇偶}{奇偶} {奇{奇偶}偶} {偶{偶奇}奇} {偶奇}{偶奇}
 * 用花括号表示匹配的中括号分组情况 发现总是可以中括号匹配 并且其中间的子括号序列长度为偶数 可以匹配
 * 一奇三偶的情况 奇偶偶偶 偶奇偶偶 ...
 * 奇数位置的和任意一个偶数位置的中括号匹配 其中间子括号序列长度为偶数
 * 剩下两个偶数位置的括号 没有可以匹配的中括号 就必须都变为小括号 花费2
 * 三奇一偶 同理 花费为2
 * 全是偶数/全是奇数 任何两个中括号中间长度都为奇数 都无非匹配 都得变小括号 花费4
 *
 * 于是发现规律 子区间上奇数位置的中括号与偶数位置的中括号的数量差 就是所需操作次数
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, q, sum[N];
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> s >> q;
        s = '.' + s;
        n = s.size();
        for(int i = 1; i < n; i++) {
            sum[i] = sum[i - 1];
            if(s[i] == '[' || s[i] == ']') {
                if(i % 2 == 0) sum[i]++;
                else sum[i]--;
            }
        }
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            cout << abs(sum[r] - sum[l - 1]) << "\n";
        }
    }
};