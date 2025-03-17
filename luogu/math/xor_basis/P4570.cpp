/**
 * @Time : 2025/3/16-11:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P4570 线性基 贪心
 */
/*
  * 所选的矿石集合，它的真子集不可以异或为0
  *
  * 集合a的线性基，可以异或出 集合a中任意真子集的非0异或值
  * a的线性基可以异或出所有a中的元素 那么再往线性基中添加一个元素 这个新集合就不满足条件了
  * 所以满足条件的矿石集合，一定是a的线性基及其子集
  * 但是要让魔力值最大 肯定是选a的一个线性基 a的所有线性基 元素个数相同
  * 以普通方法求线性基的过程来看 就应该按魔力值从高到低选
  * 因为线性基中的一个元素 只占一个数位 这样选可以保证每个数位都选到了最大魔力值的那个
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, M = 63;
ll T, n, basis[M + 1];
vector<vector<ll>> infos;

void solve() {
    ll ans = 0;
    for(int j = n - 1; j >= 0; j--) {
        ll num = infos[j][1];
        for(int i = M; i >= 0; i--) {
            if((num & (1ll << i)) == 0) continue;
            if(basis[i] == 0) {
                basis[i] = num, ans += infos[j][0];
                break;
            } else num ^= basis[i];
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        infos.assign(n, vector(2, 0ll));
        for(int i = 0; i < n; i++)
            cin >> infos[i][1] >> infos[i][0];
        sort(infos.begin(), infos.end());
        solve();
    }
}