/**
 * @Time : 2025/2/27-8:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF808E 2300 思维 贪心 （参考答案学习）
 */
/*
  * 观察到 本题的物品重量只有 1 2 3 三种，分别叫a b c
  * 可以枚举其中一种选了几个 然后考虑另外两种的组合
  * 对于选出的c1, c2, c3肯定分别都拿相同重量下价值最大的
  *
  * 因为两个重量为1的物品打包就能变成重量为2的物品 所以考虑枚举c3
  * 在最终答案中 a物品的数量要么是奇数 要么是偶数
  * 如果a物品数量是偶数 将a从小到大两两打包 打包后就等价于b物品
  * 如果a物品数量是奇数 价值最大的一个肯定取到了 然后依旧可以将a物品从小到大两两打包
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 505, mod = 1e9 + 7;
ll T, n, m, base1 = 0;
vector<int> arr1, arr21, arr22, arr3;

void init() {
    sort(arr1.begin(), arr1.end(), [](auto& a, auto& b) -> bool {return a > b;});
    if(!arr1.empty()) base1 = arr1[0];
    for(int i = 0; i + 1 < arr1.size(); i += 2)
        arr22.push_back(arr1[i] + arr1[i + 1]);
    for(int i = 1; i + 1 < arr1.size(); i += 2)
        arr21.push_back(arr1[i] + arr1[i + 1]);
    arr3.push_back(INT_MAX), arr21.push_back(INT_MAX), arr22.push_back(INT_MAX);
    sort(arr3.begin(), arr3.end(), [](auto& a, auto& b) -> bool {return a > b;});
    sort(arr21.begin(), arr21.end(), [](auto& a, auto& b) -> bool {return a > b;});
    sort(arr22.begin(), arr22.end(), [](auto& a, auto& b) -> bool {return a > b;});
}

void solve() {
    ll ans = 0, sum21 = 0, sum22 = 0;
    ll sum3 = accumulate(arr3.begin() + 1, arr3.end(), 0ll);
    int c21 = 0, c22 = 0;
    for(int c3 = arr3.size() - 1; c3 >= 0; c3--) {
        int left = m - c3 * 3;
        if(left >= 0) {
            while((c21 + 1) * 2 + 1 <= left && c21 + 1 < arr21.size()) {
                c21++;
                sum21 += arr21[c21];
            }
            while((c22 + 1) * 2 <= left && c22 + 1 < arr22.size()) {
                c22++;
                sum22 += arr22[c22];
            }
            ll temp1 = left >= 1 ? sum3 + sum21 + base1 : -1, temp2 = sum3 + sum22;
            ans = max({ans, temp1, temp2});
        }
        sum3 -= arr3[c3];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> m;
    for(int i = 0, w, c; i < n; i++) {
        cin >> w >> c;
        if(w == 1) arr1.push_back(c);
        else if(w == 2) arr21.push_back(c), arr22.push_back(c);
        else arr3.push_back(c);
    }
    init();
    solve();
}