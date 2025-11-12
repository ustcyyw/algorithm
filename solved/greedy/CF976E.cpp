/**
 * @Time : 2025/3/31-2:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF976E 2100 贪心 暴力枚举 前缀和 排序
 */
 /*
  * 假设有2次翻倍操作，有两个数a和b，有三种方案
  * a和b各翻倍一次 2a + 2b
  * a翻倍2次 b不变 4a + b
  * a不变 b翻倍两次 a + 4b
  * 方案1最优 则有两个不等式成立 2a + 2b >= 4a + b，2a + 2b >= a + 4b
  * 也就是 b >= 2a 且 a >= 2b
  * 除非a = b = 0，不然两个不等式不会同时成立 因此翻倍的操作只应该放在同一个数上
  * 那么就应该暴力枚举hp翻倍的数
  *
  * 而且有些时候原始的hp > dmg，这些才有使用替换操作的必要
  * 因此还需要先找到哪些区域在不进行翻倍操作的情况下 使用hp替换dmg
  * 暴力枚举hp翻倍的数 注意其在不同区域 操作方式不同
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, M = 30;
ll n, a, b, hps[N], dmgs[N], base;
vector<vector<int>> infos = {{INT_MIN, 0, 0}};

void solve() {
    ll idx = n + 1; // [idx, n]上 默认用hp替代dmg
    for(int i = 1; i <= n; i++) {
        hps[i] = hps[i - 1] + infos[i][1];
        dmgs[i] = dmgs[i - 1] + infos[i][2];
        if(idx == n + 1 && infos[i][0] >= 0) idx = i;
    }
    if(b == 0) { // 不可以进行任何替换操作
        cout << dmgs[n];
        return;
    }
    idx = max({idx, n - b + 1});
    ll ans = dmgs[idx - 1] + hps[n] - hps[idx - 1];
    for(int i = 1; i <= n; i++) {
        ll add = base * infos[i][1], temp = 0;
        if(i < idx) { // dmg区有一个用翻倍操作过的hp替换dmg
            // b的数量还够 dmg区用hp替换 依旧可以维持原本的hp区
            // 特殊地 idx = n + 1 的情况 也会落到这个逻辑分支 因为 b > 0，n - b + 1 一定小于idx
            // 此时 temp = dmgs[n] + add - infos[i][2]，hp区为空 依旧维持了原本hp空的情况
            if(n - b + 1 < idx)
                temp = dmgs[idx - 1] + add - infos[i][2] + hps[n] - hps[idx - 1];
                // b的数量不够 i位置用了hp替换 那么原本的hp区下标右移1位
            else temp = dmgs[idx] + add - infos[i][2] + hps[n] - hps[idx];
        } else { // hp区有一个用翻倍操作过的hp替换原hp
            temp = dmgs[idx - 1] + add - infos[i][1] + hps[n] - hps[idx - 1];
        }
        ans = max(ans, temp);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> a >> b;
    base = pow(2, a);
    for(int i = 1, num1, num2; i <= n; i++) {
        cin >> num1 >> num2;
        infos.push_back({num1 - num2, num1, num2});
    }
    sort(infos.begin(), infos.end());
    solve();
}