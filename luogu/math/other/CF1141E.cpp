/**
 * @Time : 2024/5/8-11:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * md一个攻击周期内的最大伤害 sum一个完整攻击周期内的
 * 如果 md > h 第一个周期内某一天就解决战斗
 * 否则 需要多个周期来解决 但是如果 sum >= 0，一个周期内怪物血量不降低 那就永远结束不了战斗了
 *
 * 怪物死的那一轮攻击 肯定是在md伤害达成或者之前
 * 因此计算攻击多少轮时 先将h - md。保证最后一轮攻击及时停下
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e9 + 1;
ll n, h, md = 0, sum = 0, nums[N];

ll solve() {
    if(abs(md) < h && sum >= 0) return -1;
    ll time, val;
    if(h <= abs(md)) time = 0, val = h;
    else {
        h += md;
        ll cnt = h / abs(sum), mod = h % abs(sum);
        time = cnt * n, val = mod + abs(md);
    }
    for(int i = 0; val > 0; i = (i + 1) % n) {
        val += nums[i];
        time++;
    }
    return time;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> h >> n;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
        md = min(md, sum);
    }
    cout << solve();
};