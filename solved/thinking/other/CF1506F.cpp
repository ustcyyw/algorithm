/**
 * @Time : 2024/7/9-10:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1506F 思维 找规律
 */
/*
  * 题目保证有解 由于边是单向往下走的 肯定要先到达行号较低的层
  * 数据量很大 所以得找规律
  * 记 diff = r - c
  * 如果diff = 1, 3, 5... 那么顺着这条斜边走 不需要任何cost就能一直向下
  * 如果diff = 0, 2, 4... 走这条斜边 每向下一层需要1的消耗
  * 那显然如果不是有就在这条斜边的目标点 肯定先切换到奇数斜边 免费向下走
  * 走到合适的位置再切到相应编号到斜边 直接到达目标点
  * 斜边可以从小编号切换到大编号 并且从偶数到奇数是不需要消耗的 从奇数到偶数消耗1
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, r[N], c[N], diff[N];
vector<vector<int>> pos;

void solve() {
    for(int i = 0; i < n; i++)
        pos.push_back({r[i], c[i]});
    sort(pos.begin(), pos.end());
    for(int i = 0; i < pos.size(); i++)
        diff[i] = pos[i][0] - pos[i][1];
    ll ans = 0;
    for(int i = 1; i < pos.size(); i++) {
        int d1 = diff[i - 1], d2 = diff[i];
        if(d1 == d2) {
            if(d1 % 2 == 0)
                ans += pos[i][1] - pos[i - 1][1];
        }
        else {
            int temp = d2 - d1 + (d1 % 2);
            ans += temp / 2;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        pos = {{1, 1}};
        for(int i = 0; i < n; i++)
            cin >> r[i];
        for(int i = 0; i < n; i++)
            cin >> c[i];
        solve();
    }
};