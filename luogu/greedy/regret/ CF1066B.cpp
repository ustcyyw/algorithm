/**
 * @Time : 2024/4/22-4:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 反悔贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000 + 5;
int n, r, a[N];

int solve() {
    cin >> n >> r;
    int ans = 0;
    int hi = 0, pos = INT_MIN; // hi表示上一个加热器覆盖范围的最右端; pos表示当前选择的加热器位置
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        if(num == 0) continue;
        if(pos == INT_MIN) {
            if(i - r + 1 > 1) return -1; // 覆盖不到第一个位置
            pos = i, ans++;
        } else {
            if(pos + r - 1 + 1 < i - r + 1) return -1; // 覆盖不到上一个加热器的边缘
            // 现在试探的加热器覆盖不到 上一个加热器的最右端 那么当前加热器就必须选
            // 更新hi 并且答案+1 表示现在试探的这个加热器先开启
            if(i - r + 1 > hi + 1) {
                hi = pos + r - 1;
                ans++;
            }
            pos = i; // 在兼顾前面的前提下 尽可能拿最靠近右边的加热器
            if(i + r - 1 >= n) break;
        }
    }
    return pos + r - 1 >= n ? ans : -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cout << solve();
};