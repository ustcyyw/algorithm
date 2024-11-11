/**
 * @Time : 2024/3/30-4:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
ll T, n, d, k, a, b, t;

ll solve() {
    // 开车一次就能到达终点
    if(d <= k) return d * a;
    // 开车一次无法到达终点 但是至少开一次车 然后不修 一定是最优选择 假设都先开一次车
    if(k * b < k * a + t) { // 步行比开车修车快 那么开一次车之后开始步行
        return (d - k) * b + k * a;
    } else { // 开车修车比步行快。那么前面先开车，直到最后一次开车开不满k千米，就考虑剩下是步行还是修好继续开
        ll cnt = d / k, left = d % k;
        ll temp = min(left * a + t, left * b);
        return temp + cnt * k * a + (cnt - 1) * t;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> d >> k >> a >> b >> t;
    cout << solve();
};