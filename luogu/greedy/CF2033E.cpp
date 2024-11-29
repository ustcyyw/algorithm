/**
 * @Time : 2024/11/28-10:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2033E 1400 贪心 模拟
 */
 /*
  * p[p[i]] = i这个条件 举几个例子发现 就是两个数相互占了对方的位置
  * 遍历的过程中发现i位置的数不满足条件 要让他满足条件有2个办法
  * 1.将其挪动到其该在的位置p[i] 但是这样只会让一个数满足条件
  * 2.将和其搭配的数i放在他该放的位置p[i]，这样可以让两个数满足条件
  * 因此要让操作尽可能少 应该选择第二个解决办法
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7;
ll T, n, p[N], mp[N];

void solve() {
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(p[i] == i || p[p[i]] == i) continue;
        int j1 = mp[i], j2 = p[i], num = p[j2];
        mp[num] = j1;
        swap(p[j1], p[j2]);
        cnt++;
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> p[i];
            mp[p[i]] = i;
        }
        solve();
    };
};