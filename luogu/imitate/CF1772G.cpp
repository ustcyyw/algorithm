/**
 * @Time : 2024/6/12-11:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1772G 模拟 贪心
 */
/*
 * 只能一轮一轮打 但是每轮的顺序是可调整的 肯定是先排序
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, x, y, nums[N];

ll solve() {
    sort(nums + 1, nums + n + 1);
    ll cnt = 0;
    for(int i = 1; i <= n && x < y; ) {
        if(x >= nums[i]) {
            cnt++, x++, i++;
        } else {
            // gap1是可以答应nums[i]需要的，gap2是可以达到y需要的
            ll gap1 = nums[i] - x, gap2 = y - x, base = (i - 1) - (n - i + 1);
            if(base <= 0) return -1; // 走一圈已经无法加分了 那就不可能达到y了
            ll cycle = gap1 % base == 0 ? gap1 / base : gap1 / base + 1; // 向上取整
            cycle = min(cycle, gap2 % base == 0 ? gap2 / base : gap2 / base + 1);
            if(x + cycle * base > y) { // 打完cycle圈会超过y了 那么在最后一圈+分阶段需要提前退出
                cnt += n - i + 1, x -= n - i + 1; // 单独计算最后不完整那圈的扣分阶段
                x += (cycle - 1) * base, cnt += (cycle - 1) * n;
                cnt += y - x, x = y;
            } else {
                cnt += cycle * n, x += cycle * base;
            }
        }
    }
    if(x >= y) return cnt;
    // 所有人都可以打败了 那么就以n为一次循环
    ll cycle = (y - x) / n;
    x += cycle * n, cnt += cycle * n;
    return cnt + y - x;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> x >> y;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};