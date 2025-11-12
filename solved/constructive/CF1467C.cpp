/**
 * @Time : 2025/3/20-5:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1467C 1900 构造算法 贪心
 */
 /*
  * 最后剩下一个数 那么这个数所在的数组 记为a 所有数都可以拿走
  * 只需要将a的所有元素移动到除a以外的最后一个元素，然后将该元素移动到a中最后一个数 就拿到了a中所有元素
  * 另外两个数组为b和c
  *
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 15, mod = 1e9 + 7;
ll T, n1, n2, n3, sum[3];
vector<int> arrs[3];

ll cal(int a, int b, int c) {
    // b和a都消除到c上
    ll t1 = sum[a] + sum[b] - sum[c];
    // c和a都消除到b上
    ll t2 = sum[a] + sum[c] - sum[b];
    // 用b和c最小的元素来承接对方
    ll t3 = sum[a] + sum[b] + sum[c] - 2 * arrs[b][0] - 2 * arrs[c][0];
    return max({t1, t2, t3});
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n1 >> n2 >> n3;
    ll cnt[3] = {n1, n2, n3};
    for(int i = 0; i < 3; i++) {
        for(int j = 0, num; j < cnt[i]; j++) {
            cin >> num;
            arrs[i].push_back(num), sum[i] += num;
        }
        sort(arrs[i].begin(), arrs[i].end());
    }
    ll ans = max({cal(0, 1, 2), cal(1, 0, 2), cal(2, 0, 1)});
    cout << ans << "\n";
}